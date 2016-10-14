/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/get.cpp
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

#include "get_p.h"

using namespace Geltan;
using namespace PP;
using namespace Payments;

Get::Get(QObject *parent) : PPBase(*new GetPrivate, parent)
{
    Q_D(Get);
    d->payment = nullptr;
    setNetworkOperation(QNetworkAccessManager::GetOperation);
    setExpectedType(PPBase::Object);
    addRequestHeader(QByteArrayLiteral("Content-Type"), QByteArrayLiteral("application/json"));
}


Get::Get(GetPrivate &dd, QObject *parent) : PPBase(dd, parent)
{

}



void Get::call()
{
    Q_D(Get);

    setError(nullptr);
    setInOperation(true);
    setAuthentication();

    if (payment()) {
        Payment *op = payment();
        d->payment = nullptr;
        Q_EMIT paymentChanged(payment());
        if (op->parent() == this) {
            delete op;
        }
    }

    setApiPath(QStringLiteral("/v1/payments/payment/%1").arg(paymentId()));

    sendRequest();
}



void Get::call(const QString &paymentId)
{
    setPaymentId(paymentId);
    call();
}



void Get::successCallBack()
{
    Q_D(Get);

    d->payment = new Payment(jsonResult(), this);
    Q_EMIT paymentChanged(payment());

    setInOperation(false);
    Q_EMIT succeeded();
}



void Get::errorCallBack()
{
    setInOperation(false);
    Q_EMIT failed();
}



bool Get::checkInput()
{
    if (paymentId().isEmpty()) {
        setError(new Error(Error::InputError, tr("You have to set a payment ID in order to request payment details."), Error::Critical, QString(), this));
        return false;
    }

    return true;
}



bool Get::checkOutput()
{
    if (PPBase::checkOutput()) {
        return true;
    } else {
        return false;
    }
}


QString Get::paymentId() const { Q_D(const Get); return d->paymentId; }

void Get::setPaymentId(const QString &nPaymentId)
{
    Q_D(Get);
    if (nPaymentId != d->paymentId) {
        d->paymentId = nPaymentId;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentId to" << d->paymentId;
#endif
        Q_EMIT paymentIdChanged(paymentId());
    }
}


Payment *Get::payment() const { Q_D(const Get); return d->payment; }
