/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/creditcard.cpp
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

#include "creditcard_p.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <Geltan/PP/ppenumsmap.h>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


CreditCard::CreditCard(QObject *parent) :
    QObject(parent), d_ptr(new CreditCardPrivate)
{
}


CreditCard::CreditCard(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new CreditCardPrivate)
{
    loadFromJson(json);
}


CreditCard::CreditCard(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new CreditCardPrivate)
{
    loadFromJson(json);
}


CreditCard::~CreditCard()
{

}


QString CreditCard::number() const { Q_D(const CreditCard); return d->number; }

void CreditCard::setNumber(const QString &nNumber)
{
    Q_D(CreditCard); 
    if (nNumber != d->number) {
        d->number = nNumber;
#ifdef QT_DEBUG
        qDebug() << "Changed number to" << d->number;
#endif
        Q_EMIT numberChanged(number());
    }
}




PayPal::CreditCardType CreditCard::type() const { Q_D(const CreditCard); return d->type; }

void CreditCard::setType(PayPal::CreditCardType nType)
{
    Q_D(CreditCard);
    if (nType != d->type) {
        d->type = nType;
#ifdef QT_DEBUG
        qDebug() << "Changed type to" << d->type;
#endif
        Q_EMIT typeChanged(type());
    }
}




quint8 CreditCard::expireMonth() const { Q_D(const CreditCard); return d->expireMonth; }

void CreditCard::setExpireMonth(quint8 nExpireMonth)
{
    Q_D(CreditCard); 
    if (nExpireMonth != d->expireMonth) {
        d->expireMonth = nExpireMonth;
#ifdef QT_DEBUG
        qDebug() << "Changed expireMonth to" << d->expireMonth;
#endif
        Q_EMIT expireMonthChanged(expireMonth());
    }
}




quint16 CreditCard::expireYear() const { Q_D(const CreditCard); return d->expireYear; }

void CreditCard::setExpireYear(quint16 nExpireYear)
{
    Q_D(CreditCard); 
    if (nExpireYear != d->expireYear) {
        d->expireYear = nExpireYear;
#ifdef QT_DEBUG
        qDebug() << "Changed expireYear to" << d->expireYear;
#endif
        Q_EMIT expireYearChanged(expireYear());
    }
}




QString CreditCard::cvv2() const { Q_D(const CreditCard); return d->cvv2; }

void CreditCard::setCvv2(const QString &nCvv2)
{
    Q_D(CreditCard); 
    if (nCvv2 != d->cvv2) {
        d->cvv2 = nCvv2;
#ifdef QT_DEBUG
        qDebug() << "Changed cvv2 to" << d->cvv2;
#endif
        Q_EMIT cvv2Changed(cvv2());
    }
}




QString CreditCard::firstName() const { Q_D(const CreditCard); return d->firstName; }

void CreditCard::setFirstName(const QString &nFirstName)
{
    Q_D(CreditCard); 
    if (nFirstName != d->firstName) {
        d->firstName = nFirstName;
#ifdef QT_DEBUG
        qDebug() << "Changed firstName to" << d->firstName;
#endif
        Q_EMIT firstNameChanged(firstName());
    }
}




QString CreditCard::lastName() const { Q_D(const CreditCard); return d->lastName; }

void CreditCard::setLastName(const QString &nLastName)
{
    Q_D(CreditCard); 
    if (nLastName != d->lastName) {
        d->lastName = nLastName;
#ifdef QT_DEBUG
        qDebug() << "Changed lastName to" << d->lastName;
#endif
        Q_EMIT lastNameChanged(lastName());
    }
}




Address *CreditCard::billingAddress() const { Q_D(const CreditCard); return d->billingAddress; }

void CreditCard::setBillingAddress(Address *nBillingAddress)
{
    Q_D(CreditCard); 
    if (nBillingAddress != d->billingAddress) {
        d->billingAddress = nBillingAddress;
#ifdef QT_DEBUG
        qDebug() << "Changed billingAddress to" << d->billingAddress;
#endif
        Q_EMIT billingAddressChanged(billingAddress());
    }
}




QString CreditCard::externalCustomerId() const { Q_D(const CreditCard); return d->externalCustomerId; }

void CreditCard::setExternalCustomerId(const QString &nExternalCustomerId)
{
    Q_D(CreditCard); 
    if (nExternalCustomerId != d->externalCustomerId) {
        d->externalCustomerId = nExternalCustomerId;
#ifdef QT_DEBUG
        qDebug() << "Changed externalCustomerId to" << d->externalCustomerId;
#endif
        Q_EMIT externalCustomerIdChanged(externalCustomerId());
    }
}




CreditCard::State CreditCard::state() const { Q_D(const CreditCard); return d->state; }

void CreditCard::setState(State nState)
{
    Q_D(CreditCard); 
    if (nState != d->state) {
        d->state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << d->state;
#endif
        Q_EMIT stateChanged(state());
    }
}




QDateTime CreditCard::validUntil() const { Q_D(const CreditCard); return d->validUntil; }

void CreditCard::setValidUntil(const QDateTime &nValidUntil)
{
    Q_D(CreditCard); 
    if (nValidUntil != d->validUntil) {
        d->validUntil = nValidUntil;
#ifdef QT_DEBUG
        qDebug() << "Changed validUntil to" << d->validUntil;
#endif
        Q_EMIT validUntilChanged(validUntil());
    }
}




QList<Link*> CreditCard::links() const { Q_D(const CreditCard); return d->links; }

void CreditCard::setLinks(const QList<Link*> &nLinks)
{
    Q_D(CreditCard); 
    if (nLinks != d->links) {
        d->links = nLinks;
#ifdef QT_DEBUG
        qDebug() << "Changed links to" << d->links;
#endif
        Q_EMIT linksChanged(links());
    }
}



QUrl CreditCard::getLinkURL(const QString &rel) const
{
    const Link *l = getLink(rel);
    if (l) {
        return l->href();
    } else {
        return QUrl();
    }
}



Link* CreditCard::getLink(const QString &rel) const
{
    Q_D(const CreditCard);

    if (d->links.isEmpty()) {
        return nullptr;
    }

    for (Link *l : d->links) {
        if (l->rel() == rel) {
            return l;
        }
    }

    return nullptr;
}




QVariantMap CreditCard::toVariant()
{
    Q_D(CreditCard);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("number"), number());

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    d->addStringToVariantMap(&map, QStringLiteral("type"), em->creditCardTypeEnumToToken(type()));
    map.insert(QStringLiteral("expire_month"), expireMonth());
    map.insert(QStringLiteral("expire_year"), expireYear());
    d->addStringToVariantMap(&map, QStringLiteral("cvv2"), cvv2(), 4);
    d->addStringToVariantMap(&map, QStringLiteral("first_name"), firstName());
    d->addStringToVariantMap(&map, QStringLiteral("last_name"), lastName());
    if (billingAddress()) {
        d->addMapToVariantMap(&map, QStringLiteral("billing_address"), billingAddress()->toVariant());
    }
    d->addStringToVariantMap(&map, QStringLiteral("external_customer_id"), externalCustomerId(), 256);

    return map;
}



QJsonObject CreditCard::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void CreditCard::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void CreditCard::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(CreditCard);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    setNumber(json.value(QStringLiteral("number")).toString());

    setType(em->creditCardTypeTokenToEnum(json.value(QStringLiteral("type")).toString()));

    setExpireMonth(json.value(QStringLiteral("expire_month")).toString().toUInt());

    setExpireYear(json.value(QStringLiteral("expire_year")).toString().toUInt());

    setCvv2(json.value(QStringLiteral("cvv2")).toString());

    setFirstName(json.value(QStringLiteral("first_name")).toString());

    setLastName(json.value(QStringLiteral("last_name")).toString());

    const QJsonObject bao = json.value(QStringLiteral("billing_address")).toObject();
    Address *oldBillingAddress = billingAddress();
    if (!bao.isEmpty()) {
        if (oldBillingAddress) {
            oldBillingAddress->loadFromJson(bao);
        } else {
            setBillingAddress(new Address(bao, this));
        }
    } else {
        setBillingAddress(nullptr);
        delete oldBillingAddress;
    }


    setExternalCustomerId(json.value(QStringLiteral("external_customer_id")).toString());

    const QString sState = json.value(QStringLiteral("state")).toString();
    if (sState == QLatin1String("ok")) {
        setState(Ok);
    } else if (sState == QLatin1String("expired")) {
        setState(Expired);
    } else {
        setState(NoState);
    }

    const QString sValidUntil = json.value(QStringLiteral("valid_until")).toString();
    if (!sValidUntil.isEmpty()) {
        setValidUntil(QDateTime::fromString(sValidUntil, Qt::ISODate));
    } else {
        setValidUntil(QDateTime());
    }

    const QJsonArray la = json.value(QStringLiteral("links")).toArray();
    d->clearLinks();
    Q_EMIT linksChanged(links());
    if (!la.isEmpty()) {
        QList<Link*> linksToAdd;
        QJsonArray::const_iterator i = la.constBegin();
        while (i != la.constEnd()) {
            linksToAdd.append(new Link(i->toObject()));
            ++i;
        }
        setLinks(linksToAdd);
    }
}
