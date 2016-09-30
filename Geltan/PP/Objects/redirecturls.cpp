/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * redirecturls.cpp
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

#include "redirecturls_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


RedirectUrls::RedirectUrls(QObject *parent) :
    QObject(parent), d_ptr(new RedirectUrlsPrivate)
{
#ifdef QT_DEBUG
    qDebug() << "Constructing new empty" << this;
#endif
}



RedirectUrls::RedirectUrls(const QUrl &returnUrl, const QUrl &cancelUrl, QObject *parent) : QObject(parent), d_ptr(new RedirectUrlsPrivate)
{
    Q_D(RedirectUrls);
    d->returnUrl = returnUrl;
    d->cancelUrl = cancelUrl;

#ifdef QT_DEBUG
    qDebug() << "Constructing new" << this << " with Return URL:" << returnUrl << "Cancel URL:" << cancelUrl;
#endif
}



RedirectUrls::RedirectUrls(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new RedirectUrlsPrivate)
{
    loadFromJson(json);
}



RedirectUrls::RedirectUrls(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new RedirectUrlsPrivate)
{
    loadFromJson(json);
}



RedirectUrls::~RedirectUrls()
{
}


QUrl RedirectUrls::returnUrl() const { Q_D(const RedirectUrls); return d->returnUrl; }

void RedirectUrls::setReturnUrl(const QUrl &nReturnUrl)
{
    Q_D(RedirectUrls); 
    if (nReturnUrl != d->returnUrl) {
        d->returnUrl = nReturnUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed returnUrl to" << d->returnUrl;
#endif
        Q_EMIT returnUrlChanged(returnUrl());
    }
}




QUrl RedirectUrls::cancelUrl() const { Q_D(const RedirectUrls); return d->cancelUrl; }

void RedirectUrls::setCancelUrl(const QUrl &nCancelUrl)
{
    Q_D(RedirectUrls); 
    if (nCancelUrl != d->cancelUrl) {
        d->cancelUrl = nCancelUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed cancelUrl to" << d->cancelUrl;
#endif
        Q_EMIT cancelUrlChanged(cancelUrl());
    }
}




QVariantMap RedirectUrls::toVariant() const
{
    QVariantMap map;

    if (returnUrl().isValid()) {
        map.insert(QStringLiteral("return_url"), returnUrl().toString());
    }

    if (cancelUrl().isValid()) {
        map.insert(QStringLiteral("cancel_url"), cancelUrl().toString());
    }

    return map;
}



QJsonObject RedirectUrls::toJsonObject() const
{
    return QJsonObject::fromVariantMap(this->toVariant());
}




bool RedirectUrls::isValid() const
{
    return (returnUrl().isValid() && cancelUrl().isValid());
}


void RedirectUrls::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void RedirectUrls::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    const QString ru = json.value(QStringLiteral("return_url")).toString();
    if (!ru.isEmpty()) {
        setReturnUrl(QUrl(ru));
    } else {
        setReturnUrl(QUrl());
    }

    const QString cu = json.value(QStringLiteral("cancel_url")).toString();
    if (!cu.isEmpty()) {
        setReturnUrl(QUrl(cu));
    } else {
        setReturnUrl(QUrl());
    }
}
