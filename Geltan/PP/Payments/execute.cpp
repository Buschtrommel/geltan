/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/execute.cpp
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

#include "execute_p.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>
#include <Geltan/PP/Objects/paymentamount.h>

using namespace Geltan;
using namespace PP;
using namespace Payments;

Execute::Execute(QObject *parent) : PPBase(*new ExecutePrivate, parent)
{
    Q_D(Execute);
    d->payment = nullptr;
    setNetworkOperation(QNetworkAccessManager::PostOperation);
    setExpectedType(PPBase::Object);
    addRequestHeader(QByteArrayLiteral("Content-Type"), QByteArrayLiteral("application/json"));
}


Execute::Execute(ExecutePrivate &dd, QObject *parent) : PPBase(dd, parent)
{

}




void Execute::call()
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



void Execute::call(const QString &paymentId, const QString &payerId)
{
    setPaymentId(paymentId);
    setPayerId(payerId);

    call();
}


void Execute::call(const QUrl &returnUrl)
{
    if (!returnUrl.isValid() || !returnUrl.hasQuery()) {
        setError(new Error(Error::InputError, tr("Invalid return URL."), Error::Critical, returnUrl.toString(), this));
        return;
    }

    QUrlQuery q(returnUrl);

    call(q.queryItemValue(QStringLiteral("paymentId")), q.queryItemValue(QStringLiteral("PayerID")));
}



void Execute::successCallBack()
{
    if (payment()) {
        payment()->loadFromJson(jsonResult());
    } else {
        setPayment(new Payment(jsonResult(), this));
    }

    setInOperation(false);
    Q_EMIT succeeded();
}



void Execute::errorCallBack()
{
    setInOperation(false);
    Q_EMIT failed();
}




bool Execute::checkInput()
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



bool Execute::checkOutput()
{
    if (PPBase::checkOutput()) {
        return true;
    } else{
        return false;
    }
}



Payment *Execute::payment() const { Q_D(const Execute); return d->payment; }

void Execute::setPayment(Payment *nPayment)
{
    Q_D(Execute);
    if (nPayment != d->payment) {
        d->payment = nPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed payment to" << d->payment;
#endif
        Q_EMIT paymentChanged(payment());
    }
}




QString Execute::payerId() const { Q_D(const Execute); return d->payerId; }

void Execute::setPayerId(const QString &nPayerId)
{
    Q_D(Execute);
    if (nPayerId != d->payerId) {
        d->payerId = nPayerId;
#ifdef QT_DEBUG
        qDebug() << "Changed payerId to" << d->payerId;
#endif
        Q_EMIT payerIdChanged(payerId());
    }
}




QString Execute::paymentId() const { Q_D(const Execute); return d->paymentId; }

void Execute::setPaymentId(const QString &nPaymentId)
{
    Q_D(Execute);
    if (nPaymentId != d->paymentId) {
        d->paymentId = nPaymentId;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentId to" << d->paymentId;
#endif
        Q_EMIT paymentIdChanged(paymentId());
    }
}




QList<Transaction*> Execute::transactions() const { Q_D(const Execute); return d->transactions; }

void Execute::setTransactions(const QList<Transaction*> &nTransactions)
{
    Q_D(Execute);
    if (nTransactions != d->transactions) {
        d->transactions = nTransactions;
#ifdef QT_DEBUG
        qDebug() << "Changed transactions to" << d->transactions;
#endif
        Q_EMIT transactionsChanged(transactions());
    }
}
