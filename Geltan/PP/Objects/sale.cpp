/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/sale.cpp
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
    QObject(parent), d_ptr(new SalePrivate(this))
{
}



Sale::Sale(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new SalePrivate(this))
{
    loadFromJson(json);
}



Sale::Sale(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new SalePrivate(this))
{
    loadFromJson(json);
}


Sale::~Sale()
{
}


QString Sale::id() const { Q_D(const Sale); return d->id; }






QString Sale::purchaseUnitReferenceId() const { Q_D(const Sale); return d->purchaseUnitReferenceId; }






PaymentAmount *Sale::amount() const { Q_D(const Sale); return d->amount; }






PayPal::PaymentModeType Sale::paymentMode() const { Q_D(const Sale); return d->paymentMode; }






PayPal::StateType Sale::state() const { Q_D(const Sale); return d->state; }






PayPal::ReasonCode Sale::reasonCode() const { Q_D(const Sale); return d->reasonCode; }






PayPal::ProtectionEligibility Sale::protectionEligibility() const { Q_D(const Sale); return d->protectionEligibility; }






QList<PayPal::ProtectionEligibilityType> Sale::protectionEligibilityType() const { Q_D(const Sale); return d->protectionEligibilityType; }






QDateTime Sale::clearingTime() const { Q_D(const Sale); return d->clearingTime; }






Sale::PaymentHoldStatus Sale::paymentHoldStatus() const { Q_D(const Sale); return d->paymentHoldStatus; }






QStringList Sale::paymentHoldReasons() const { Q_D(const Sale); return d->paymentHoldReasons; }






Currency *Sale::transactionFee() const { Q_D(const Sale); return d->transactionFee; }






Currency *Sale::receivableAmount() const { Q_D(const Sale); return d->receivableAmount; }






float Sale::exchangeRate() const { Q_D(const Sale); return d->exchangeRate; }






FMFDetails *Sale::fmfDetails() const { Q_D(const Sale); return d->fmfDetails; }






QString Sale::receiptId() const { Q_D(const Sale); return d->receiptId; }






QString Sale::parentPayment() const { Q_D(const Sale); return d->parentPayment; }






ProcessorResponse *Sale::processorResponse() const { Q_D(const Sale); return d->processorResponse; }






QString Sale::billingAgreementId() const { Q_D(const Sale); return d->billingAgreementId; }






QDateTime Sale::createTime() const { Q_D(const Sale); return d->createTime; }






QDateTime Sale::updateTime() const { Q_D(const Sale); return d->updateTime; }






QList<Link*> Sale::links() const { Q_D(const Sale); return d->links; }





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

    d->setId(json.value(QStringLiteral("id")).toString());

    d->setPurchaseUnitReferenceId(json.value(QStringLiteral("purchase_unit_reference_id")).toString());

    const QJsonObject ao = json.value(QStringLiteral("amount")).toObject();
    PaymentAmount *oldAo = amount();
    if (!ao.isEmpty()) {
        if (oldAo) {
            oldAo->loadFromJson(ao);
        } else {
            d->setAmount(new PaymentAmount(ao, this));
        }
    } else {
        d->setAmount(nullptr);
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

    const QString scs = json.value(QStringLiteral("clearing_time")).toString();
    if (!scs.isEmpty()) {
        d->setClearingTime(QDateTime::fromString(scs, Qt::ISODate));
    } else {
        d->setClearingTime(QDateTime());
    }

    const QString phs = json.value(QStringLiteral("payment_hold_status")).toString();
    if (phs == QLatin1String("HELD")) {
        d->setPaymentHoldStatus(HELD);
    } else {
        d->setPaymentHoldStatus(NO_PAYMENT_HOLD_STATUS);
    }

    const QJsonArray phrs = json.value(QStringLiteral("payment_hold_reasons")).toArray();
    if (!phrs.isEmpty()) {
        QStringList phrList;
        QJsonArray::const_iterator i = phrs.constBegin();
        while (i != phrs.constEnd()) {
            phrList.append(i->toString());
            ++i;
        }
        d->setPaymentHoldReasons(phrList);
    } else {
        d->setPaymentHoldReasons(QStringList());
    }

    const QJsonObject tf = json.value(QStringLiteral("transaction_fee")).toObject();
    Currency *oldTf = transactionFee();
    if (!tf.isEmpty()) {
        if (oldTf) {
            oldTf->loadFromJson(tf);
        } else {
            d->setTransactionFee(new Currency(tf, this));
        }
    } else {
        d->setTransactionFee(nullptr);
        delete oldTf;
    }

    const QJsonObject ra = json.value(QStringLiteral("receivable_amount")).toObject();
    Currency *oldRa = receivableAmount();
    if (!ra.isEmpty()) {
        if (oldRa) {
            oldRa->loadFromJson(ra);
        } else {
            d->setReceivableAmount(new Currency(ra, this));
        }
    } else {
        d->setReceivableAmount(nullptr);
        delete oldRa;
    }

    d->setExchangeRate(json.value(QStringLiteral("exchange_rate")).toString().toFloat());

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

    d->setReceiptId(json.value(QStringLiteral("receipt_id")).toString());

    d->setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    const QJsonObject pro = json.value(QStringLiteral("processor_response")).toObject();
    ProcessorResponse *oldPro = processorResponse();
    if (!pro.isEmpty()) {
        if (oldPro) {
            oldPro->loadFromJson(pro);
        } else {
            d->setProcessorResponse(new ProcessorResponse(pro, this));
        }
    } else {
        d->setProcessorResponse(nullptr);
        delete oldPro;
    }


    d->setBillingAgreementId(json.value(QStringLiteral("billing_agreement_id")).toString());

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
