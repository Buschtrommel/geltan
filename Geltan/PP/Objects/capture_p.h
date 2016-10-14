/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/capture_p.h
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

#ifndef CAPTURE_P_H
#define CAPTURE_P_H

#include "capture.h"
#include "ppobjectsbase_p.h"
#include "../ppenumsmap.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {


class CapturePrivate : public PPObjectsBasePrivate
{
public:
    CapturePrivate(Capture *parent) :
        q_ptr(parent),
        amount(nullptr),
        isFinalCapture(false),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode),
        transactionFee(nullptr)
    {}

    ~CapturePrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    /*!
     * \brief Sets the ID of the capture transaction.
     */
    void setId(const QString &nId)
    {
        if (id != nId) {
            Q_Q(Capture);
            id = nId;
#ifdef QT_DEBUG
            qDebug() << "Changed id to" << id;
#endif
            Q_EMIT q->idChanged(id);
        }
    }


    /*!
     * \brief Sets the state of the capture transaction.
     */
    void setState(PayPal::StateType nState)
    {
        if (state != nState) {
            Q_Q(Capture);
            state = nState;
#ifdef QT_DEBUG
            qDebug() << "Changed state to" << state;
#endif
            Q_EMIT q->stateChanged(state);
        }
    }

    /*!
     * \brief Sets the reason code if state is \c pending or \c reversed.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode)
    {
        if (reasonCode != nReasonCode) {
            Q_Q(Capture);
            reasonCode = nReasonCode;
#ifdef QT_DEBUG
            qDebug() << "Changed reasonCode to" << reasonCode;
#endif
            Q_EMIT q->reasonCodeChanged(reasonCode);
        }
    }

    /*!
     * \brief Set the ID of the payment on which this transaction is based.
     */
    void setParentPayment(const QString &nParentPayment)
    {
        if (parentPayment != nParentPayment) {
            Q_Q(Capture);
            parentPayment = nParentPayment;
#ifdef QT_DEBUG
            qDebug() << "Changed parentPayment to" << parentPayment;
#endif
            Q_EMIT q->parentPaymentChanged(parentPayment);
        }
    }

    /*!
     * \brief Sets the date and time of capture.
     */
    void setCreateTime(const QDateTime &nCreateTime)
    {
        if (createTime != nCreateTime) {
            Q_Q(Capture);
            createTime = nCreateTime;
#ifdef QT_DEBUG
            qDebug() << "Changed createTime to" << createTime;
#endif
            Q_EMIT q->createTimeChanged(createTime);
        }
    }

    /*!
     * \brief Sets the date and time when the resource was last updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime)
    {
        if (updateTime != nUpdateTime) {
            Q_Q(Capture);
            updateTime = nUpdateTime;
#ifdef QT_DEBUG
            qDebug() << "Changed updateTime to" << updateTime;
#endif
            Q_EMIT q->updateTimeChanged(updateTime);
        }
    }

    /*!
     * \brief Sets the HATEOAS links of the capture for related calls.
     */
    void setLinks(const QList<Link*> &nLinks)
    {
        if (links != nLinks) {
            Q_Q(Capture);
            links = nLinks;
#ifdef QT_DEBUG
            qDebug() << "Changed links to" << links;
#endif
            Q_EMIT q->linksChanged(links);
        }
    }

    Capture * const q_ptr;
    Q_DECLARE_PUBLIC(Capture)
    QString id;
    PaymentAmount *amount;
    bool isFinalCapture;
    PayPal::StateType state;
    PayPal::ReasonCode reasonCode;
    QString parentPayment;
    QString invoiceNumber;
    Currency *transactionFee;
    QDateTime createTime;
    QDateTime updateTime;
    QList<Link*> links;
};

}
}

#endif // CAPTURE_P_H
