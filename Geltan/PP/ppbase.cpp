/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * ppbase.cpp
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "ppbase_p.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

using namespace Geltan;
using namespace PP;


PPBase::PPBase(QObject *parent)
    : Component(*new PPBasePrivate, parent)
{
    setRequestHeaders({{QByteArrayLiteral("Accept"), QByteArrayLiteral("application/json")}});
#ifdef QT_DEBUG
    setApiUrl(QUrl(QStringLiteral("https://api.sandbox.paypal.com")));
#else
    setApiUrl(QUrl(QStringLiteral("https://api.paypal.com")));
#endif
}


PPBase::PPBase(PPBasePrivate &dd, QObject *parent)
    : Component(dd, parent)
{
    setRequestHeaders({{QByteArrayLiteral("Accept"), QByteArrayLiteral("application/json")}});
#ifdef QT_DEBUG
    setApiUrl(QUrl(QStringLiteral("https://api.sandbox.paypal.com")));
#else
    setApiUrl(QUrl(QStringLiteral("https://api.paypal.com")));
#endif
}


PPBase::~PPBase()
{

}




void PPBase::setClientID(const QString &id)
{
    Q_D(PPBase);
    d->clientID = id;
}



QString PPBase::clientID() const
{
    Q_D(const PPBase);
    return d->clientID;
}



void PPBase::setSecret(const QString &sec)
{
    Q_D(PPBase);
    d->secret = sec;
}



QString PPBase::secret() const
{
    Q_D(const PPBase);
    return d->secret;
}


void PPBase::setToken(const QString &t)
{
    Q_D(PPBase);
    d->token = t;
}


QString PPBase::token() const
{
    Q_D(const PPBase);
    return d->token;
}



void PPBase::setAuthentication()
{
    Q_D(const PPBase);
    QString token;
    if (d->token.isEmpty() || d->tokenType == PayPal::NoTokenType) {
        token = QStringLiteral("Basic ");
        QString tokenParts;
        tokenParts.append(d->clientID);
        tokenParts.append(QLatin1String(":"));
        tokenParts.append(d->secret);
        token.append(QString(tokenParts.toUtf8().toBase64()));
    } else {
        switch(d->tokenType) {
        case PayPal::Bearer:
            token = QStringLiteral("Bearer ");
            break;
        case PayPal::MAC:
            token = QStringLiteral("MAC ");
            break;
        default:
            token = QStringLiteral("Basic ");
            break;
        }
        token.append(d->token);
    }
    qDebug("%s", qUtf8Printable(token));
    setAuth(token);
}



void PPBase::extractError(QNetworkReply *reply)
{
    if (!reply) {
        return;
    }

    QVariant vStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (vStatusCode.isValid()) {

        int statusCode = vStatusCode.toInt();
        if ((statusCode >= 400 && statusCode <= 404) || (statusCode >= 500 && statusCode <= 511)) {

            QJsonDocument json;
            json = QJsonDocument::fromJson(result());

            if (json.isNull() || !json.isObject()) {

                setError(new Error(reply, this));

            } else {

                QJsonObject jo = json.object();
                QJsonValue jsonMessage = jo.value(QStringLiteral("message"));
                QJsonValue jsonDetails = jo.value(QStringLiteral("details"));

                if (!jsonMessage.isNull() && jsonMessage.isString()) {
                    setError(new Error(Error::RequestError, jsonMessage.toString(), Error::Critical, jsonDetails.toString(), this));
                } else {
                    setError(new Error(reply, this));
                }
            }

        } else {
            setError(new Error(reply, this));
        }

    } else {
        setError(new Error(reply, this));
    }
}




bool PPBase::checkOutput()
{
    setJsonResult();

    if (jsonResult().isNull() && !(expectedType() == Empty)) {
        setError(new Error(Error::JSONParsingError, tr("Failed to parse network reply JSON data."), Error::Critical, QString(), this));
        return false;
    } else if (jsonResult().isNull() && expectedType() == Empty) {
        return true;
    } else {
        if (expectedType() == Array) {
            if (jsonResult().isArray()) {
                return true;
            } else {
                setError(new Error(Error::OutputError, tr("It was expected to retrieve a JSON array. The result data does not contain an array."), Error::Warning, QString(), this));
                return false;
            }
        } else {
            if (jsonResult().isObject()) {
                return true;
            } else {
                setError(new Error(Error::OutputError, tr("It was expected to retrieve a JSON object. The result data does not contain an object."), Error::Warning, QString(), this));
                return false;
            }
        }
    }
}




QJsonDocument PPBase::jsonResult() const
{
    Q_D(const PPBase);
    return d->jsonResult;
}


void PPBase::setJsonResult()
{
    Q_D(PPBase);
    d->jsonResult = QJsonDocument::fromJson(result());
}


void PPBase::setJsonResult(const QJsonDocument &nJsonResult)
{
    Q_D(PPBase);
    d->jsonResult = nJsonResult;
}


void PPBase::setJsonResult(const QByteArray &nJsonResult)
{
    Q_D(PPBase);
    d->jsonResult = QJsonDocument::fromJson(nJsonResult);
}



void PPBase::setExpectedType(ExpectedJSONType t)
{
    Q_D(PPBase);
    d->expectedType = t;
}


PPBase::ExpectedJSONType PPBase::expectedType() const
{
    Q_D(const PPBase);
    return d->expectedType;
}



PayPal::TokenType PPBase::tokenType() const { Q_D(const PPBase); return d->tokenType; }

void PPBase::setTokenType(PayPal::TokenType nTokenType)
{
    Q_D(PPBase);
    d->tokenType = nTokenType;
#ifdef QT_DEBUG
    qDebug() << " Set tokenType to" << d->tokenType;
#endif
}
