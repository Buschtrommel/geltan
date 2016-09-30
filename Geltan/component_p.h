/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * component_p.h
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

#ifndef COMPONENT_P_H
#define COMPONENT_P_H

#include "component.h"
#include <QUrlQuery>
#include <QTimer>

namespace Geltan {

class ComponentPrivate
{
public:
    ComponentPrivate() :
        nam(nullptr),
        retryCount(0),
        inOperation(false),
        requestTimeout(60),
        error(nullptr),
        namOperation(QNetworkAccessManager::GetOperation),
        timeoutTimer(nullptr),
        networkReply(nullptr)
    {}

    virtual ~ComponentPrivate() {}

    void performNetworkOperation(const QNetworkRequest &request)
    {
        switch(namOperation) {
        case QNetworkAccessManager::HeadOperation:
            networkReply = nam->head(request);
            break;
        case QNetworkAccessManager::PostOperation:
            networkReply = nam->post(request, payload);
            break;
        case QNetworkAccessManager::PutOperation:
            networkReply = nam->put(request, payload);
            break;
        case QNetworkAccessManager::DeleteOperation:
            networkReply = nam->deleteResource(request);
            break;
        default:
            networkReply = nam->get(request);
            break;
        }
    }

    QNetworkAccessManager *nam;
    quint8 retryCount;
    bool inOperation;
    int requestTimeout;
    Error *error;
    QNetworkAccessManager::Operation namOperation;
    QUrl apiUrl;
    QString apiPath;
    QHash<QByteArray,QByteArray> requestHeaders;
    QByteArray payload;
    QUrlQuery urlQuery;
    QString auth;
    QByteArray result;
    QTimer *timeoutTimer;
    QNetworkReply *networkReply;
};

}

#endif // COMPONENT_P_H
