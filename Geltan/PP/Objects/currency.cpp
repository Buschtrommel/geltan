/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * currency.cpp
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

#include "currency_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Currency::Currency(QObject *parent) :
    QObject(parent), d_ptr(new CurrencyPrivate)
{
}


Currency::Currency(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new CurrencyPrivate)
{
    loadFromJson(json);
}


Currency::Currency(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new CurrencyPrivate)
{
    loadFromJson(json);
}


Currency::~Currency()
{
    delete d_ptr;
}


QString Currency::currency() const { Q_D(const Currency); return d->currency; }

void Currency::setCurrency(const QString &nCurrency)
{
    Q_D(Currency); 
    QString _cur = nCurrency.simplified().remove(QStringLiteral(" "));
    _cur.truncate(3);
    if (_cur != d->currency) {
        d->currency = _cur;
#ifdef QT_DEBUG
        qDebug() << "Changed currency to" << d->currency;
#endif
        Q_EMIT currencyChanged(currency());
    }
}




float Currency::value() const { Q_D(const Currency); return d->value; }

void Currency::setValue(float nValue)
{
    Q_D(Currency); 
    if (nValue != d->value) {
        d->value = nValue;
#ifdef QT_DEBUG
        qDebug() << "Changed value to" << d->value;
#endif
        Q_EMIT valueChanged(value());
    }
}



QVariantMap Currency::toVariant()
{
    Q_D(Currency);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("currency"), currency(), 3);
    d->addFloatToVariantMap(&map, QStringLiteral("value"), value());

    return map;
}


QJsonObject Currency::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void Currency::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void Currency::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setCurrency(json.value(QStringLiteral("currency")).toString());

    setValue(json.value(QStringLiteral("value")).toString().toFloat());
}
