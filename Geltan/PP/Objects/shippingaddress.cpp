/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * shippingaddress.cpp
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

#include "shippingaddress_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


ShippingAddress::ShippingAddress(QObject *parent) :
    Address(parent), d_ptr(new ShippingAddressPrivate)
{
}


ShippingAddress::ShippingAddress(const QJsonDocument &json, QObject *parent) :
    Address(parent), d_ptr(new ShippingAddressPrivate)
{
    loadFromJson(json);
}


ShippingAddress::ShippingAddress(const QJsonObject &json, QObject *parent) :
    Address(parent), d_ptr(new ShippingAddressPrivate)
{
    loadFromJson(json);
}


ShippingAddress::~ShippingAddress()
{

}




QString ShippingAddress::recipientName() const { Q_D(const ShippingAddress); return d->recipientName; }

void ShippingAddress::setRecipientName(const QString &nRecipientName)
{
    Q_D(ShippingAddress); 
    if (nRecipientName != d->recipientName) {
        d->recipientName = nRecipientName;
#ifdef QT_DEBUG
        qDebug() << "Changed recipientName to" << d->recipientName;
#endif
        Q_EMIT recipientNameChanged(recipientName());
    }
}




QVariantMap ShippingAddress::toVariant()
{
    Q_D(ShippingAddress);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("line1"), line1(), 100);
    d->addStringToVariantMap(&map, QStringLiteral("line2"), line2(), 100);
    d->addStringToVariantMap(&map, QStringLiteral("city"), city(), 50);
    d->addStringToVariantMap(&map, QStringLiteral("country_code"), countryCode(), 2);
    d->addStringToVariantMap(&map, QStringLiteral("postal_code"), postalCode(), 20);
    d->addStringToVariantMap(&map, QStringLiteral("state"), state(), 100);
    d->addPhoneNumberToVariantMap(&map, QStringLiteral("phone"), phone());

    QString st; // status
    switch (status()) {
    case Confirmed:
        st = QStringLiteral("CONFIRMED");
        break;
    case Unconfirmed:
        st = QStringLiteral("UNCONFIRMED");
        break;
    default:
        break;
    }
    d->addStringToVariantMap(&map, QStringLiteral("status"), st);
    d->addStringToVariantMap(&map, QStringLiteral("typew"), type());
    d->addStringToVariantMap(&map, QStringLiteral("recipient_name"), recipientName(), 127);

    return map;
}



QJsonObject ShippingAddress::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void ShippingAddress::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void ShippingAddress::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setLine1(json.value(QStringLiteral("line1")).toString());

    setLine2(json.value(QStringLiteral("line2")).toString());

    setCity(json.value(QStringLiteral("city")).toString());

    setCountryCode(json.value(QStringLiteral("country_code")).toString());

    setPostalCode(json.value(QStringLiteral("postal_code")).toString());

    const QString stateString = json.value(QStringLiteral("state")).toString();
    if (QString::compare(stateString, QStringLiteral("Empty"), Qt::CaseInsensitive) == 0) {
        setState(QString());
    } else {
        setState(stateString);
    }

    setPhone(json.value(QStringLiteral("phone")).toString());

    const QString ns = json.value(QStringLiteral("normalization_status")).toString();
    if (ns == QLatin1String("UNNORMALIZED_USER_PREFERRED")) {
        setNormalizationStatus(UnnormalizedUserPreferred);
    } else if (ns == QLatin1String("NORMALIZED")) {
        setNormalizationStatus(Normalized);
    } else if (ns == QLatin1String("UNNORMALIZED")) {
        setNormalizationStatus(Unnormalized);
    } else {
        setNormalizationStatus(Unknown);
    }

    const QString ss = json.value(QStringLiteral("status")).toString();
    if (ss == QLatin1String("CONFIRMED")) {
        setStatus(Confirmed);
    } else if (ss == QLatin1String("UNCONFIRMED")) {
        setStatus(Unconfirmed);
    } else {
        setStatus(NoStatus);
    }

    setType(json.value(QStringLiteral("type")).toString());

    setRecipientName(json.value(QStringLiteral("recipient_name")).toString());
}
