/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/order.cpp
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
    QObject(parent), d_ptr(new OrderPrivate(this))
{
}



Order::Order(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new OrderPrivate(this))
{
    loadFromJson(json);
}


Order::Order(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new OrderPrivate(this))
{
    loadFromJson(json);
}


Order::~Order()
{
}


QString Order::id() const { Q_D(const Order); return d->id; }






QString Order::referenceId() const { Q_D(const Order); return d->referenceId; }






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






PayPal::StateType Order::state() const { Q_D(const Order); return d->state; }






PayPal::ReasonCode Order::reasonCode() const { Q_D(const Order); return d->reasonCode; }






PayPal::ProtectionEligibility Order::protectionEligibility() const { Q_D(const Order); return d->protectionEligibility; }






QList<Geltan::PP::PayPal::ProtectionEligibilityType> Order::protectionEligibilityType() const { Q_D(const Order); return d->protectionEligibilityType; }






QString Order::parentPayment() const { Q_D(const Order); return d->parentPayment; }






FMFDetails *Order::fmfDetails() const { Q_D(const Order); return d->fmfDetails; }






QDateTime Order::createTime() const { Q_D(const Order); return d->createTime; }






QDateTime Order::updateTime() const { Q_D(const Order); return d->updateTime; }






QList<Link*> Order::links() const { Q_D(const Order); return d->links; }





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

    d->setId(json.value(QStringLiteral("id")).toString());

    d->setReferenceId(json.value(QStringLiteral("reference_id")).toString());

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


    d->setPaymentMode(em->paymentModeTypeTokenToEnum(json.value(QStringLiteral("payment_mode")).toString()));

    d->setState(em->stateTypeTokenToEnum(json.value(QStringLiteral("state")).toString()));

    d->setReasonCode(em->reasonCodeTokenToEnum(json.value(QStringLiteral("reason_code")).toString()));

    d->setProtectionEligibility(em->protectionEligibilityTokenToEnum(json.value(QStringLiteral("protection_eligibility")).toString()));

    const QString pets = json.value(QStringLiteral("protection_eligibility_type")).toString();
    if (!pets.isEmpty()) {
        QList<Geltan::PP::PayPal::ProtectionEligibilityType> petList;
        const QStringList petsList = pets.split(QChar(','));
        petList.reserve(petsList.size());
        for (const QString &pet : petsList) {
            petList.append(em->protectionEligibilityTypeTokenToEnum(pet));
        }
        d->setProtectionEligibilityType(petList);
    } else {
        d->setProtectionEligibilityType(QList<Geltan::PP::PayPal::ProtectionEligibilityType>());
    }

    d->setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    const QJsonObject fmfo = json.value(QStringLiteral("fmf_details")).toObject();
    FMFDetails *oldFmf = fmfDetails();
    if (!fmfo.isEmpty()) {
        if (oldFmf) {
            oldFmf->loadFromJson(fmfo);
        } else {
            d->setFmfDetails(new FMFDetails(fmfo, this));
        }
    } else {
        d->setFmfDetails(nullptr);
        delete oldFmf;
    }

    const QString ct = json.value(QStringLiteral("create_time")).toString();
    if (!ct.isEmpty()) {
        d->setCreateTime(QDateTime::fromString(ct, Qt::ISODate));
    } else {
        d->setCreateTime(QDateTime());
    }

    const QString ut = json.value(QStringLiteral("update_time")).toString();
    if (!ut.isEmpty()) {
        d->setUpdateTime(QDateTime::fromString(ut, Qt::ISODate));
    } else {
        d->setUpdateTime(QDateTime());
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
        d->setLinks(linksToAdd);
    }
}
