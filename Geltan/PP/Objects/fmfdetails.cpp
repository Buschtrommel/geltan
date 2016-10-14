/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/fmfdetails.cpp
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


#include "fmfdetails_p.h"
#include <QJsonDocument>
#include <QJsonObject>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


FMFDetails::FMFDetails(QObject *parent) :
    QObject(parent), d_ptr(new FMFDetailsPrivate(this))
{
}


FMFDetails::FMFDetails(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new FMFDetailsPrivate(this))
{
    loadFromJson(json);
}


FMFDetails::FMFDetails(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new FMFDetailsPrivate(this))
{
    loadFromJson(json);
}


FMFDetails::~FMFDetails()
{
}


FMFDetails::FilterType FMFDetails::filterType() const { Q_D(const FMFDetails); return d->filterType; }


FMFDetails::FilterIdentifier FMFDetails::filterId() const { Q_D(const FMFDetails); return d->filterId; }


QString FMFDetails::name() const { Q_D(const FMFDetails); return d->name; }


QString FMFDetails::description() const { Q_D(const FMFDetails); return d->description; }



void FMFDetails::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void FMFDetails::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(FMFDetails);

    d->setFilterType(json.value(QStringLiteral("filter_type")).toString());
    d->setFilterId(json.value(QStringLiteral("filter_id")).toString());
    d->setName(json.value(QStringLiteral("name")).toString());
    d->setDescription(json.value(QStringLiteral("description")).toString());
}
