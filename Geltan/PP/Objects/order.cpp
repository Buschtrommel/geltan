/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * order.cpp
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

#include "order_p.h"
#include <Geltan/PP/Objects/paymentamount.h>
#include <Geltan/PP/Objects/fmfdetails.h>
#include <Geltan/PP/Objects/link.h>
#include <Geltan/PP/ppenumsmap.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Order::Order(QObject *parent) :
    QObject(parent), d_ptr(new OrderPrivate)
{
}



Order::Order(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new OrderPrivate)
{
    loadFromJson(json);
}


Order::Order(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new OrderPrivate)
{
    loadFromJson(json);
}


Order::~Order()
{
}


QString Order::id() const { Q_D(const Order); return d->id; }

void Order::setId(const QString &nId)
{
    Q_D(Order); 
    if (nId != d->id) {
        d->id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << d->id;
#endif
        Q_EMIT idChanged(id());
    }
}




QString Order::referenceId() const { Q_D(const Order); return d->referenceId; }

void Order::setReferenceId(const QString &nReferenceId)
{
    Q_D(Order); 
    if (nReferenceId != d->referenceId) {
        d->referenceId = nReferenceId;
#ifdef QT_DEBUG
        qDebug() << "Changed referenceId to" << d->referenceId;
#endif
        Q_EMIT referenceIdChanged(referenceId());
    }
}




PaymentAmount *Order::amount() const { Q_D(const Order); return d->amount; }

void Order::setAmount(PaymentAmount *nAmount)
{
    Q_D(Order); 
    if (nAmount != d->amount) {
        d->amount = nAmount;
#ifdef QT_DEBUG
        qDebug() << "Changed amount to" << d->amount;
#endif
        Q_EMIT amountChanged(amount());
    }
}




PayPal::PaymentModeType Order::paymentMode() const { Q_D(const Order); return d->paymentMode; }

void Order::setPaymentMode(PayPal::PaymentModeType nPaymentMode)
{
    Q_D(Order); 
    if (nPaymentMode != d->paymentMode) {
        d->paymentMode = nPaymentMode;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentMode to" << d->paymentMode;
#endif
        Q_EMIT paymentModeChanged(paymentMode());
    }
}




PayPal::StateType Order::state() const { Q_D(const Order); return d->state; }

void Order::setState(PayPal::StateType nState)
{
    Q_D(Order); 
    if (nState != d->state) {
        d->state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << d->state;
#endif
        Q_EMIT stateChanged(state());
    }
}




PayPal::ReasonCode Order::reasonCode() const { Q_D(const Order); return d->reasonCode; }

void Order::setReasonCode(PayPal::ReasonCode nReasonCode)
{
    Q_D(Order); 
    if (nReasonCode != d->reasonCode) {
        d->reasonCode = nReasonCode;
#ifdef QT_DEBUG
        qDebug() << "Changed reasonCode to" << d->reasonCode;
#endif
        Q_EMIT reasonCodeChanged(reasonCode());
    }
}




PayPal::ProtectionEligibility Order::protectionEligibility() const { Q_D(const Order); return d->protectionEligibility; }

void Order::setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility)
{
    Q_D(Order); 
    if (nProtectionEligibility != d->protectionEligibility) {
        d->protectionEligibility = nProtectionEligibility;
#ifdef QT_DEBUG
        qDebug() << "Changed protectionEligibility to" << d->protectionEligibility;
#endif
        Q_EMIT protectionEligibilityChanged(protectionEligibility());
    }
}




QList<Geltan::PP::PayPal::ProtectionEligibilityType> Order::protectionEligibilityType() const { Q_D(const Order); return d->protectionEligibilityType; }

void Order::setProtectionEligibilityType(const QList<Geltan::PP::PayPal::ProtectionEligibilityType> &nProtectionEligibilityType)
{
    Q_D(Order); 
    if (nProtectionEligibilityType != d->protectionEligibilityType) {
        d->protectionEligibilityType = nProtectionEligibilityType;
#ifdef QT_DEBUG
        qDebug() << "Changed protectionEligibilityType to" << d->protectionEligibilityType;
#endif
        Q_EMIT protectionEligibilityTypeChanged(protectionEligibilityType());
    }
}




QString Order::parentPayment() const { Q_D(const Order); return d->parentPayment; }

void Order::setParentPayment(const QString &nParentPayment)
{
    Q_D(Order); 
    if (nParentPayment != d->parentPayment) {
        d->parentPayment = nParentPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed parentPayment to" << d->parentPayment;
#endif
        Q_EMIT parentPaymentChanged(parentPayment());
    }
}




FMFDetails *Order::fmfDetails() const { Q_D(const Order); return d->fmfDetails; }

void Order::setFmfDetails(FMFDetails *nFmfDetails)
{
    Q_D(Order); 
    if (nFmfDetails != d->fmfDetails) {
        d->fmfDetails = nFmfDetails;
#ifdef QT_DEBUG
        qDebug() << "Changed fmfDetails to" << d->fmfDetails;
#endif
        Q_EMIT fmfDetailsChanged(fmfDetails());
    }
}




QDateTime Order::createTime() const { Q_D(const Order); return d->createTime; }

void Order::setCreateTime(const QDateTime &nCreateTime)
{
    Q_D(Order); 
    if (nCreateTime != d->createTime) {
        d->createTime = nCreateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed createTime to" << d->createTime;
#endif
        Q_EMIT createTimeChanged(createTime());
    }
}




QDateTime Order::updateTime() const { Q_D(const Order); return d->updateTime; }

void Order::setUpdateTime(const QDateTime &nUpdateTime)
{
    Q_D(Order); 
    if (nUpdateTime != d->updateTime) {
        d->updateTime = nUpdateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed updateTime to" << d->updateTime;
#endif
        Q_EMIT updateTimeChanged(updateTime());
    }
}




QList<Link*> Order::links() const { Q_D(const Order); return d->links; }

void Order::setLinks(const QList<Link*> &nLinks)
{
    Q_D(Order); 
    if (nLinks != d->links) {
        d->links = nLinks;
#ifdef QT_DEBUG
        qDebug() << "Changed links to" << d->links;
#endif
        Q_EMIT linksChanged(links());
    }
}



QUrl Order::getLinkURL(const QString &rel) const
{
    const Link *l = getLink(rel);
    if (l) {
        return l->href();
    } else {
        return QUrl();
    }
}



Link* Order::getLink(const QString &rel) const
{
    Q_D(const Order);

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




void Order::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void Order::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Order);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    setId(json.value(QStringLiteral("id")).toString());

    setReferenceId(json.value(QStringLiteral("reference_id")).toString());

    const QJsonObject ao = json.value(QStringLiteral("amount")).toObject();
    PaymentAmount *oldAo = amount();
    if (!ao.isEmpty()) {
        if (oldAo) {
            oldAo->loadFromJson(ao);
        } else {
            setAmount(new PaymentAmount(ao, this));
        }
    } else {
        setAmount(nullptr);
        delete oldAo;
    }


    setPaymentMode(em->paymentModeTypeTokenToEnum(json.value(QStringLiteral("payment_mode")).toString()));

    setState(em->stateTypeTokenToEnum(json.value(QStringLiteral("state")).toString()));

    setReasonCode(em->reasonCodeTokenToEnum(json.value(QStringLiteral("reason_code")).toString()));

    setProtectionEligibility(em->protectionEligibilityTokenToEnum(json.value(QStringLiteral("protection_eligibility")).toString()));

    const QString pets = json.value(QStringLiteral("protection_eligibility_type")).toString();
    if (!pets.isEmpty()) {
        QList<Geltan::PP::PayPal::ProtectionEligibilityType> petList;
        const QStringList petsList = pets.split(QChar(','));
        petList.reserve(petsList.size());
        for (const QString &pet : petsList) {
            petList.append(em->protectionEligibilityTypeTokenToEnum(pet));
        }
        setProtectionEligibilityType(petList);
    } else {
        setProtectionEligibilityType(QList<Geltan::PP::PayPal::ProtectionEligibilityType>());
    }

    setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    const QJsonObject fmfo = json.value(QStringLiteral("fmf_details")).toObject();
    FMFDetails *oldFmf = fmfDetails();
    if (!fmfo.isEmpty()) {
        if (oldFmf) {
            oldFmf->loadFromJson(fmfo);
        } else {
            setFmfDetails(new FMFDetails(fmfo, this));
        }
    } else {
        setFmfDetails(nullptr);
        delete oldFmf;
    }

    const QString ct = json.value(QStringLiteral("create_time")).toString();
    if (!ct.isEmpty()) {
        setCreateTime(QDateTime::fromString(ct, Qt::ISODate));
    } else {
        setCreateTime(QDateTime());
    }

    const QString ut = json.value(QStringLiteral("update_time")).toString();
    if (!ut.isEmpty()) {
        setUpdateTime(QDateTime::fromString(ut, Qt::ISODate));
    } else {
        setUpdateTime(QDateTime());
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
