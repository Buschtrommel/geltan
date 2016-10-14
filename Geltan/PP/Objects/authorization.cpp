/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/authorization.cpp
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

#include "authorization_p.h"
#include <Geltan/PP/Objects/paymentamount.h>
#include <Geltan/PP/Objects/fmfdetails.h>
#include <Geltan/PP/Objects/link.h>
#include <Geltan/PP/ppenumsmap.h>
#include <QJsonDocument>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Authorization::Authorization(QObject *parent) :
    QObject(parent), d_ptr(new AuthorizationPrivate(this))
{
}


Authorization::Authorization(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new AuthorizationPrivate(this))
{
    loadFromJson(json);
}


Authorization::Authorization(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new AuthorizationPrivate(this))
{
    loadFromJson(json);
}


Authorization::~Authorization()
{
}


QString Authorization::id() const { Q_D(const Authorization); return d->id; }






PaymentAmount *Authorization::amount() const { Q_D(const Authorization); return d->amount; }

void Authorization::setAmount(PaymentAmount *nAmount)
{
    Q_D(Authorization); 
    if (nAmount != d->amount) {
        d->amount = nAmount;
#ifdef QT_DEBUG
        qDebug() << "Changed amount to" << d->amount;
#endif
        Q_EMIT amountChanged(amount());
    }
}




PayPal::PaymentModeType Authorization::paymentMode() const { Q_D(const Authorization); return d->paymentMode; }






PayPal::StateType Authorization::state() const { Q_D(const Authorization); return d->state; }






PayPal::ReasonCode Authorization::reasonCode() const { Q_D(const Authorization); return d->reasonCode; }






PayPal::ProtectionEligibility Authorization::protectionEligibility() const { Q_D(const Authorization); return d->protectionEligibility; }






QList<PayPal::ProtectionEligibilityType> Authorization::protectionEligibilityType() const { Q_D(const Authorization); return d->protectionEligibilityType; }






FMFDetails *Authorization::fmfDetails() const { Q_D(const Authorization); return d->fmfDetails; }






QString Authorization::parentPayment() const { Q_D(const Authorization); return d->parentPayment; }






QDateTime Authorization::validUntil() const { Q_D(const Authorization); return d->validUntil; }






QDateTime Authorization::createTime() const { Q_D(const Authorization); return d->createTime; }






QDateTime Authorization::updateTime() const { Q_D(const Authorization); return d->updateTime; }






QString Authorization::referenceId() const { Q_D(const Authorization); return d->referenceId; }






QString Authorization::receiptId() const { Q_D(const Authorization); return d->receiptId; }






QList<Link*> Authorization::links() const { Q_D(const Authorization); return d->links; }





QUrl Authorization::getLinkURL(const QString &rel) const
{
    const Link *l = getLink(rel);
    if (l) {
        return l->href();
    } else {
        return QUrl();
    }
}



Link* Authorization::getLink(const QString &rel) const
{
    Q_D(const Authorization);

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




QVariantMap Authorization::toVariant()
{
    Q_D(Authorization);

    QVariantMap map;

    if (amount()) {
        d->addMapToVariantMap(&map, QStringLiteral("amount"), amount()->toVariant());
    }

    return map;
}



QJsonObject Authorization::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}




void Authorization::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void Authorization::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Authorization);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    d->setId(json.value(QStringLiteral("id")).toString());

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

    d->setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    const QString vu = json.value(QStringLiteral("valid_until")).toString();
    if (!vu.isEmpty()) {
        d->setValidUntil(QDateTime::fromString(vu, Qt::ISODate));
    } else {
        d->setValidUntil(QDateTime());
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

    d->setReferenceId(json.value(QStringLiteral("reference_id")).toString());

    d->setReceiptId(json.value(QStringLiteral("receipt_id")).toString());

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
