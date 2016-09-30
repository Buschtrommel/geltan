/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * requestaccesstoken.cpp
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

#include "requestaccesstoken_p.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

using namespace Geltan;
using namespace PP;


RequestAccessToken::RequestAccessToken(QObject *parent) :
    PPBase(*new RequestAccessTokenPrivate, parent)
{
    Q_D(RequestAccessToken);

    d->expiresIn = 0;
    d->apiPath = QStringLiteral("/v1/oauth2/token");
    d->payload = QByteArrayLiteral("grant_type=client_credentials");
    d->namOperation = QNetworkAccessManager::PostOperation;
    setExpectedType(PPBase::Object);
    addRequestHeaders({
                          {QByteArrayLiteral("Accept-Language"), QByteArrayLiteral("en_US")},
                          {QByteArrayLiteral("Content-Type"), QByteArrayLiteral("application/x-www-form-urlencoded")}
                      });

#ifdef GELTAN_PAYPAL_CLIENTID
    setClientID(QStringLiteral(GELTAN_PAYPAL_CLIENTID));
#endif

#ifdef GELTAN_PAYPAL_SECRET
    setSecret(QStringLiteral(GELTAN_PAYPAL_SECRET));
#endif

}


RequestAccessToken::RequestAccessToken(RequestAccessTokenPrivate &dd, QObject *parent) :
    PPBase(dd, parent)
{

}


RequestAccessToken::~RequestAccessToken()
{
}


void RequestAccessToken::call()
{
    setError(nullptr);
    setInOperation(true);

    setAuthentication();

    sendRequest();
}



void RequestAccessToken::successCallBack()
{
    QJsonObject ro = jsonResult().object();

    setScopes(ro.value(QStringLiteral("scope")).toString().split(QStringLiteral(" ")));
    setToken(ro.value(QStringLiteral("access_token")).toString());
    QString tt = ro.value(QStringLiteral("token_type")).toString();
    if (tt.contains(QLatin1String("bearer"), Qt::CaseInsensitive)) {
        setTokenType(PayPal::Bearer);
    } else if (tt.contains(QLatin1String("mac"), Qt::CaseInsensitive)) {
        setTokenType(PayPal::MAC);
    } else {
        setTokenType(PayPal::NoTokenType);
    }
    setAppID(ro.value(QStringLiteral("app_id")).toString());
    setExpiresIn(ro.value(QStringLiteral("expires_in")).toInt());

    setInOperation(false);
    Q_EMIT succeeded();
}


void RequestAccessToken::errorCallBack()
{
    setInOperation(false);
    Q_EMIT failed();
}




bool RequestAccessToken::checkInput()
{
    if (clientID().isEmpty() || secret().isEmpty()) {
        setError(new Error(Error::InputError, tr("Empty access token. You need to specify your app's Client ID and Secret in order to request an authentication token."), Error::Critical));
        return false;
    } else {
        return true;
    }
}



bool RequestAccessToken::checkOutput()
{
    return PPBase::checkOutput();
}



QStringList RequestAccessToken::scopes() const { Q_D(const RequestAccessToken); return d->scopes; }

void RequestAccessToken::setScopes(const QStringList & scopes)
{
    Q_D(RequestAccessToken);
    if (scopes != d->scopes) {
        d->scopes = scopes;
#ifdef QT_DEBUG
        qDebug() << "Changed scopes to" << d->scopes;
#endif
        Q_EMIT scopesChanged(d->scopes);
    }
}




QString RequestAccessToken::token() const { Q_D(const RequestAccessToken); return d->token; }

void RequestAccessToken::setToken(const QString & token)
{
    Q_D(RequestAccessToken);
    if (token != d->token) {
        d->token = token;
#ifdef QT_DEBUG
        qDebug() << "Changed token to" << d->token;
#endif
        Q_EMIT tokenChanged(d->token);
    }
}



PayPal::TokenType RequestAccessToken::tokenType() const { Q_D(const RequestAccessToken); return d->tokenType; }

void RequestAccessToken::setTokenType(PayPal::TokenType nTokenType)
{
    Q_D(RequestAccessToken);
    if (nTokenType != d->tokenType) {
        d->tokenType = nTokenType;
#ifdef QT_DEBUG
        qDebug() << "Changed tokenType to" << d->tokenType;
#endif
        Q_EMIT tokenTypeChanged(tokenType());
    }
}


QString RequestAccessToken::appID() const { Q_D(const RequestAccessToken); return d->appID; }

void RequestAccessToken::setAppID(const QString & appID)
{
    Q_D(RequestAccessToken);
    if (appID != d->appID) {
        d->appID = appID;
#ifdef QT_DEBUG
        qDebug() << "Changed appID to" << d->appID;
#endif
        Q_EMIT appIDChanged(d->appID);
    }
}


int RequestAccessToken::expiresIn() const { Q_D(const RequestAccessToken); return d->expiresIn; }

void RequestAccessToken::setExpiresIn(int expiresIn)
{
    Q_D(RequestAccessToken);
    if (expiresIn != d->expiresIn) {
        d->expiresIn = expiresIn;
#ifdef QT_DEBUG
        qDebug() << "Changed expiresIn to" << d->expiresIn;
#endif
        Q_EMIT expiresInChanged(d->expiresIn);
    }
}




