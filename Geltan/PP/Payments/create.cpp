/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/create.cpp
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

#include "create_p.h"
#include <Geltan/PP/Objects/payer.h>
#include <Geltan/PP/Objects/redirecturls.h>
#include <Geltan/PP/Objects/transaction.h>
#include <Geltan/PP/Objects/itemlist.h>
#include <Geltan/PP/Objects/item.h>
#include <Geltan/PP/Objects/paymentamount.h>
#include <Geltan/PP/Objects/details.h>
#include <QJsonObject>
#include <QJsonArray>

using namespace Geltan;
using namespace PP;
using namespace Payments;

Create::Create(QObject *parent) : PPBase(*new CreatePrivate, parent)
{
    Q_D(Create);
    d->payment = nullptr;
    setApiPath(QStringLiteral("/v1/payments/payment"));
    setNetworkOperation(QNetworkAccessManager::PostOperation);
    setExpectedType(PPBase::Object);
    addRequestHeader(QByteArrayLiteral("Content-Type"), QByteArrayLiteral("application/json"));
}


Create::Create(CreatePrivate &dd, QObject *parent) : PPBase(dd, parent)
{

}



void Create::call()
{
    if (!payment()) {
        setError(new Error(Error::InputError, tr("No valid payment data available."), Error::Critical, QString(), this));
        return;
    }

    setError(nullptr);
    setInOperation(true);
    setAuthentication();

    setPayload(payment()->toJson());

    sendRequest();
}



void Create::successCallBack()
{
    if (payment()) {
        payment()->loadFromJson(jsonResult());
    } else {
        setPayment(new Payment(jsonResult(), this));
    }

    setInOperation(false);
    Q_EMIT succeeded();
}



void Create::errorCallBack()
{
    setInOperation(false);
    Q_EMIT failed();
}



bool Create::checkInput()
{
    Q_D(Create);

    if (!d->payment) {
        setError(new Error(Error::InputError, tr("No valid payment data available."), Error::Critical, QString(), this));
        return false;
    }

    if (d->token.isEmpty()) {
        setError(new Error(Error::InputError, tr("No valid authentication token set."), Error::Critical, QString(), this));
        return false;
    }

    if (d->tokenType == PayPal::NoTokenType) {
        setError(new Error(Error::InputError, tr("No valid token type set."), Error::Critical, QString(), this));
        return false;
    }

    if (d->payment->intent() == Payment::NoIntent) {
        setError(new Error(Error::InputError, tr("No valid payment intent set."), Error::Critical, QString(), this));
        return false;
    }

    if (!d->payment->payer()) {
        setError(new Error(Error::InputError, tr("No valid Payer object available on the Payment object."), Error::Critical, QString(), this));
        return false;
    }

    const QList<Transaction*> trs = d->payment->transactions();
    if (trs.isEmpty()) {
        setError(new Error(Error::InputError, tr("You have to specify at least one transaction with total amount, currency and description."), Error::Critical, QString(), this));
        return false;
    }

    if ((d->payment->intent() == Payment::Sale) && (d->payment->payer()->paymentMethod() == PayPal::PayPalWallet)) {

        if (!d->payment->redirectUrls()) {
            setError(new Error(Error::InputError, tr("In order to accept a PayPal payment, you have to provide valid redirect URLs."), Error::Critical, QString(), this));
            return false;
        }

        if (!d->payment->redirectUrls()->isValid()) {
            setError(new Error(Error::InputError, tr("In order to accept a PayPal payment, you have to provide valid redirect URLs."), Error::Critical, QString(), this));
            return false;
        }

        for (Transaction *t : trs) {
            if (!t->referenceId().isEmpty()) {
                setError(new Error(Error::InputError, tr("Reference ID is not allowed when accepting PayPal payments."), Error::Critical, QString(), this));
                return false;
            }
        }

    }

    if ((d->payment->intent() == Payment::Sale) && (d->payment->payer()->paymentMethod() == PayPal::CreditCard)) {

        if (!d->payment->payer()->fundingInstruments().isEmpty()) {
            setError(new Error(Error::InputError, tr("No valid credit card data available."), Error::Critical, QString(), this));
            return false;
        }

    }

    for (Transaction *t : trs) {

        if (!t->amount()) {
            setError(new Error(Error::InputError, tr("You have to specify the amount of the transaction."), Error::Critical, QString(), this));
            return false;
        }

        if (!t->amount()->valid()) {
            setError(new Error(Error::InputError, tr("The amount data is not valid. Maybe data is missing or the values do not sum up as expected."), Error::Critical, QString(), this));
            return false;
        }

        if (t->amount()->details()) {
            if (d->payment->payer()->paymentMethod() != PayPal::PayPalWallet) {
                Details *det = t->amount()->details();
                if (det->handlingFee() > 0.0f) {
                    setError(new Error(Error::InputError, tr("Handling fees are only supported if the payment method is set to PayPal."), Error::Critical, QString(), this));
                    return false;
                }

                if (det->shippingDiscount() > 0.0f) {
                    setError(new Error(Error::InputError, tr("Shipping discount is only supported if the payment method is set to PayPal."), Error::Critical, QString(), this));
                    return false;
                }

                if (det->insurance() > 0.0f) {
                    setError(new Error(Error::InputError, tr("Insurance is only supported if the payment method is set to PayPal."), Error::Critical, QString(), this));
                    return false;
                }
            }
        }

        if (t->itemList() && !t->itemList()->items().isEmpty()) {
            const QList<Item*> its = t->itemList()->items();

            if (!its.isEmpty()) {
                float ilTotal = 0.0f; // total of all item price values
                float ilTax = 0.0f; // total of all item tax values

                for (Item *it : its) {

                    if (it->quantity() < 1) {
                        setError(new Error(Error::InputError, tr("Item quantity has to be more than one."), Error::Critical, QString(), this));
                        return false;
                    }

                    if (it->currency() != t->amount()->currency()) {
                        setError(new Error(Error::InputError, tr("Item currency codes should be the same as the transaction currency code in all buckets."), Error::Critical, QString(), this));
                        return false;
                    }

                    if (d->payment->payer()->paymentMethod() != PayPal::PayPalWallet) {
                        if (!it->description().isEmpty()) {
                            setError(new Error(Error::InputError, tr("Item description is only allowed if the payment method is set to PayPal."), Error::Critical, QString(), this));
                            return false;
                        }

                        if (it->tax() > 0.0f) {
                            setError(new Error(Error::InputError, tr("Per item tax is only supported if the payment method is set to PayPal."), Error::Critical, QString(), this));
                            return false;
                        }
                    }

                    ilTotal += (it->price() * it->quantity());
                    ilTax += (it->tax() * it->quantity());
                }


                if (!t->amount()->details() && ilTotal != t->amount()->total()) {
                    setError(new Error(Error::InputError, tr("The sum of all item prices in a transaction has to be the same as the total amount of the transaction."), Error::Critical, QString(), this));
                    return false;
                }

                if (t->amount()->details()) {
                    if (t->amount()->details()->subtotal() > 0.0f) {
                        if (ilTotal != t->amount()->details()->subtotal()) {
                            setError(new Error(Error::InputError, tr("The sum of all item prices in a transaction has to be the same as the subtotal amount of the transaction."), Error::Critical, QString(), this));
                            return false;
                        }
                    }

                    if (t->amount()->details()->tax() > 0.0f) {
                        if (ilTax != t->amount()->details()->tax()) {
                            setError(new Error(Error::InputError, tr("The sum of all item tax values in a transaction has to be the same as the tax amount of the transaction."), Error::Critical, QString(), this));
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}



bool Create::checkOutput()
{
    if (PPBase::checkOutput()) {

        const QJsonObject o = jsonResult().object();

        if (o.value(QStringLiteral("id")).toString().isEmpty()) {
            setError(new Error(Error::OutputError, tr("No valid ID found in response data."), Error::Critical, QString(), this));
            return false;
        }

        if (QString::compare(o.value(QStringLiteral("state")).toString(), QStringLiteral("created"), Qt::CaseInsensitive) != 0) {
            setError(new Error(Error::OutputError, tr("The payment has not been created."), Error::Critical, o.value(QStringLiteral("state")).toString(), this));
            return false;
        }

        if (o.value(QStringLiteral("links")).toArray().isEmpty()) {
            setError(new Error(Error::OutputError, tr("The response does not contain any links for further processing."), Error::Critical, QString(), this));
            return false;
        }

        return true;

    } else {
        return false;
    }
}



Payment *Create::payment() const { Q_D(const Create); return d->payment; }

void Create::setPayment(Payment *nPayment)
{
    Q_D(Create);
    if (nPayment != d->payment) {
        d->payment = nPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed payment to" << d->payment;
#endif
        Q_EMIT paymentChanged(payment());
    }
}




Payment *Create::newPayment()
{
    Payment *curPayment = payment();

    Payment *p = new Payment(this);
    Payer *payer = new Payer(p);
    p->setPayer(payer);
    setPayment(p);

    if (curPayment) {
        if (curPayment->parent() == this) {
            delete curPayment;
        }
    }

    return payment();
}
