/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * link.cpp
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

#include "link_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Link::Link(QObject *parent) :
    QObject(parent), d_ptr(new LinkPrivate)
{
}



Link::Link(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new LinkPrivate)
{
    loadFromJson(json);
}


Link::Link(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new LinkPrivate)
{
    loadFromJson(json);
}



Link::~Link()
{

}


QUrl Link::href() const { Q_D(const Link); return d->href; }

void Link::setHref(const QUrl &nHref)
{
    Q_D(Link); 
    if (nHref != d->href) {
        d->href = nHref;
#ifdef QT_DEBUG
        qDebug() << "Changed href to" << d->href;
#endif
        Q_EMIT hrefChanged(href());
    }
}




QString Link::rel() const { Q_D(const Link); return d->rel; }

void Link::setRel(const QString &nRel)
{
    Q_D(Link); 
    if (nRel != d->rel) {
        d->rel = nRel;
#ifdef QT_DEBUG
        qDebug() << "Changed rel to" << d->rel;
#endif
        Q_EMIT relChanged(rel());
    }
}




Link::MethodType Link::method() const { Q_D(const Link); return d->method; }

void Link::setMethod(MethodType nMethod)
{
    Q_D(Link); 
    if (nMethod != d->method) {
        d->method = nMethod;
#ifdef QT_DEBUG
        qDebug() << "Changed method to" << d->method;
#endif
        Q_EMIT methodChanged(method());
    }
}




QVariantMap Link::toVariant()
{
    Q_D(Link);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("href"), href().toString());
    d->addStringToVariantMap(&map, QStringLiteral("rel"), rel());

    QString m; // method string

    switch(method()) {
    case Get:
        m = QStringLiteral("GET");
        break;
    case Redirect:
        m = QStringLiteral("REDIRECT");
        break;
    case Post:
        m = QStringLiteral("POST");
        break;
    default:
        break;
    }

    d->addStringToVariantMap(&map, QStringLiteral("method"), m);

    return map;
}



QJsonObject Link::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}


void Link::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void Link::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setHref(QUrl(json.value(QStringLiteral("href")).toString()));
    setRel(json.value(QStringLiteral("rel")).toString());

    const QString sMethod = json.value(QStringLiteral("method")).toString();
    if (sMethod == QLatin1String("GET")) {
        setMethod(Get);
    } else if (sMethod == QLatin1String("REDIRECT")) {
        setMethod(Redirect);
    } else if (sMethod == QLatin1String("POST")) {
        setMethod(Post);
    } else {
        setMethod(Undefined);
    }
}
