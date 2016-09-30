/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * executepayment.cpp
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

#include "executepayment_p.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>
#include "Objects/paymentamount.h"

using namespace Geltan;
using namespace PP;

ExecutePayment::ExecutePayment(QObject *parent) : PPBase(*new ExecutePaymentPrivate, parent)
{
    Q_D(ExecutePayment);
    d->payment = nullptr;
    setNetworkOperation(QNetworkAccessManager::PostOperation);
    setExpectedType(PPBase::Object);
    addRequestHeader(QByteArrayLiteral("Content-Type"), QByteArrayLiteral("application/json"));
}


ExecutePayment::ExecutePayment(ExecutePaymentPrivate &dd, QObject *parent) : PPBase(dd, parent)
{

}



ExecutePayment::~ExecutePayment()
{

}



void ExecutePayment::call()
{
    if (payment()) {
        setPaymentId(payment()->id());
    }

    setApiPath(QStringLiteral("/v1/payments/payment/%1/execute/").arg(paymentId()));

    setError(nullptr);
    setInOperation(true);
    setAuthentication();

    QJsonObject root;
    root.insert(QStringLiteral("payer_id"), QJsonValue(payerId()));

    if (!transactions().isEmpty()) {
        QJsonArray trArr;
        const QList<Transaction*> trs = transactions();
        for (Transaction *t : trs) {
            if (t->amount()) {
                QJsonObject to;
                to.insert(QStringLiteral("amount"), QJsonValue(t->amount()->toJsonObject()));
                trArr.append(to);
            } else {
                setError(new Error(Error::InputError, tr("In order to update a transaction, a PaymentAmount object has to be specified."), Error::Warning, QString(), this));
            }
        }
        root.insert(QStringLiteral("transactions"), QJsonValue(trArr));
    }

    setPayload(QJsonDocument(root).toJson());

    sendRequest();
}



void ExecutePayment::call(const QString &paymentId, const QString &payerId)
{
    setPaymentId(paymentId);
    setPayerId(payerId);

    call();
}


void ExecutePayment::call(const QUrl &returnUrl)
{
    if (!returnUrl.isValid() || !returnUrl.hasQuery()) {
        setError(new Error(Error::InputError, tr("Invalid return URL."), Error::Critical, returnUrl.toString(), this));
        return;
    }

    QUrlQuery q(returnUrl);

    call(q.queryItemValue(QStringLiteral("paymentId")), q.queryItemValue(QStringLiteral("PayerID")));
}



void ExecutePayment::successCallBack()
{
    if (payment()) {
        payment()->loadFromJson(jsonResult());
    } else {
        setPayment(new Payment(jsonResult(), this));
    }

    setInOperation(false);
    Q_EMIT succeeded();
}



void ExecutePayment::errorCallBack()
{
    setInOperation(false);
    Q_EMIT failed();
}




bool ExecutePayment::checkInput()
{
    if (paymentId().isEmpty()) {
        setError(new Error(Error::InputError, tr("You have to set a payment ID in order to execute a payment."), Error::Critical, QString(), this));
        return false;
    }

    if (payerId().isEmpty()) {
        setError(new Error(Error::InputError, tr("You have to set a payer ID in order to execute a payment."), Error::Critical, QString(), this));
        return false;
    }

    return true;
}



bool ExecutePayment::checkOutput()
{
    if (PPBase::checkOutput()) {
        return true;
    } else{
        return false;
    }
}



Payment *ExecutePayment::payment() const { Q_D(const ExecutePayment); return d->payment; }

void ExecutePayment::setPayment(Payment *nPayment)
{
    Q_D(ExecutePayment);
    if (nPayment != d->payment) {
        d->payment = nPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed payment to" << d->payment;
#endif
        Q_EMIT paymentChanged(payment());
    }
}




QString ExecutePayment::payerId() const { Q_D(const ExecutePayment); return d->payerId; }

void ExecutePayment::setPayerId(const QString &nPayerId)
{
    Q_D(ExecutePayment);
    if (nPayerId != d->payerId) {
        d->payerId = nPayerId;
#ifdef QT_DEBUG
        qDebug() << "Changed payerId to" << d->payerId;
#endif
        Q_EMIT payerIdChanged(payerId());
    }
}




QString ExecutePayment::paymentId() const { Q_D(const ExecutePayment); return d->paymentId; }

void ExecutePayment::setPaymentId(const QString &nPaymentId)
{
    Q_D(ExecutePayment);
    if (nPaymentId != d->paymentId) {
        d->paymentId = nPaymentId;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentId to" << d->paymentId;
#endif
        Q_EMIT paymentIdChanged(paymentId());
    }
}




QList<Transaction*> ExecutePayment::transactions() const { Q_D(const ExecutePayment); return d->transactions; }

void ExecutePayment::setTransactions(const QList<Transaction*> &nTransactions)
{
    Q_D(ExecutePayment);
    if (nTransactions != d->transactions) {
        d->transactions = nTransactions;
#ifdef QT_DEBUG
        qDebug() << "Changed transactions to" << d->transactions;
#endif
        Q_EMIT transactionsChanged(transactions());
    }
}
