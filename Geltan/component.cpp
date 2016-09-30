/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * component.cpp
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

#include "component_p.h"
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QEventLoop>

#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;

Component::Component(QObject *parent) : QObject(parent), d_ptr(new ComponentPrivate)
{

}


Component::Component(ComponentPrivate &dd, QObject *parent)
    : QObject(parent), d_ptr(&dd)
{

}


Component::~Component()
{

}




QNetworkAccessManager *Component::networkAccessManager() const { Q_D(const Component); return d->nam; }

void Component::setNetworkAccessManager(QNetworkAccessManager * networkAccessManager)
{
    Q_D(Component);
    if (networkAccessManager != d->nam) {
        d->nam = networkAccessManager;
#ifdef QT_DEBUG
        qDebug() << "Changed networkAccessManager to" << d->nam;
#endif
        Q_EMIT networkAccessManagerChanged(d->nam);
    }
}


bool Component::inOperation() const { Q_D(const Component); return d->inOperation; }

void Component::setInOperation(bool nInOperation)
{
    Q_D(Component);
    if (nInOperation != d->inOperation) {
        d->inOperation = nInOperation;
#ifdef QT_DEBUG
        qDebug() << "Changed inOperation to" << d->inOperation;
#endif
        Q_EMIT inOperationChanged(inOperation());
    }
}


int Component::requestTimeout() const { Q_D(const Component); return d->requestTimeout; }

void Component::setRequestTimeout(int nRequestTimeout)
{
    Q_D(Component);
    if (nRequestTimeout != d->requestTimeout) {
        d->requestTimeout = nRequestTimeout;
#ifdef QT_DEBUG
        qDebug() << "Changed requestTimeout to" << d->requestTimeout;
#endif
        Q_EMIT requestTimeoutChanged(requestTimeout());
    }
}



QNetworkAccessManager::Operation Component::networkOperation() const
{
    Q_D(const Component);
    return d->namOperation;
}



void Component::setNetworkOperation(QNetworkAccessManager::Operation operation)
{
    Q_D(Component);
    d->namOperation = operation;
}




QUrl Component::apiUrl() const
{
    Q_D(const Component);
    return d->apiUrl;
}


void Component::setApiUrl(const QUrl &url)
{
    Q_D(Component);
    d->apiUrl = url;
}




QString Component::apiPath() const
{
    Q_D(const Component);
    return d->apiPath;
}


void Component::setApiPath(const QString &path)
{
    Q_D(Component);
    d->apiPath = path;
}




QHash<QByteArray, QByteArray> Component::requestHeaders() const
{
    Q_D(const Component);
    return d->requestHeaders;
}


void Component::setRequestHeaders(const QHash<QByteArray, QByteArray> &headers)
{
    Q_D(Component);
    d->requestHeaders = headers;
}


void Component::addRequestHeader(const QByteArray &headerName, const QByteArray &headerValue)
{
    if (headerName.isEmpty()) {
        return;
    }

    Q_D(Component);
    d->requestHeaders.insert(headerName, headerValue);
}


void Component::addRequestHeaders(const QHash<QByteArray, QByteArray> &headers)
{
    if (headers.isEmpty()) {
        return;
    }

    Q_D(Component);

    QHash<QByteArray, QByteArray>::const_iterator i = headers.constBegin();
    while (i != headers.constEnd()) {
        d->requestHeaders.insert(i.key(), i.value());
        ++i;
    }
}




QByteArray Component::result() const
{
    Q_D(const Component);
    return d->result;
}




QByteArray Component::payload() const
{
    Q_D(const Component);
    return d->payload;
}


void Component::setPayload(const QByteArray &nPayload)
{
    Q_D(Component);
    d->payload = nPayload;
}


void Component::setPayload(const QString &nPayload)
{
    setPayload(nPayload.toUtf8());
}




Geltan::Error *Component::error() const
{
    Q_D(const Component);
    return d->error;
}


void Component::setError(Error *nError)
{
    Q_D(Component);

    if (d->error != nError) {
        Error *oldError = d->error;
        d->error = nError;
        if (oldError) {
            delete oldError;
        }
        Q_EMIT errorChanged(error());
    }
}



QString Component::auth() const
{
    Q_D(const Component);
    return d->auth;
}


void Component::setAuth(const QString &nAuth)
{
    Q_D(Component);
    d->auth = nAuth;
}




void Component::setUrlQuery(const QUrlQuery &query)
{
    Q_D(Component);
    d->urlQuery = query;
}


void Component::setUrlQuery(const QList<QPair<QString, QString> > &queryItems)
{
    if (!queryItems.isEmpty()) {
        Q_D(Component);
        d->urlQuery.setQueryItems(queryItems);
    }
}


void Component::addUrlQueryItem(const QString &key, const QString &value)
{
    if (key.isEmpty()) {
        return;
    }

    Q_D(Component);
    d->urlQuery.addQueryItem(key, value);
}


void Component::addUrlQueryItem(const QPair<QString, QString> &queryItem)
{
    if (queryItem.first.isEmpty()) {
        return;
    }

    Q_D(Component);
    d->urlQuery.addQueryItem(queryItem.first, queryItem.second);
}


void Component::addUrlQueryItems(const QList<QPair<QString, QString> > &queryItems)
{
    if (queryItems.isEmpty()) {
        return;
    }

    Q_D(Component);

    for (const auto &qi : queryItems) {
        d->urlQuery.addQueryItem(qi.first, qi.second);
    }
}


void Component::setUrlQueryDelimeters(QChar valueDelimeter, QChar pairDelimeter)
{
    Q_D(Component);
    d->urlQuery.setQueryDelimiters(valueDelimeter, pairDelimeter);
}


QUrlQuery Component::urlQuery() const
{
    Q_D(const Component);
    return d->urlQuery;
}





bool Component::checkInput()
{
    return true;
}



bool Component::checkOutput()
{
    return true;
}



void Component::sendRequest()
{
    Q_D(Component);

    setError(nullptr);
    d->result.clear();

    if (!checkInput()) {
        errorCallBack();
        return;
    }

    if (!d->apiUrl.isValid()) {
        setError(new Error(Error::InputError, tr("Invalid API URL."), Error::Critical, d->apiUrl.toString(), this));
        errorCallBack();
        return;
    }

    if (!d->apiPath.isEmpty()) {
        d->apiUrl.setPath(d->apiPath);
    }

    if (!d->urlQuery.isEmpty()) {
        d->apiUrl.setQuery(d->urlQuery);
    }

    if (!d->apiUrl.isValid()) {
        setError(new Error(Error::InputError, tr("Invalid API URL"), Error::Critical, d->apiUrl.toString(), this));
        errorCallBack();
        return;
    }

    if ((d->namOperation == QNetworkAccessManager::PostOperation || d->namOperation == QNetworkAccessManager::PutOperation) && d->payload.isEmpty()) {
        setError(new Error(Error::InputError, tr("Empty payload when trying to perform a POST network operation."), Error::Critical, QString(), this));
        errorCallBack();
        return;
    }

    if (!d->nam) {
        setNetworkAccessManager(new QNetworkAccessManager(this));
    }

    QNetworkRequest nr;

    if (!d->requestHeaders.isEmpty()) {
        QHash<QByteArray, QByteArray>::const_iterator i = d->requestHeaders.constBegin();
        while (i != d->requestHeaders.constEnd()) {
            nr.setRawHeader(i.key(), i.value());
            ++i;
        }
    }

    if (!d->auth.isEmpty()) {
        nr.setRawHeader(QByteArrayLiteral("Authorization"), d->auth.toUtf8());
    }

    nr.setUrl(d->apiUrl);

    if (!d->payload.isEmpty()) {
        nr.setRawHeader(QByteArrayLiteral("Content-Length"), QByteArray::number(d->payload.length()));
    }

#ifdef QT_DEBUG
    qDebug("Start performing network operation.");
    qDebug() << "API URL:" << d->apiUrl;
    if (!nr.rawHeaderList().isEmpty()) {
        const QList<QByteArray> hl = nr.rawHeaderList();
        for (const QByteArray &header : hl) {
            qDebug() << header << ":" << nr.rawHeader(header);
        }
    }
    qDebug() << "Payload:" << d->payload;
#endif

    if (d->requestTimeout > 0) {
        if (!d->timeoutTimer) {
            d->timeoutTimer = new QTimer(this);
            d->timeoutTimer->setSingleShot(true);
            d->timeoutTimer->setTimerType(Qt::VeryCoarseTimer);
            connect(d->timeoutTimer, &QTimer::timeout, this, &Component::_q_requestTimedOut);
        }
        d->timeoutTimer->start(d->requestTimeout * 1000);
    }

    d->performNetworkOperation(nr);
    connect(d->networkReply, &QNetworkReply::finished, this, &Component::_q_requestFinished);
}




void Component::sendRequest(const QUrl &url, const QString &path, const QHash<QByteArray, QByteArray> &headers, const QUrlQuery &query, const QByteArray &payLoad)
{
    setApiUrl(url);
    setApiPath(path);
    setRequestHeaders(headers);
    setUrlQuery(query);
    setPayload(payLoad);
    sendRequest();
}



void Component::_q_requestFinished()
{
    Q_D(Component);

    if (d->timeoutTimer && d->timeoutTimer->isActive()) {
        d->timeoutTimer->stop();
    }

    d->result = d->networkReply->readAll();

#ifdef QT_DEBUG
        qDebug("Request result: %s", d->result.constData());
#endif

    if (d->networkReply->error() == QNetworkReply::NoError) {

        if (checkOutput()) {
            successCallBack();
        } else {
            errorCallBack();
        }

    } else {

        extractError(d->networkReply);

        errorCallBack();
    }

    d->networkReply->deleteLater();
    d->networkReply = nullptr;
}




void Component::_q_requestTimedOut()
{
    Q_D(Component);

    setError(new Error(Error::RequestError, tr("The connection to the remote server timed out."), Error::Critical, d->networkReply->request().url().toString(), this));

    QNetworkReply *nr = d->networkReply;
    d->networkReply = nullptr;
    delete nr;

    errorCallBack();
}
