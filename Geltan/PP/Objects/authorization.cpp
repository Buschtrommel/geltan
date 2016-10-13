/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * authorization.cpp
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
    QObject(parent), d_ptr(new AuthorizationPrivate)
{
}


Authorization::Authorization(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new AuthorizationPrivate)
{
    loadFromJson(json);
}


Authorization::Authorization(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new AuthorizationPrivate)
{
    loadFromJson(json);
}


Authorization::~Authorization()
{
}


QString Authorization::id() const { Q_D(const Authorization); return d->id; }

void Authorization::setId(const QString &nId)
{
    Q_D(Authorization); 
    if (nId != d->id) {
        d->id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << d->id;
#endif
        Q_EMIT idChanged(id());
    }
}




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

void Authorization::setPaymentMode(PayPal::PaymentModeType nPaymentMode)
{
    Q_D(Authorization); 
    if (nPaymentMode != d->paymentMode) {
        d->paymentMode = nPaymentMode;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentMode to" << d->paymentMode;
#endif
        Q_EMIT paymentModeChanged(paymentMode());
    }
}




PayPal::StateType Authorization::state() const { Q_D(const Authorization); return d->state; }

void Authorization::setState(PayPal::StateType nState)
{
    Q_D(Authorization); 
    if (nState != d->state) {
        d->state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << d->state;
#endif
        Q_EMIT stateChanged(state());
    }
}




PayPal::ReasonCode Authorization::reasonCode() const { Q_D(const Authorization); return d->reasonCode; }

void Authorization::setReasonCode(PayPal::ReasonCode nReasonCode)
{
    Q_D(Authorization); 
    if (nReasonCode != d->reasonCode) {
        d->reasonCode = nReasonCode;
#ifdef QT_DEBUG
        qDebug() << "Changed reasonCode to" << d->reasonCode;
#endif
        Q_EMIT reasonCodeChanged(reasonCode());
    }
}




PayPal::ProtectionEligibility Authorization::protectionEligibility() const { Q_D(const Authorization); return d->protectionEligibility; }

void Authorization::setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility)
{
    Q_D(Authorization); 
    if (nProtectionEligibility != d->protectionEligibility) {
        d->protectionEligibility = nProtectionEligibility;
#ifdef QT_DEBUG
        qDebug() << "Changed protectionEligibility to" << d->protectionEligibility;
#endif
        Q_EMIT protectionEligibilityChanged(protectionEligibility());
    }
}




QList<PayPal::ProtectionEligibilityType> Authorization::protectionEligibilityType() const { Q_D(const Authorization); return d->protectionEligibilityType; }

void Authorization::setProtectionEligibilityType(const QList<PayPal::ProtectionEligibilityType> &nProtectionEligibilityType)
{
    Q_D(Authorization); 
    if (nProtectionEligibilityType != d->protectionEligibilityType) {
        d->protectionEligibilityType = nProtectionEligibilityType;
#ifdef QT_DEBUG
        qDebug() << "Changed protectionEligibilityType to" << d->protectionEligibilityType;
#endif
        Q_EMIT protectionEligibilityTypeChanged(protectionEligibilityType());
    }
}




FMFDetails *Authorization::fmfDetails() const { Q_D(const Authorization); return d->fmfDetails; }

void Authorization::setFmfDetails(FMFDetails *nFmfDetails)
{
    Q_D(Authorization); 
    if (nFmfDetails != d->fmfDetails) {
        d->fmfDetails = nFmfDetails;
#ifdef QT_DEBUG
        qDebug() << "Changed fmfDetails to" << d->fmfDetails;
#endif
        Q_EMIT fmfDetailsChanged(fmfDetails());
    }
}




QString Authorization::parentPayment() const { Q_D(const Authorization); return d->parentPayment; }

void Authorization::setParentPayment(const QString &nParentPayment)
{
    Q_D(Authorization); 
    if (nParentPayment != d->parentPayment) {
        d->parentPayment = nParentPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed parentPayment to" << d->parentPayment;
#endif
        Q_EMIT parentPaymentChanged(parentPayment());
    }
}




QDateTime Authorization::validUntil() const { Q_D(const Authorization); return d->validUntil; }

void Authorization::setValidUntil(const QDateTime &nValidUntil)
{
    Q_D(Authorization); 
    if (nValidUntil != d->validUntil) {
        d->validUntil = nValidUntil;
#ifdef QT_DEBUG
        qDebug() << "Changed validUntil to" << d->validUntil;
#endif
        Q_EMIT validUntilChanged(validUntil());
    }
}




QDateTime Authorization::createTime() const { Q_D(const Authorization); return d->createTime; }

void Authorization::setCreateTime(const QDateTime &nCreateTime)
{
    Q_D(Authorization); 
    if (nCreateTime != d->createTime) {
        d->createTime = nCreateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed createTime to" << d->createTime;
#endif
        Q_EMIT createTimeChanged(createTime());
    }
}




QDateTime Authorization::updateTime() const { Q_D(const Authorization); return d->updateTime; }

void Authorization::setUpdateTime(const QDateTime &nUpdateTime)
{
    Q_D(Authorization); 
    if (nUpdateTime != d->updateTime) {
        d->updateTime = nUpdateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed updateTime to" << d->updateTime;
#endif
        Q_EMIT updateTimeChanged(updateTime());
    }
}




QString Authorization::referenceId() const { Q_D(const Authorization); return d->referenceId; }

void Authorization::setReferenceId(const QString &nReferenceId)
{
    Q_D(Authorization); 
    if (nReferenceId != d->referenceId) {
        d->referenceId = nReferenceId;
#ifdef QT_DEBUG
        qDebug() << "Changed referenceId to" << d->referenceId;
#endif
        Q_EMIT referenceIdChanged(referenceId());
    }
}




QString Authorization::receiptId() const { Q_D(const Authorization); return d->receiptId; }

void Authorization::setReceiptId(const QString &nReceiptId)
{
    Q_D(Authorization); 
    if (nReceiptId != d->receiptId) {
        d->receiptId = nReceiptId;
#ifdef QT_DEBUG
        qDebug() << "Changed receiptId to" << d->receiptId;
#endif
        Q_EMIT receiptIdChanged(receiptId());
    }
}




QList<Link*> Authorization::links() const { Q_D(const Authorization); return d->links; }

void Authorization::setLinks(const QList<Link*> &nLinks)
{
    Q_D(Authorization); 
    if (nLinks != d->links) {
        d->links = nLinks;
#ifdef QT_DEBUG
        qDebug() << "Changed links to" << d->links;
#endif
        Q_EMIT linksChanged(links());
    }
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

    setId(json.value(QStringLiteral("id")).toString());

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

    setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    const QString vu = json.value(QStringLiteral("valid_until")).toString();
    if (!vu.isEmpty()) {
        setValidUntil(QDateTime::fromString(vu, Qt::ISODate));
    } else {
        setValidUntil(QDateTime());
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

    setReferenceId(json.value(QStringLiteral("reference_id")).toString());

    setReceiptId(json.value(QStringLiteral("receipt_id")).toString());

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
