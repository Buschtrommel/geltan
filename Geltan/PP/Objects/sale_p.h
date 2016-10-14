/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/sale.h
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

#ifndef SALE_P_H
#define SALE_P_H

#include "sale.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {


class SalePrivate
{
public:
    SalePrivate(Sale *parent) :
        q_ptr(parent),
        amount(nullptr),
        paymentMode(PayPal::NoPaymentMode),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode),
        protectionEligibility(PayPal::NoProtectionEligibility),
        paymentHoldStatus(Sale::NO_PAYMENT_HOLD_STATUS),
        transactionFee(nullptr),
        receivableAmount(nullptr),
        exchangeRate(0.0),
        fmfDetails(nullptr),
        processorResponse(nullptr)
    {}

    ~SalePrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }


    /*!
     * \brief Sets the identifier for the sale transaction.
     */
    void setId(const QString &nId)
    {
        if (nId != id) {
            Q_Q(Sale);
            id = nId;
    #ifdef QT_DEBUG
            qDebug() << "Changed id to" << id;
    #endif
            Q_EMIT q->idChanged(id);
        }
    }


    /*!
     * \brief Sets the identiefier to the purchase or transaction unit corresponding to this sale transaction.
     */
    void setPurchaseUnitReferenceId(const QString &nPurchaseUnitReferenceId)
    {
        if (nPurchaseUnitReferenceId != purchaseUnitReferenceId) {
            Q_Q(Sale);
            purchaseUnitReferenceId = nPurchaseUnitReferenceId;
    #ifdef QT_DEBUG
            qDebug() << "Changed purchaseUnitReferenceId to" << purchaseUnitReferenceId;
    #endif
            Q_EMIT q->purchaseUnitReferenceIdChanged(purchaseUnitReferenceId);
        }
    }


    /*!
     * \brief Sets the payment amount with break-ups.
     */
    void setAmount(PaymentAmount *nAmount)
    {
        if (nAmount != amount) {
            Q_Q(Sale);
            amount = nAmount;
    #ifdef QT_DEBUG
            qDebug() << "Changed amount to" << amount;
    #endif
            Q_EMIT q->amountChanged(amount);
        }
    }


    /*!
     * \brief Specifies payment mode of the transaction.
     *
     * Only supported if the \c payment_method is set to \c paypal.
     */
    void setPaymentMode(PayPal::PaymentModeType nPaymentMode)
    {
        if (nPaymentMode != paymentMode) {
            Q_Q(Sale);
            paymentMode = nPaymentMode;
    #ifdef QT_DEBUG
            qDebug() << "Changed paymentMode to" << paymentMode;
    #endif
            Q_EMIT q->paymentModeChanged(paymentMode);
        }
    }


    /*!
     * \brief Sets the state of the transaction.
     */
    void setState(PayPal::StateType nState)
    {
        if (nState != state) {
            Q_Q(Sale);
            state = nState;
    #ifdef QT_DEBUG
            qDebug() << "Changed state to" << state;
    #endif
            Q_EMIT q->stateChanged(state);
        }
    }


    /*!
     * \brief Sets the reason code for the transaction if the state is Pending or Reserved.
     *
     * Only supported if the \c payment_method is set to \c paypal.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode)
    {
        if (nReasonCode != reasonCode) {
            Q_Q(Sale);
            reasonCode = nReasonCode;
    #ifdef QT_DEBUG
            qDebug() << "Changed reasonCode to" << reasonCode;
    #endif
            Q_EMIT q->reasonCodeChanged(reasonCode);
        }
    }


    /*!
     * \brief Sets the level  of seller protection in force for the transaction.
     *
     * Only supported if the \c payment_method is set to \c paypal.
     */
    void setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility)
    {
        if (nProtectionEligibility != protectionEligibility) {
            Q_Q(Sale);
            protectionEligibility = nProtectionEligibility;
    #ifdef QT_DEBUG
            qDebug() << "Changed protectionEligibility to" << protectionEligibility;
    #endif
            Q_EMIT q->protectionEligibilityChanged(protectionEligibility);
        }
    }


    /*!
     * \brief Sets the kind of seller protection in force for the transaction.
     *
     * It is returned only when protectionEligibility is \a ELIGIBLE or \a PARTIALLY_ELIGIBLE. Only supported when the \c payment_method is set to \c paypal.
     */
    void setProtectionEligibilityType(const QList<PayPal::ProtectionEligibilityType> &nProtectionEligibilityType)
    {
        if (nProtectionEligibilityType != protectionEligibilityType) {
            Q_Q(Sale);
            protectionEligibilityType = nProtectionEligibilityType;
    #ifdef QT_DEBUG
            qDebug() << "Changed protectionEligibilityType to" << protectionEligibilityType;
    #endif
            Q_EMIT q->protectionEligibilityTypeChanged(protectionEligibilityType);
        }
    }


    /*!
     * \brief Sets the expected clearing time for eCheck Transactions.
     *
     * Returned when payment is made with eCheck. Only supported when the \c payment_method is set to \c paypal.
     */
    void setClearingTime(const QDateTime &nClearingTime)
    {
        if (nClearingTime != clearingTime) {
            Q_Q(Sale);
            clearingTime = nClearingTime;
    #ifdef QT_DEBUG
            qDebug() << "Changed clearingTime to" << clearingTime;
    #endif
            Q_EMIT q->clearingTimeChanged(clearingTime);
        }
    }


    /*!
     * \brief Sets the status of the Recipient Fund.
     *
     * For now, it will be returned only when fund status is held
     */
    void setPaymentHoldStatus(Sale::PaymentHoldStatus nPaymentHoldStatus)
    {
        if (nPaymentHoldStatus != paymentHoldStatus) {
            Q_Q(Sale);
            paymentHoldStatus = nPaymentHoldStatus;
    #ifdef QT_DEBUG
            qDebug() << "Changed paymentHoldStatus to" << paymentHoldStatus;
    #endif
            Q_EMIT q->paymentHoldStatusChanged(paymentHoldStatus);
        }
    }


    /*!
     * \brief Sets reasons for PayPal holding recipient fund.
     *
     * It is set only if payment hold status is held.
     */
    void setPaymentHoldReasons(const QStringList &nPaymentHoldReasons)
    {
        if (nPaymentHoldReasons != paymentHoldReasons) {
            Q_Q(Sale);
            paymentHoldReasons = nPaymentHoldReasons;
    #ifdef QT_DEBUG
            qDebug() << "Changed paymentHoldReasons to" << paymentHoldReasons;
    #endif
            Q_EMIT q->paymentHoldReasonsChanged(paymentHoldReasons);
        }
    }


    /*!
     * \brief Sets the transaction fee charged by PayPal for this transaction.
     */
    void setTransactionFee(Currency *nTransactionFee)
    {
        if (nTransactionFee != transactionFee) {
            Q_Q(Sale);
            transactionFee = nTransactionFee;
    #ifdef QT_DEBUG
            qDebug() << "Changed transactionFee to" << transactionFee;
    #endif
            Q_EMIT q->transactionFeeChanged(transactionFee);
        }
    }


    /*!
     * \brief Sets the net amount the merchant receives for this transaction in their receivable currency.
     *
     * Returned only in cross-currency use cases where a merchant bills a buyer in a non-primary currency for that buyer.
     */
    void setReceivableAmount(Currency *nReceivableAmount)
    {
        if (nReceivableAmount != receivableAmount) {
            Q_Q(Sale);
            receivableAmount = nReceivableAmount;
    #ifdef QT_DEBUG
            qDebug() << "Changed receivableAmount to" << receivableAmount;
    #endif
            Q_EMIT q->receivableAmountChanged(receivableAmount);
        }
    }


    /*!
     * \brief Sets the exchange rate applied for this transaction.
     *
     * Returned only in cross-currency use cases where a merchant bills a buyer in a non-primary currency for that buyer.
     */
    void setExchangeRate(float nExchangeRate)
    {
        if (nExchangeRate != exchangeRate) {
            Q_Q(Sale);
            exchangeRate = nExchangeRate;
    #ifdef QT_DEBUG
            qDebug() << "Changed exchangeRate to" << exchangeRate;
    #endif
            Q_EMIT q->exchangeRateChanged(exchangeRate);
        }
    }


    /*!
     * \brief Sets the Fraud Management Filter (FMF) details applied for the payment that could result in accept, deny, or pending action.
     *
     * Returned in a payment response only if the merchant has enabled FMF in the profile settings and one
     * of the fraud filters was triggered based on those settings.
     * See \link https://paypal.github.io/docs/classic/fmf/integration-guide/FMFSummary/ Fraud Management Filters Summary \endlink for more information.
     */
    void setFmfDetails(FMFDetails *nFmfDetails)
    {
        if (nFmfDetails != fmfDetails) {
            Q_Q(Sale);
            fmfDetails = nFmfDetails;
    #ifdef QT_DEBUG
            qDebug() << "Changed fmfDetails to" << fmfDetails;
    #endif
            Q_EMIT q->fmfDetailsChanged(fmfDetails);
        }
    }



    /*!
     * \brief Sets the receipt id.
     *
     * Receipt id is a payment identification number returned for guest users to identify the payment.
     */
    void setReceiptId(const QString &nReceiptId)
    {
        if (nReceiptId != receiptId) {
            Q_Q(Sale);
            receiptId = nReceiptId;
    #ifdef QT_DEBUG
            qDebug() << "Changed receiptId to" << receiptId;
    #endif
            Q_EMIT q->receiptIdChanged(receiptId);
        }
    }


    /*!
     * \brief Sets the ID of the payment resource on which this transaction is based.
     */
    void setParentPayment(const QString &nParentPayment)
    {
        if (nParentPayment != parentPayment) {
            Q_Q(Sale);
            parentPayment = nParentPayment;
    #ifdef QT_DEBUG
            qDebug() << "Changed parentPayment to" << parentPayment;
    #endif
            Q_EMIT q->parentPaymentChanged(parentPayment);
        }
    }


    /*!
     * \brief Sets the response codes returned by the processor concerning the submitted payment.
     *
     * Only supported when the \c payment_method is set to \c credit_card.
     */
    void setProcessorResponse(ProcessorResponse *nProcessorResponse)
    {
        if (nProcessorResponse != processorResponse) {
            Q_Q(Sale);
            processorResponse = nProcessorResponse;
    #ifdef QT_DEBUG
            qDebug() << "Changed processorResponse to" << processorResponse;
    #endif
            Q_EMIT q->processorResponseChanged(processorResponse);
        }
    }


    /*!
     * \brief Sets the ID of the billing agreement used as reference to execute this transaction.
     */
    void setBillingAgreementId(const QString &nBillingAgreementId)
    {
        if (nBillingAgreementId != billingAgreementId) {
            Q_Q(Sale);
            billingAgreementId = nBillingAgreementId;
    #ifdef QT_DEBUG
            qDebug() << "Changed billingAgreementId to" << billingAgreementId;
    #endif
            Q_EMIT q->billingAgreementIdChanged(billingAgreementId);
        }
    }


    /*!
     * \brief Sets the time of sale.
     */
    void setCreateTime(const QDateTime &nCreateTime)
    {
        if (nCreateTime != createTime) {
            Q_Q(Sale);
            createTime = nCreateTime;
    #ifdef QT_DEBUG
            qDebug() << "Changed createTime to" << createTime;
    #endif
            Q_EMIT q->createTimeChanged(createTime);
        }
    }


    /*!
     * \brief Sets the time the resource was last updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime)
    {
        if (nUpdateTime != updateTime) {
            Q_Q(Sale);
            updateTime = nUpdateTime;
    #ifdef QT_DEBUG
            qDebug() << "Changed updateTime to" << updateTime;
    #endif
            Q_EMIT q->updateTimeChanged(updateTime);
        }
    }


    /*!
     * \brief Sets the HATEOAS links related to this call.
     */
    void setLinks(const QList<Link*> &nLinks)
    {
        if (nLinks != links) {
            Q_Q(Sale);
            links = nLinks;
    #ifdef QT_DEBUG
            qDebug() << "Changed links to" << links;
    #endif
            Q_EMIT q->linksChanged(links);
        }
    }


    Sale * const q_ptr;
    Q_DECLARE_PUBLIC(Sale)
    QString id;
    QString purchaseUnitReferenceId;
    PaymentAmount *amount;
    PayPal::PaymentModeType paymentMode;
    PayPal::StateType state;
    PayPal::ReasonCode reasonCode;
    PayPal::ProtectionEligibility protectionEligibility;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType;
    QDateTime clearingTime;
    Sale::PaymentHoldStatus paymentHoldStatus;
    QStringList paymentHoldReasons;
    Currency *transactionFee;
    Currency *receivableAmount;
    float exchangeRate;
    FMFDetails *fmfDetails;
    QString receiptId;
    QString parentPayment;
    ProcessorResponse *processorResponse;
    QString billingAgreementId;
    QDateTime createTime;
    QDateTime updateTime;
    QList<Link*> links;
};

}
}

#endif // SALE_P_H
