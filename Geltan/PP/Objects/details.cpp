/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/details.cpp
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

#include "details_p.h"
#include <QJsonDocument>
#include <QtMath>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Details::Details(QObject *parent) :
    QObject(parent), d_ptr(new DetailsPrivate)
{
}


Details::Details(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new DetailsPrivate)
{
    loadFromJson(json);
}


Details::Details(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new DetailsPrivate)
{
    loadFromJson(json);
}



Details::Details(float subtotal, float shipping, float tax, float handlingFee, float shippingDiscount, float insurance, float giftWrap, QObject *parent) :
    QObject(parent), d_ptr(new DetailsPrivate)
{
    Q_D(Details);
    d->subtotal = subtotal;
    d->shipping = shipping;
    d->tax = tax;
    d->handlingFee = handlingFee;
    d->shippingDiscount = shippingDiscount;
    d->insurance = insurance;
    d->giftWrap = giftWrap;
}


Details::~Details()
{

}


float Details::subtotal() const { Q_D(const Details); return d->subtotal; }

void Details::setSubtotal(float nSubtotal)
{
    Q_D(Details); 
    if (nSubtotal != d->subtotal) {
        d->subtotal = nSubtotal;
#ifdef QT_DEBUG
        qDebug() << "Changed subtotal to" << d->subtotal;
#endif
        Q_EMIT subtotalChanged(subtotal());
    }
}




float Details::shipping() const { Q_D(const Details); return d->shipping; }

void Details::setShipping(float nShipping)
{
    Q_D(Details); 
    if (nShipping != d->shipping) {
        d->shipping = nShipping;
#ifdef QT_DEBUG
        qDebug() << "Changed shipping to" << d->shipping;
#endif
        Q_EMIT shippingChanged(shipping());
    }
}




float Details::tax() const { Q_D(const Details); return d->tax; }

void Details::setTax(float nTax)
{
    Q_D(Details); 
    if (nTax != d->tax) {
        d->tax = nTax;
#ifdef QT_DEBUG
        qDebug() << "Changed tax to" << d->tax;
#endif
        Q_EMIT taxChanged(tax());
    }
}




float Details::handlingFee() const { Q_D(const Details); return d->handlingFee; }

void Details::setHandlingFee(float nHandlingFee)
{
    Q_D(Details); 
    if (nHandlingFee != d->handlingFee) {
        d->handlingFee = nHandlingFee;
#ifdef QT_DEBUG
        qDebug() << "Changed handlingFee to" << d->handlingFee;
#endif
        Q_EMIT handlingFeeChanged(handlingFee());
    }
}




float Details::shippingDiscount() const { Q_D(const Details); return d->shippingDiscount; }

void Details::setShippingDiscount(float nShippingDiscount)
{
    Q_D(Details); 
    if (nShippingDiscount != d->shippingDiscount) {
        d->shippingDiscount = nShippingDiscount;
#ifdef QT_DEBUG
        qDebug() << "Changed shippingDiscount to" << d->shippingDiscount;
#endif
        Q_EMIT shippingDiscountChanged(shippingDiscount());
    }
}




float Details::insurance() const { Q_D(const Details); return d->insurance; }

void Details::setInsurance(float nInsurance)
{
    Q_D(Details); 
    if (nInsurance != d->insurance) {
        d->insurance = nInsurance;
#ifdef QT_DEBUG
        qDebug() << "Changed insurance to" << d->insurance;
#endif
        Q_EMIT insuranceChanged(insurance());
    }
}




float Details::giftWrap() const { Q_D(const Details); return d->giftWrap; }

void Details::setGiftWrap(float nGiftWrap)
{
    Q_D(Details); 
    if (nGiftWrap != d->giftWrap) {
        d->giftWrap = nGiftWrap;
#ifdef QT_DEBUG
        qDebug() << "Changed giftWrap to" << d->giftWrap;
#endif
        Q_EMIT giftWrapChanged(giftWrap());
    }
}



QVariantMap Details::toVariant(const QString &currency)
{
    Q_D(Details);

    QVariantMap map;

    if (QStringList({QStringLiteral("HUF"), QStringLiteral("JPY"), QStringLiteral("TWD")}).contains(currency)) {
        d->addIntToVariantMap(&map, QStringLiteral("subtotal"), qFloor(subtotal()));
        d->addIntToVariantMap(&map, QStringLiteral("shipping"), qFloor(shipping()));
        d->addIntToVariantMap(&map, QStringLiteral("tax"), qFloor(tax()));
        d->addIntToVariantMap(&map, QStringLiteral("handling_fee"), qFloor(handlingFee()));
        d->addIntToVariantMap(&map, QStringLiteral("shipping_discount"), qFloor(shippingDiscount()));
        d->addIntToVariantMap(&map, QStringLiteral("insurance"), qFloor(insurance()));
        d->addIntToVariantMap(&map, QStringLiteral("gift_wrap"), qFloor(giftWrap()));
    } else {
        d->addFloatToVariantMap(&map, QStringLiteral("subtotal"), subtotal());
        d->addFloatToVariantMap(&map, QStringLiteral("shipping"), shipping());
        d->addFloatToVariantMap(&map, QStringLiteral("tax"), tax());
        d->addFloatToVariantMap(&map, QStringLiteral("handling_fee"), handlingFee());
        d->addFloatToVariantMap(&map, QStringLiteral("shipping_discount"), shippingDiscount());
        d->addFloatToVariantMap(&map, QStringLiteral("insurance"), insurance());
        d->addFloatToVariantMap(&map, QStringLiteral("gift_wrap"), giftWrap());
    }

    return map;
}


QJsonObject Details::toJsonObject(const QString &currency)
{
    return QJsonObject::fromVariantMap(this->toVariant(currency));
}




void Details::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void Details::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setSubtotal(json.value(QStringLiteral("subtotal")).toString().toFloat());

    setShipping(json.value(QStringLiteral("shipping")).toString().toFloat());

    setTax(json.value(QStringLiteral("tax")).toString().toFloat());

    setHandlingFee(json.value(QStringLiteral("handling_fee")).toString().toFloat());

    setShippingDiscount(json.value(QStringLiteral("shipping_discount")).toString().toFloat());

    setInsurance(json.value(QStringLiteral("insurance")).toString().toFloat());

    setGiftWrap(json.value(QStringLiteral("gift_wrap")).toString().toFloat());
}
