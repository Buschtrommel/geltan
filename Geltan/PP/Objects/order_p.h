/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/order_p.h
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

#ifndef ORDER_P_H
#define ORDER_P_H

#include "order.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {


class OrderPrivate
{
public:
    OrderPrivate(Order *parent) :
        q_ptr(parent),
        amount(nullptr),
        paymentMode(PayPal::NoPaymentMode),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode),
        protectionEligibility(PayPal::NoProtectionEligibility),
        fmfDetails(nullptr)
    {}

    ~OrderPrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    /*!
     * \brief Sets the identifier of the order transaction.
     */
    void setId(const QString &nId)
    {
        if (nId != id) {
            Q_Q(Order);
            id = nId;
    #ifdef QT_DEBUG
            qDebug() << "Changed id to" << id;
    #endif
            Q_EMIT q->idChanged(id);
        }
    }


    /*!
     * \brief Sets the reference id of the order transaction.
     */
    void setReferenceId(const QString &nReferenceId)
    {
        if (nReferenceId != referenceId) {
            Q_Q(Order);
            referenceId = nReferenceId;
    #ifdef QT_DEBUG
            qDebug() << "Changed referenceId to" << referenceId;
    #endif
            Q_EMIT q->referenceIdChanged(referenceId);
        }
    }


    /*!
     * \brief Sets the payment mode of the transaction.
     */
    void setPaymentMode(PayPal::PaymentModeType nPaymentMode)
    {
        if (nPaymentMode != paymentMode) {
            Q_Q(Order);
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
            Q_Q(Order);
            state = nState;
    #ifdef QT_DEBUG
            qDebug() << "Changed state to" << state;
    #endif
            Q_EMIT q->stateChanged(state);
        }
    }


    /*!
     * \brief Sets the reason code of the transaction.
     *
     * Only supported when the \a payment_mehtod is set to \c paypal.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode)
    {
        if (nReasonCode != reasonCode) {
            Q_Q(Order);
            reasonCode = nReasonCode;
    #ifdef QT_DEBUG
            qDebug() << "Changed reasonCode to" << reasonCode;
    #endif
            Q_EMIT q->reasonCodeChanged(reasonCode);
        }
    }


    /*!
     * \brief Sets the level of seller protection in force.
     */
    void setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility)
    {
        if (nProtectionEligibility != protectionEligibility) {
            Q_Q(Order);
            protectionEligibility = nProtectionEligibility;
    #ifdef QT_DEBUG
            qDebug() << "Changed protectionEligibility to" << protectionEligibility;
    #endif
            Q_EMIT q->protectionEligibilityChanged(protectionEligibility);
        }
    }


    /*!
     * \brief Sets the kind of seller protection in force.
     */
    void setProtectionEligibilityType(const QList<Geltan::PP::PayPal::ProtectionEligibilityType> &nProtectionEligibilityType)
    {
        if (nProtectionEligibilityType != protectionEligibilityType) {
            Q_Q(Order);
            protectionEligibilityType = nProtectionEligibilityType;
    #ifdef QT_DEBUG
            qDebug() << "Changed protectionEligibilityType to" << protectionEligibilityType;
    #endif
            Q_EMIT q->protectionEligibilityTypeChanged(protectionEligibilityType);
        }
    }


    /*!
     * \brief Sets the ID of the payment resource that this transaction is based on.
     */
    void setParentPayment(const QString &nParentPayment)
    {
        if (nParentPayment != parentPayment) {
            Q_Q(Order);
            parentPayment = nParentPayment;
    #ifdef QT_DEBUG
            qDebug() << "Changed parentPayment to" << parentPayment;
    #endif
            Q_EMIT q->parentPaymentChanged(parentPayment);
        }
    }


    /*!
     * \brief Sets the details of Fraud Management Filter.
     */
    void setFmfDetails(FMFDetails *nFmfDetails)
    {
        if (nFmfDetails != fmfDetails) {
            Q_Q(Order);
            fmfDetails = nFmfDetails;
    #ifdef QT_DEBUG
            qDebug() << "Changed fmfDetails to" << fmfDetails;
    #endif
            Q_EMIT q->fmfDetailsChanged(fmfDetails);
        }
    }


    /*!
     * \brief Sets the time the resource was created.
     */
    void setCreateTime(const QDateTime &nCreateTime)
    {
        if (nCreateTime != createTime) {
            Q_Q(Order);
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
            Q_Q(Order);
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
            Q_Q(Order);
            links = nLinks;
    #ifdef QT_DEBUG
            qDebug() << "Changed links to" << links;
    #endif
            Q_EMIT q->linksChanged(links);
        }
    }


    Order * const q_ptr;
    Q_DECLARE_PUBLIC(Order)
    QString id;
    QString referenceId;
    PaymentAmount *amount;
    PayPal::PaymentModeType paymentMode;
    PayPal::StateType state;
    PayPal::ReasonCode reasonCode;
    PayPal::ProtectionEligibility protectionEligibility;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType;
    QString parentPayment;
    FMFDetails *fmfDetails;
    QDateTime createTime;
    QDateTime updateTime;
    QList<Link*> links;
};

}
}

#endif // ORDER_P_H
