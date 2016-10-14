/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/authorization_p.h
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

#ifndef AUTHORIZATION_P_H
#define AUTHORIZATION_P_H

#include "authorization.h"
#include "ppobjectsbase_p.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {


class AuthorizationPrivate : public PPObjectsBasePrivate
{
public:
    AuthorizationPrivate(Authorization *parent) :
        q_ptr(parent),
        amount(nullptr),
        paymentMode(PayPal::NoPaymentMode),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode),
        protectionEligibility(PayPal::NoProtectionEligibility),
        fmfDetails(nullptr)
    {}

    ~AuthorizationPrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }


    /*!
     * \brief Sets the ID of the authorization transaction.
     */
    void setId(const QString &nId)
    {
        if (nId != id) {
            Q_Q(Authorization);
            id = nId;
#ifdef QT_DEBUG
            qDebug() << "Changed id to" << id;
#endif
            Q_EMIT q->idChanged(id);
        }
    }


    /*!
     * \brief Sets the payment mode.
     */
    void setPaymentMode(PayPal::PaymentModeType nPaymentMode)
    {
        if (nPaymentMode != paymentMode) {
            Q_Q(Authorization);
            paymentMode = nPaymentMode;
#ifdef QT_DEBUG
            qDebug() << "Changed paymentMode to" << paymentMode;
#endif
            Q_EMIT q->paymentModeChanged(paymentMode);
        }
    }


    /*!
     * \brief Sets the state of the authorization.
     */
    void setState(PayPal::StateType nState)
    {
        if (nState != state) {
            Q_Q(Authorization);
            state = nState;
#ifdef QT_DEBUG
            qDebug() << "Changed state to" << state;
#endif
            Q_EMIT q->stateChanged(state);
        }
    }


    /*!
     * \brief Sets the reason code for an authorizatin state of \c pending.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode)
    {
        if (nReasonCode != reasonCode) {
            Q_Q(Authorization);
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
            Q_Q(Authorization);
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
    void setProtectionEligibilityType(const QList<PayPal::ProtectionEligibilityType> &nProtectionEligibilityType)
    {
        if (nProtectionEligibilityType != protectionEligibilityType) {
            Q_Q(Authorization);
            protectionEligibilityType = nProtectionEligibilityType;
#ifdef QT_DEBUG
            qDebug() << "Changed protectionEligibilityType to" << protectionEligibilityType;
#endif
            Q_EMIT q->protectionEligibilityTypeChanged(protectionEligibilityType);
        }
    }


    /*!
     * \brief Sets the details of Fraud Management Filter (FMF).
     */
    void setFmfDetails(FMFDetails *nFmfDetails)
    {
        if (nFmfDetails != fmfDetails) {
            Q_Q(Authorization);
            fmfDetails = nFmfDetails;
#ifdef QT_DEBUG
            qDebug() << "Changed fmfDetails to" << fmfDetails;
#endif
            Q_EMIT q->fmfDetailsChanged(fmfDetails);
        }
    }


    /*!
     * \brief Sets the ID of a parent payment.
     */
    void setParentPayment(const QString &nParentPayment)
    {
        if (nParentPayment != parentPayment) {
            Q_Q(Authorization);
            parentPayment = nParentPayment;
#ifdef QT_DEBUG
            qDebug() << "Changed parentPayment to" << parentPayment;
#endif
            Q_EMIT q->parentPaymentChanged(parentPayment);
        }
    }


    /*!
     * \brief Sets the expiration time and date.
     */
    void setValidUntil(const QDateTime &nValidUntil)
    {
        if (nValidUntil != validUntil) {
            Q_Q(Authorization);
            validUntil = nValidUntil;
#ifdef QT_DEBUG
            qDebug() << "Changed validUntil to" << validUntil;
#endif
            Q_EMIT q->validUntilChanged(validUntil);
        }
    }


    /*!
     * \brief Sets the date and time of the authorization.
     */
    void setCreateTime(const QDateTime &nCreateTime)
    {
        if (nCreateTime != createTime) {
            Q_Q(Authorization);
            createTime = nCreateTime;
#ifdef QT_DEBUG
            qDebug() << "Changed createTime to" << createTime;
#endif
            Q_EMIT q->createTimeChanged(createTime);
        }
    }


    /*!
     * \brief Sets the date and time the resource was last updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime)
    {
        if (nUpdateTime != updateTime) {
            Q_Q(Authorization);
            updateTime = nUpdateTime;
#ifdef QT_DEBUG
            qDebug() << "Changed updateTime to" << updateTime;
#endif
            Q_EMIT q->updateTimeChanged(updateTime);
        }
    }


    /*!
     * \brief Sets the ID of the purchase or transaction unit corresponding to this authorization.
     */
    void setReferenceId(const QString &nReferenceId)
    {
        if (nReferenceId != referenceId) {
            Q_Q(Authorization);
            referenceId = nReferenceId;
#ifdef QT_DEBUG
            qDebug() << "Changed referenceId to" << referenceId;
#endif
            Q_EMIT q->referenceIdChanged(referenceId);
        }
    }


    /*!
     * \brief Sets the 16 digit number payment identification number.
     */
    void setReceiptId(const QString &nReceiptId)
    {
        if (nReceiptId != receiptId) {
            Q_Q(Authorization);
            receiptId = nReceiptId;
#ifdef QT_DEBUG
            qDebug() << "Changed receiptId to" << receiptId;
#endif
            Q_EMIT q->receiptIdChanged(receiptId);
        }
    }
    /*!
     * \brief Sets the HATEOS links related to this call.
     */
    void setLinks(const QList<Link*> &nLinks)
    {
        if (nLinks != links) {
            Q_Q(Authorization);
            links = nLinks;
    #ifdef QT_DEBUG
            qDebug() << "Changed links to" << links;
    #endif
            Q_EMIT q->linksChanged(links);
        }
    }



    Authorization * const q_ptr;
    Q_DECLARE_PUBLIC(Authorization)
    QString id;
    PaymentAmount *amount;
    PayPal::PaymentModeType paymentMode;
    PayPal::StateType state;
    PayPal::ReasonCode reasonCode;
    PayPal::ProtectionEligibility protectionEligibility;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType;
    FMFDetails *fmfDetails;
    QString parentPayment;
    QDateTime validUntil;
    QDateTime createTime;
    QDateTime updateTime;
    QString referenceId;
    QString receiptId;
    QList<Link*> links;
};

}
}

#endif // AUTHORIZATION_P_H
