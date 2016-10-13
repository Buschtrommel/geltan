/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * paymentamount.cpp
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

#include "paymentamount_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


PaymentAmount::PaymentAmount(QObject *parent) :
    QObject(parent), d_ptr(new PaymentAmountPrivate(this))
{
}


PaymentAmount::PaymentAmount(float total, const QString &currency, QObject *parent) :
    QObject(parent), d_ptr(new PaymentAmountPrivate(this))
{
    Q_D(PaymentAmount);
    d->total = total;
    d->currency = currency;
    d->checkValidity();
}



PaymentAmount::PaymentAmount(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new PaymentAmountPrivate(this))
{
    loadFromJson(json);
}


PaymentAmount::PaymentAmount(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new PaymentAmountPrivate(this))
{
    loadFromJson(json);
}


PaymentAmount::~PaymentAmount()
{

}


QString PaymentAmount::currency() const { Q_D(const PaymentAmount); return d->currency; }

void PaymentAmount::setCurrency(const QString &nCurrency)
{
    Q_D(PaymentAmount); 
    if (nCurrency != d->currency) {
        d->currency = nCurrency;
#ifdef QT_DEBUG
        qDebug() << "Changed currency to" << d->currency;
#endif
        Q_EMIT currencyChanged(currency());
        d->checkValidity();
    }
}




float PaymentAmount::total() const { Q_D(const PaymentAmount); return d->total; }

void PaymentAmount::setTotal(float nTotal)
{
    Q_D(PaymentAmount); 
    if (nTotal != d->total) {
        d->total = nTotal;
#ifdef QT_DEBUG
        qDebug() << "Changed total to" << d->total;
#endif
        Q_EMIT totalChanged(total());
        d->checkValidity();
    }
}




Details *PaymentAmount::details() const { Q_D(const PaymentAmount); return d->details; }

void PaymentAmount::setDetails(Details *nDetails)
{
    Q_D(PaymentAmount); 
    if (nDetails != d->details) {

        Details *old = d->details;
        if (old) {
//            disconnect(old, &Details::subtotalChanged, this, &PaymentAmount::subtotalChanged);
//            disconnect(old, &Details::shippingChanged, this, &PaymentAmount::shippingChanged);
//            disconnect(old, &Details::taxChanged, this, &PaymentAmount::taxChanged);
//            disconnect(old, &Details::handlingFeeChanged, this, &PaymentAmount::handlingFeeChanged);
//            disconnect(old, &Details::shippingDiscountChanged, this, &PaymentAmount::shippingDiscountChanged);
//            disconnect(old, &Details::insuranceChanged, this, &PaymentAmount::insuranceChanged);
//            disconnect(old, &Details::giftWrapChanged, this, &PaymentAmount::giftWrapChanged);

//            disconnect(old, &Details::subtotalChanged, this, &PaymentAmount::checkValidity);
//            disconnect(old, &Details::shippingChanged, this, &PaymentAmount::checkValidity);
//            disconnect(old, &Details::taxChanged, this, &PaymentAmount::checkValidity);
//            disconnect(old, &Details::handlingFeeChanged, this, &PaymentAmount::checkValidity);
//            disconnect(old, &Details::shippingDiscountChanged, this, &PaymentAmount::checkValidity);
//            disconnect(old, &Details::insuranceChanged, this, &PaymentAmount::checkValidity);
//            disconnect(old, &Details::giftWrapChanged, this, &PaymentAmount::checkValidity);

            old->disconnect();
        }

        d->details = nDetails;

        if (d->details) {
            connect(d->details, &Details::subtotalChanged, this, &PaymentAmount::subtotalChanged);
            connect(d->details, &Details::shippingChanged, this, &PaymentAmount::shippingChanged);
            connect(d->details, &Details::taxChanged, this, &PaymentAmount::taxChanged);
            connect(d->details, &Details::handlingFeeChanged, this, &PaymentAmount::handlingFeeChanged);
            connect(d->details, &Details::shippingDiscountChanged, this, &PaymentAmount::shippingDiscountChanged);
            connect(d->details, &Details::insuranceChanged, this, &PaymentAmount::insuranceChanged);
            connect(d->details, &Details::giftWrapChanged, this, &PaymentAmount::giftWrapChanged);

            connect(d->details, &Details::subtotalChanged, [=] () {d->checkValidity();});
            connect(d->details, &Details::shippingChanged, [=] () {d->checkValidity();});
            connect(d->details, &Details::taxChanged, [=] () {d->checkValidity();});
            connect(d->details, &Details::handlingFeeChanged, [=] () {d->checkValidity();});
            connect(d->details, &Details::shippingDiscountChanged, [=] () {d->checkValidity();});
            connect(d->details, &Details::insuranceChanged, [=] () {d->checkValidity();});
            connect(d->details, &Details::giftWrapChanged, [=] () {d->checkValidity();});
        }
#ifdef QT_DEBUG
        qDebug() << "Changed details to" << d->details;
#endif
        Q_EMIT detailsChanged(details());
        d->checkValidity();
    }
}



float PaymentAmount::subtotal() const
{
    Q_D(const PaymentAmount);
    if (d->details) {
        return d->details->subtotal();
    } else {
        return 0.0f;
    }
}


void PaymentAmount::setSubtotal(float nSubtotal)
{
    Q_D(PaymentAmount);
    if (!d->details) {
        setDetails(new Details(nSubtotal, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, this));
        Q_EMIT subtotalChanged(subtotal());
    } else {
        d->details->setSubtotal(nSubtotal);
    }
}




float PaymentAmount::shipping() const
{
    Q_D(const PaymentAmount);
    if (d->details) {
        return d->details->shipping();
    } else {
        return 0.0f;
    }
}


void PaymentAmount::setShipping(float nShipping)
{
    Q_D(PaymentAmount);
    if (!d->details) {
        setDetails(new Details(0.0, nShipping, 0.0, 0.0, 0.0, 0.0, 0.0, this));
        Q_EMIT shippingChanged(shipping());
    } else {
        d->details->setShipping(nShipping);
    }
}



float PaymentAmount::tax() const
{
    Q_D(const PaymentAmount);
    if (d->details) {
        return d->details->tax();
    } else {
        return 0.0f;
    }
}



void PaymentAmount::setTax(float nTax)
{
    Q_D(PaymentAmount);
    if (!d->details) {
        setDetails(new Details(0.0, 0.0, nTax, 0.0, 0.0, 0.0, 0.0, this));
        Q_EMIT taxChanged(tax());
    } else {
        d->details->setTax(nTax);
    }
}



float PaymentAmount::handlingFee() const
{
    Q_D(const PaymentAmount);
    if (d->details) {
        return d->details->handlingFee();
    } else {
        return 0.0f;
    }
}


void PaymentAmount::setHandlingFee(float nHandlingFee)
{
    Q_D(PaymentAmount);
    if (!d->details) {
        setDetails(new Details(0.0, 0.0, 0.0, nHandlingFee, 0.0, 0.0, 0.0, this));
        Q_EMIT handlingFeeChanged(handlingFee());
    } else {
        d->details->setHandlingFee(nHandlingFee);
    }
}



float PaymentAmount::shippingDiscount() const
{
    Q_D(const PaymentAmount);
    if (d->details) {
        return d->details->shippingDiscount();
    } else {
        return 0.0f;
    }
}



void PaymentAmount::setShippingDiscount(float nShippingDiscount)
{
    Q_D(PaymentAmount);
    if (!d->details) {
        setDetails(new Details(0.0, 0.0, 0.0, 0.0, nShippingDiscount, 0.0, 0.0, this));
        Q_EMIT shippingDiscountChanged(shippingDiscount());
    } else {
        d->details->setShippingDiscount(nShippingDiscount);
    }
}


float PaymentAmount::insurance() const
{
    Q_D(const PaymentAmount);
    if (d->details) {
        return d->details->insurance();
    } else {
        return 0.0f;
    }
}



void PaymentAmount::setInsurance(float nInsurance)
{
    Q_D(PaymentAmount);
    if (!d->details) {
        setDetails(new Details(0.0, 0.0, 0.0, 0.0, 0.0, nInsurance, 0.0, this));
        Q_EMIT insuranceChanged(insurance());
    } else {
        d->details->setInsurance(nInsurance);
    }
}


float PaymentAmount::giftWrap() const
{
    Q_D(const PaymentAmount);
    if (d->details) {
        return d->details->giftWrap();
    } else {
        return 0.0f;
    }
}


void PaymentAmount::setGiftWrap(float nGiftWrap)
{
    Q_D(PaymentAmount);
    if (!d->details) {
        setDetails(new Details(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, nGiftWrap, this));
        Q_EMIT giftWrapChanged(giftWrap());
    } else {
        d->details->setGiftWrap(nGiftWrap);
    }
}


bool PaymentAmount::valid() const { Q_D(const PaymentAmount); return d->valid; }



QVariantMap PaymentAmount::toVariant()
{
    Q_D(PaymentAmount);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("currency"), currency(), 3);
    d->addFloatToVariantMap(&map, QStringLiteral("total"), total());

    if (details()) {
        d->addMapToVariantMap(&map, QStringLiteral("details"), details()->toVariant());
    }

    return map;
}



QJsonObject PaymentAmount::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}




void PaymentAmount::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void PaymentAmount::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setCurrency(json.value(QStringLiteral("currency")).toString());

    setTotal(json.value(QStringLiteral("total")).toString().toFloat());

    const QJsonObject deo = json.value(QStringLiteral("details")).toObject();
    Details *oldDeo = details();
    if (!deo.isEmpty()) {
        if (oldDeo) {
            oldDeo->loadFromJson(deo);
        } else {
            setDetails(new Details(deo, this));
        }
    } else {
        setDetails(nullptr);
        delete oldDeo;
    }
}
