/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * sale.cpp
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

#include "sale_p.h"
#include <Geltan/PP/ppenums.h>
#include <Geltan/PP/Objects/paymentamount.h>
#include <Geltan/PP/Objects/currency.h>
#include <Geltan/PP/Objects/fmfdetails.h>
#include <Geltan/PP/Objects/processorresponse.h>
#include <Geltan/PP/Objects/link.h>
#include <QJsonDocument>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Sale::Sale(QObject *parent) :
    QObject(parent), d_ptr(new SalePrivate)
{
}



Sale::Sale(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new SalePrivate)
{
    loadFromJson(json);
}



Sale::Sale(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new SalePrivate)
{
    loadFromJson(json);
}


Sale::~Sale()
{
}


QString Sale::id() const { Q_D(const Sale); return d->id; }

void Sale::setId(const QString &nId)
{
    Q_D(Sale); 
    if (nId != d->id) {
        d->id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << d->id;
#endif
        Q_EMIT idChanged(id());
    }
}




QString Sale::purchaseUnitReferenceId() const { Q_D(const Sale); return d->purchaseUnitReferenceId; }

void Sale::setPurchaseUnitReferenceId(const QString &nPurchaseUnitReferenceId)
{
    Q_D(Sale); 
    if (nPurchaseUnitReferenceId != d->purchaseUnitReferenceId) {
        d->purchaseUnitReferenceId = nPurchaseUnitReferenceId;
#ifdef QT_DEBUG
        qDebug() << "Changed purchaseUnitReferenceId to" << d->purchaseUnitReferenceId;
#endif
        Q_EMIT purchaseUnitReferenceIdChanged(purchaseUnitReferenceId());
    }
}




PaymentAmount *Sale::amount() const { Q_D(const Sale); return d->amount; }

void Sale::setAmount(PaymentAmount *nAmount)
{
    Q_D(Sale); 
    if (nAmount != d->amount) {
        d->amount = nAmount;
#ifdef QT_DEBUG
        qDebug() << "Changed amount to" << d->amount;
#endif
        Q_EMIT amountChanged(amount());
    }
}




PayPal::PaymentModeType Sale::paymentMode() const { Q_D(const Sale); return d->paymentMode; }

void Sale::setPaymentMode(PayPal::PaymentModeType nPaymentMode)
{
    Q_D(Sale); 
    if (nPaymentMode != d->paymentMode) {
        d->paymentMode = nPaymentMode;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentMode to" << d->paymentMode;
#endif
        Q_EMIT paymentModeChanged(paymentMode());
    }
}




PayPal::StateType Sale::state() const { Q_D(const Sale); return d->state; }

void Sale::setState(PayPal::StateType nState)
{
    Q_D(Sale); 
    if (nState != d->state) {
        d->state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << d->state;
#endif
        Q_EMIT stateChanged(state());
    }
}




PayPal::ReasonCode Sale::reasonCode() const { Q_D(const Sale); return d->reasonCode; }

void Sale::setReasonCode(PayPal::ReasonCode nReasonCode)
{
    Q_D(Sale); 
    if (nReasonCode != d->reasonCode) {
        d->reasonCode = nReasonCode;
#ifdef QT_DEBUG
        qDebug() << "Changed reasonCode to" << d->reasonCode;
#endif
        Q_EMIT reasonCodeChanged(reasonCode());
    }
}




PayPal::ProtectionEligibility Sale::protectionEligibility() const { Q_D(const Sale); return d->protectionEligibility; }

void Sale::setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility)
{
    Q_D(Sale); 
    if (nProtectionEligibility != d->protectionEligibility) {
        d->protectionEligibility = nProtectionEligibility;
#ifdef QT_DEBUG
        qDebug() << "Changed protectionEligibility to" << d->protectionEligibility;
#endif
        Q_EMIT protectionEligibilityChanged(protectionEligibility());
    }
}




QList<PayPal::ProtectionEligibilityType> Sale::protectionEligibilityType() const { Q_D(const Sale); return d->protectionEligibilityType; }

void Sale::setProtectionEligibilityType(QList<PayPal::ProtectionEligibilityType> nProtectionEligibilityType)
{
    Q_D(Sale); 
    if (nProtectionEligibilityType != d->protectionEligibilityType) {
        d->protectionEligibilityType = nProtectionEligibilityType;
#ifdef QT_DEBUG
        qDebug() << "Changed protectionEligibilityType to" << d->protectionEligibilityType;
#endif
        Q_EMIT protectionEligibilityTypeChanged(protectionEligibilityType());
    }
}




QDateTime Sale::clearingTime() const { Q_D(const Sale); return d->clearingTime; }

void Sale::setClearingTime(const QDateTime &nClearingTime)
{
    Q_D(Sale); 
    if (nClearingTime != d->clearingTime) {
        d->clearingTime = nClearingTime;
#ifdef QT_DEBUG
        qDebug() << "Changed clearingTime to" << d->clearingTime;
#endif
        Q_EMIT clearingTimeChanged(clearingTime());
    }
}




Sale::PaymentHoldStatus Sale::paymentHoldStatus() const { Q_D(const Sale); return d->paymentHoldStatus; }

void Sale::setPaymentHoldStatus(PaymentHoldStatus nPaymentHoldStatus)
{
    Q_D(Sale); 
    if (nPaymentHoldStatus != d->paymentHoldStatus) {
        d->paymentHoldStatus = nPaymentHoldStatus;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentHoldStatus to" << d->paymentHoldStatus;
#endif
        Q_EMIT paymentHoldStatusChanged(paymentHoldStatus());
    }
}




QStringList Sale::paymentHoldReasons() const { Q_D(const Sale); return d->paymentHoldReasons; }

void Sale::setPaymentHoldReasons(const QStringList &nPaymentHoldReasons)
{
    Q_D(Sale); 
    if (nPaymentHoldReasons != d->paymentHoldReasons) {
        d->paymentHoldReasons = nPaymentHoldReasons;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentHoldReasons to" << d->paymentHoldReasons;
#endif
        Q_EMIT paymentHoldReasonsChanged(paymentHoldReasons());
    }
}




Currency *Sale::transactionFee() const { Q_D(const Sale); return d->transactionFee; }

void Sale::setTransactionFee(Currency *nTransactionFee)
{
    Q_D(Sale); 
    if (nTransactionFee != d->transactionFee) {
        d->transactionFee = nTransactionFee;
#ifdef QT_DEBUG
        qDebug() << "Changed transactionFee to" << d->transactionFee;
#endif
        Q_EMIT transactionFeeChanged(transactionFee());
    }
}




Currency *Sale::receivableAmount() const { Q_D(const Sale); return d->receivableAmount; }

void Sale::setReceivableAmount(Currency *nReceivableAmount)
{
    Q_D(Sale); 
    if (nReceivableAmount != d->receivableAmount) {
        d->receivableAmount = nReceivableAmount;
#ifdef QT_DEBUG
        qDebug() << "Changed receivableAmount to" << d->receivableAmount;
#endif
        Q_EMIT receivableAmountChanged(receivableAmount());
    }
}




float Sale::exchangeRate() const { Q_D(const Sale); return d->exchangeRate; }

void Sale::setExchangeRate(float nExchangeRate)
{
    Q_D(Sale); 
    if (nExchangeRate != d->exchangeRate) {
        d->exchangeRate = nExchangeRate;
#ifdef QT_DEBUG
        qDebug() << "Changed exchangeRate to" << d->exchangeRate;
#endif
        Q_EMIT exchangeRateChanged(exchangeRate());
    }
}




FMFDetails *Sale::fmfDetails() const { Q_D(const Sale); return d->fmfDetails; }

void Sale::setFmfDetails(FMFDetails *nFmfDetails)
{
    Q_D(Sale); 
    if (nFmfDetails != d->fmfDetails) {
        d->fmfDetails = nFmfDetails;
#ifdef QT_DEBUG
        qDebug() << "Changed fmfDetails to" << d->fmfDetails;
#endif
        Q_EMIT fmfDetailsChanged(fmfDetails());
    }
}




QString Sale::receiptId() const { Q_D(const Sale); return d->receiptId; }

void Sale::setReceiptId(const QString &nReceiptId)
{
    Q_D(Sale); 
    if (nReceiptId != d->receiptId) {
        d->receiptId = nReceiptId;
#ifdef QT_DEBUG
        qDebug() << "Changed receiptId to" << d->receiptId;
#endif
        Q_EMIT receiptIdChanged(receiptId());
    }
}




QString Sale::parentPayment() const { Q_D(const Sale); return d->parentPayment; }

void Sale::setParentPayment(const QString &nParentPayment)
{
    Q_D(Sale); 
    if (nParentPayment != d->parentPayment) {
        d->parentPayment = nParentPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed parentPayment to" << d->parentPayment;
#endif
        Q_EMIT parentPaymentChanged(parentPayment());
    }
}




ProcessorResponse *Sale::processorResponse() const { Q_D(const Sale); return d->processorResponse; }

void Sale::setProcessorResponse(ProcessorResponse *nProcessorResponse)
{
    Q_D(Sale); 
    if (nProcessorResponse != d->processorResponse) {
        d->processorResponse = nProcessorResponse;
#ifdef QT_DEBUG
        qDebug() << "Changed processorResponse to" << d->processorResponse;
#endif
        Q_EMIT processorResponseChanged(processorResponse());
    }
}




QString Sale::billingAgreementId() const { Q_D(const Sale); return d->billingAgreementId; }

void Sale::setBillingAgreementId(const QString &nBillingAgreementId)
{
    Q_D(Sale); 
    if (nBillingAgreementId != d->billingAgreementId) {
        d->billingAgreementId = nBillingAgreementId;
#ifdef QT_DEBUG
        qDebug() << "Changed billingAgreementId to" << d->billingAgreementId;
#endif
        Q_EMIT billingAgreementIdChanged(billingAgreementId());
    }
}




QDateTime Sale::createTime() const { Q_D(const Sale); return d->createTime; }

void Sale::setCreateTime(const QDateTime &nCreateTime)
{
    Q_D(Sale); 
    if (nCreateTime != d->createTime) {
        d->createTime = nCreateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed createTime to" << d->createTime;
#endif
        Q_EMIT createTimeChanged(createTime());
    }
}




QDateTime Sale::updateTime() const { Q_D(const Sale); return d->updateTime; }

void Sale::setUpdateTime(const QDateTime &nUpdateTime)
{
    Q_D(Sale); 
    if (nUpdateTime != d->updateTime) {
        d->updateTime = nUpdateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed updateTime to" << d->updateTime;
#endif
        Q_EMIT updateTimeChanged(updateTime());
    }
}




QList<Link*> Sale::links() const { Q_D(const Sale); return d->links; }

void Sale::setLinks(const QList<Link*> &nLinks)
{
    Q_D(Sale); 
    if (nLinks != d->links) {
        d->links = nLinks;
#ifdef QT_DEBUG
        qDebug() << "Changed links to" << d->links;
#endif
        Q_EMIT linksChanged(links());
    }
}



QUrl Sale::getLinkURL(const QString &rel) const
{
    const Link *l = getLink(rel);
    if (l) {
        return l->href();
    } else {
        return QUrl();
    }
}



Link* Sale::getLink(const QString &rel) const
{
    Q_D(const Sale);

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




void Sale::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}




void Sale::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Sale);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    setId(json.value(QStringLiteral("id")).toString());

    setPurchaseUnitReferenceId(json.value(QStringLiteral("purchase_unit_reference_id")).toString());

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
        for (const QString &pet : petsList) {
            petList.append(em->protectionEligibilityTypeTokenToEnum(pet));
        }
        setProtectionEligibilityType(petList);
    } else {
        setProtectionEligibilityType(QList<Geltan::PP::PayPal::ProtectionEligibilityType>());
    }

    const QString scs = json.value(QStringLiteral("clearing_time")).toString();
    if (!scs.isEmpty()) {
        setClearingTime(QDateTime::fromString(scs, Qt::ISODate));
    } else {
        setClearingTime(QDateTime());
    }

    const QString phs = json.value(QStringLiteral("payment_hold_status")).toString();
    if (phs == QLatin1String("HELD")) {
        setPaymentHoldStatus(Held);
    } else {
        setPaymentHoldStatus(NoPaymentHoldStatus);
    }

    const QJsonArray phrs = json.value(QStringLiteral("payment_hold_reasons")).toArray();
    if (!phrs.isEmpty()) {
        QStringList phrList;
        QJsonArray::const_iterator i = phrs.constBegin();
        while (i != phrs.constEnd()) {
            phrList.append(i->toString());
            ++i;
        }
        setPaymentHoldReasons(phrList);
    } else {
        setPaymentHoldReasons(QStringList());
    }

    const QJsonObject tf = json.value(QStringLiteral("transaction_fee")).toObject();
    Currency *oldTf = transactionFee();
    if (!tf.isEmpty()) {
        if (oldTf) {
            oldTf->loadFromJson(tf);
        } else {
            setTransactionFee(new Currency(tf, this));
        }
    } else {
        setTransactionFee(nullptr);
        delete oldTf;
    }

    const QJsonObject ra = json.value(QStringLiteral("receivable_amount")).toObject();
    Currency *oldRa = receivableAmount();
    if (!ra.isEmpty()) {
        if (oldRa) {
            oldRa->loadFromJson(ra);
        } else {
            setReceivableAmount(new Currency(ra, this));
        }
    } else {
        setReceivableAmount(nullptr);
        delete oldRa;
    }

    setExchangeRate(json.value(QStringLiteral("exchange_rate")).toString().toFloat());

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

    setReceiptId(json.value(QStringLiteral("receipt_id")).toString());

    setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    const QJsonObject pro = json.value(QStringLiteral("processor_response")).toObject();
    ProcessorResponse *oldPro = processorResponse();
    if (!pro.isEmpty()) {
        if (oldPro) {
            oldPro->loadFromJson(pro);
        } else {
            setProcessorResponse(new ProcessorResponse(pro, this));
        }
    } else {
        setProcessorResponse(nullptr);
        delete oldPro;
    }


    setBillingAgreementId(json.value(QStringLiteral("billing_agreement_id")).toString());

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
