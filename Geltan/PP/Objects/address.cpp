/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/address.cpp
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

#include "address_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Address::Address(QObject *parent) :
    QObject(parent), d_ptr(new AddressPrivate(this))
{
}



Address::Address(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new AddressPrivate(this))
{
    loadFromJson(json);
}


Address::Address(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new AddressPrivate(this))
{
    loadFromJson(json);
}



Address::~Address()
{
}


QString Address::line1() const { Q_D(const Address); return d->line1; }

void Address::setLine1(const QString &nLine1)
{
    Q_D(Address); 
    if (nLine1 != d->line1) {
        d->line1 = nLine1;
#ifdef QT_DEBUG
        qDebug() << "Changed line1 to" << d->line1;
#endif
        Q_EMIT line1Changed(line1());
    }
}




QString Address::line2() const { Q_D(const Address); return d->line2; }

void Address::setLine2(const QString &nLine2)
{
    Q_D(Address); 
    if (nLine2 != d->line2) {
        d->line2 = nLine2;
#ifdef QT_DEBUG
        qDebug() << "Changed line2 to" << d->line2;
#endif
        Q_EMIT line2Changed(line2());
    }
}



QString Address::city() const { Q_D(const Address); return d->city; }

void Address::setCity(const QString &nCity)
{
    Q_D(Address);
    if (nCity != d->city) {
        d->city = nCity;
#ifdef QT_DEBUG
        qDebug() << "Changed city to" << d->city;
#endif
        Q_EMIT cityChanged(city());
    }
}





QString Address::countryCode() const { Q_D(const Address); return d->countryCode; }

void Address::setCountryCode(const QString &nCountryCode)
{
    Q_D(Address); 
    if (nCountryCode != d->countryCode) {
        d->countryCode = nCountryCode;
#ifdef QT_DEBUG
        qDebug() << "Changed countryCode to" << d->countryCode;
#endif
        Q_EMIT countryCodeChanged(countryCode());
    }
}




QString Address::postalCode() const { Q_D(const Address); return d->postalCode; }

void Address::setPostalCode(const QString &nPostalCode)
{
    Q_D(Address); 
    if (nPostalCode != d->postalCode) {
        d->postalCode = nPostalCode;
#ifdef QT_DEBUG
        qDebug() << "Changed postalCode to" << d->postalCode;
#endif
        Q_EMIT postalCodeChanged(postalCode());
    }
}




QString Address::state() const { Q_D(const Address); return d->state; }

void Address::setState(const QString &nState)
{
    Q_D(Address); 
    if (nState != d->state) {
        d->state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << d->state;
#endif
        Q_EMIT stateChanged(state());
    }
}




QString Address::phone() const { Q_D(const Address); return d->phone; }

void Address::setPhone(const QString &nPhone)
{
    Q_D(Address); 
    if (nPhone != d->phone) {
        d->phone = nPhone;
#ifdef QT_DEBUG
        qDebug() << "Changed phone to" << d->phone;
#endif
        Q_EMIT phoneChanged(phone());
    }
}




Address::NormalizationStatus Address::normalizationStatus() const { Q_D(const Address); return d->normalizationStatus; }




Address::Status Address::status() const { Q_D(const Address); return d->status; }

void Address::setStatus(Status nStatus)
{
    Q_D(Address); 
    if (nStatus != d->status) {
        d->status = nStatus;
#ifdef QT_DEBUG
        qDebug() << "Changed status to" << d->status;
#endif
        Q_EMIT statusChanged(status());
    }
}




QString Address::type() const { Q_D(const Address); return d->type; }

void Address::setType(const QString &nType)
{
    Q_D(Address); 
    if (nType != d->type) {
        d->type = nType;
#ifdef QT_DEBUG
        qDebug() << "Changed type to" << d->type;
#endif
        Q_EMIT typeChanged(type());
    }
}



QVariantMap Address::toVariant()
{
    Q_D(Address);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("line1"), line1().simplified(), 100);
    d->addStringToVariantMap(&map, QStringLiteral("line2"), line2().simplified(), 100);
    d->addStringToVariantMap(&map, QStringLiteral("city"), city().simplified(), 50);
    d->addStringToVariantMap(&map, QStringLiteral("country_code"), countryCode().simplified(), 2);
    d->addStringToVariantMap(&map, QStringLiteral("postal_code"), postalCode().simplified(), 20);

    if (countryCode().compare(QLatin1String("us"), Qt::CaseInsensitive) == 0) {
        d->addStringToVariantMap(&map, QStringLiteral("state"), state().simplified(), 2);
    } else {
        d->addStringToVariantMap(&map, QStringLiteral("state"), state().simplified(), 100);
    }

    d->addPhoneNumberToVariantMap(&map, QStringLiteral("phone"), phone());

    if (status() == CONFIRMED) {
        d->addStringToVariantMap(&map, QStringLiteral("status"), QStringLiteral("CONFIRMED"));
    } else  if (status() == CONFIRMED) {
        d->addStringToVariantMap(&map, QStringLiteral("status"), QStringLiteral("CONFIRMED"));
    }

    d->addStringToVariantMap(&map, QStringLiteral("type"), type().simplified());

    return map;
}



QJsonObject Address::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void Address::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void Address::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Address);

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
        d->setNormalizationStatus(UNNORMALIZED_USER_PREFERRED);
    } else if (ns == QLatin1String("NORMALIZED")) {
        d->setNormalizationStatus(NORMALIZED);
    } else if (ns == QLatin1String("UNNORMALIZED")) {
        d->setNormalizationStatus(UNNORMALIZED);
    } else {
        d->setNormalizationStatus(UNKNOWN);
    }

    const QString ss = json.value(QStringLiteral("status")).toString();
    if (ss == QLatin1String("CONFIRMED")) {
        setStatus(CONFIRMED);
    } else if (ss == QLatin1String("UNCONFIRMED")) {
        setStatus(UNCONFIRMED);
    } else {
        setStatus(NO_STATUS);
    }

    setType(json.value(QStringLiteral("type")).toString());
}
