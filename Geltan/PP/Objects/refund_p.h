/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/refund_p.h
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

#ifndef REFUND_P_H
#define REFUND_P_H

#include "refund.h"
#include "ppobjectsbase_p.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {


class RefundPrivate : public PPObjectsBasePrivate
{
public:
    RefundPrivate(Refund *parent) :
        q_ptr(parent),
        amount(nullptr),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode)
    {
        id.reserve(17);
    }

    ~RefundPrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    /*!
     * \brief Sets the ID of the refund transaction.
     */
    void setId(const QString &nId)
    {
        if (nId != id) {
            Q_Q(Refund);
            id = nId;
    #ifdef QT_DEBUG
            qDebug() << "Changed id to" << id;
    #endif
            Q_EMIT q->idChanged(id);
        }
    }


    /*!
     * \brief Sets the state of the refund.
     */
    void setState(PayPal::StateType nState)
    {
        if (nState != state) {
            Q_Q(Refund);
            state = nState;
    #ifdef QT_DEBUG
            qDebug() << "Changed state to" << state;
    #endif
            Q_EMIT q->stateChanged(state);
        }
    }


    /*!
     * \brief Sets the ID of the Sale transaction being refunded.
     */
    void setSaleId(const QString &nSaleId)
    {
        if (nSaleId != saleId) {
            Q_Q(Refund);
            saleId = nSaleId;
    #ifdef QT_DEBUG
            qDebug() << "Changed saleId to" << saleId;
    #endif
            Q_EMIT q->saleIdChanged(saleId);
        }
    }


    /*!
     * \brief Sets the ID of the Capture transaction being refunded.
     */
    void setCaptureId(const QString &nCaptureId)
    {
        if (nCaptureId != captureId) {
            Q_Q(Refund);
            captureId = nCaptureId;
    #ifdef QT_DEBUG
            qDebug() << "Changed captureId to" << captureId;
    #endif
            Q_EMIT q->captureIdChanged(captureId);
        }
    }


    /*!
     * \brief Sets the ID of the payment resource on which this transaction is based.
     */
    void setParentPayment(const QString &nParentPayment)
    {
        if (nParentPayment != parentPayment) {
            Q_Q(Refund);
            parentPayment = nParentPayment;
    #ifdef QT_DEBUG
            qDebug() << "Changed parentPayment to" << parentPayment;
    #endif
            Q_EMIT q->parentPaymentChanged(parentPayment);
        }
    }


    /*!
     * \brief Sets date and time the refund was created.
     */
    void setCreateTime(const QDateTime &nCreateTime)
    {
        if (nCreateTime != createTime) {
            Q_Q(Refund);
            createTime = nCreateTime;
    #ifdef QT_DEBUG
            qDebug() << "Changed createTime to" << createTime;
    #endif
            Q_EMIT q->createTimeChanged(createTime);
        }
    }


    /*!
     * \brief Sets date and time the refund was updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime)
    {
        if (nUpdateTime != updateTime) {
            Q_Q(Refund);
            updateTime = nUpdateTime;
    #ifdef QT_DEBUG
            qDebug() << "Changed updateTime to" << updateTime;
    #endif
            Q_EMIT q->updateTimeChanged(updateTime);
        }
    }


    /*!
     * \brief Sets the reason code if the state is pending.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode)
    {
        if (nReasonCode != reasonCode) {
            Q_Q(Refund);
            reasonCode = nReasonCode;
    #ifdef QT_DEBUG
            qDebug() << "Changed reasonCode to" << reasonCode;
    #endif
            Q_EMIT q->reasonCodeChanged(reasonCode);
        }
    }


    /*!
     * \brief Sets the list of HATEOAS links related to this call.
     */
    void setLinks(const QList<Link*> &nLinks)
    {
        if (nLinks != links) {
            Q_Q(Refund);
            links = nLinks;
    #ifdef QT_DEBUG
            qDebug() << "Changed links to" << links;
    #endif
            Q_EMIT q->linksChanged(links);
        }
    }



    Refund * const q_ptr;
    Q_DECLARE_PUBLIC(Refund)
    QString id;
    PaymentAmount *amount;
    PayPal::StateType state;
    QString reason;
    QString invoiceNumber;
    QString saleId;
    QString captureId;
    QString parentPayment;
    QString description;
    QDateTime createTime;
    QDateTime updateTime;
    PayPal::ReasonCode reasonCode;
    QList<Link*> links;
};

}
}

#endif // REFUND_P_H
