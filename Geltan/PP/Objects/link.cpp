/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/link.cpp
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
    QObject(parent), d_ptr(new LinkPrivate(this))
{
}



Link::Link(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new LinkPrivate(this))
{
    loadFromJson(json);
}


Link::Link(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new LinkPrivate(this))
{
    loadFromJson(json);
}



Link::~Link()
{

}


QUrl Link::href() const { Q_D(const Link); return d->href; }


QString Link::rel() const { Q_D(const Link); return d->rel; }


Link::MethodType Link::method() const { Q_D(const Link); return d->method; }


void Link::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void Link::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Link);

    d->setHref(QUrl(json.value(QStringLiteral("href")).toString()));
    d->setRel(json.value(QStringLiteral("rel")).toString());
    d->setMethod(json.value(QStringLiteral("method")).toString());
}
