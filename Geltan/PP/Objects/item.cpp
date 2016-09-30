/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * item.cpp
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

#include "item_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Item::Item(QObject *parent) :
    QObject(parent), d_ptr(new ItemPrivate)
{
}


Item::Item(Item *other, QObject *parent) :
    QObject(parent), d_ptr(new ItemPrivate(other->d_ptr.data()))
{

}


Item::Item(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new ItemPrivate)
{
    loadFromJson(json);
}


Item::Item(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new ItemPrivate)
{
    loadFromJson(json);
}


Item::~Item()
{

}


QString Item::sku() const { Q_D(const Item); return d->sku; }

void Item::setSku(const QString &nSku)
{
    Q_D(Item); 
    if (nSku != d->sku) {
        d->sku = nSku;
#ifdef QT_DEBUG
        qDebug() << "Changed sku to" << d->sku;
#endif
        Q_EMIT skuChanged(sku());
    }
}




QString Item::name() const { Q_D(const Item); return d->name; }

void Item::setName(const QString &nName)
{
    Q_D(Item); 
    if (nName != d->name) {
        d->name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << d->name;
#endif
        Q_EMIT nameChanged(name());
    }
}




QString Item::description() const { Q_D(const Item); return d->description; }

void Item::setDescription(const QString &nDescription)
{
    Q_D(Item); 
    if (nDescription != d->description) {
        d->description = nDescription;
#ifdef QT_DEBUG
        qDebug() << "Changed description to" << d->description;
#endif
        Q_EMIT descriptionChanged(description());
    }
}




int Item::quantity() const { Q_D(const Item); return d->quantity; }

void Item::setQuantity(int nQuantity)
{
    Q_D(Item); 
    if (nQuantity != d->quantity) {
        d->quantity = nQuantity;
#ifdef QT_DEBUG
        qDebug() << "Changed quantity to" << d->quantity;
#endif
        Q_EMIT quantityChanged(quantity());
    }
}




float Item::price() const { Q_D(const Item); return d->price; }

void Item::setPrice(float nPrice)
{
    Q_D(Item); 
    if (nPrice != d->price) {
        d->price = nPrice;
#ifdef QT_DEBUG
        qDebug() << "Changed price to" << d->price;
#endif
        Q_EMIT priceChanged(price());
    }
}




QString Item::currency() const { Q_D(const Item); return d->currency; }

void Item::setCurrency(const QString &nCurrency)
{
    Q_D(Item); 
    if (nCurrency != d->currency) {
        d->currency = nCurrency;
#ifdef QT_DEBUG
        qDebug() << "Changed currency to" << d->currency;
#endif
        Q_EMIT currencyChanged(currency());
    }
}




float Item::tax() const { Q_D(const Item); return d->tax; }

void Item::setTax(float nTax)
{
    Q_D(Item); 
    if (nTax != d->tax) {
        d->tax = nTax;
#ifdef QT_DEBUG
        qDebug() << "Changed tax to" << d->tax;
#endif
        Q_EMIT taxChanged(tax());
    }
}




QUrl Item::url() const { Q_D(const Item); return d->url; }

void Item::setUrl(const QUrl &nUrl)
{
    Q_D(Item); 
    if (nUrl != d->url) {
        d->url = nUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed url to" << d->url;
#endif
        Q_EMIT urlChanged(url());
    }
}




QVariantMap Item::toVariant()
{
    Q_D(Item);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("sku"), sku(), 127);
    d->addStringToVariantMap(&map, QStringLiteral("name"), name(), 127);
    d->addStringToVariantMap(&map, QStringLiteral("description"), description(), 127);
    d->addStringToVariantMap(&map, QStringLiteral("quantity"), QString::number(quantity()));
    d->addStringToVariantMap(&map, QStringLiteral("price"), QString::number(price(), 'f', 2), 10);
    d->addStringToVariantMap(&map, QStringLiteral("currency"), currency(), 3);
    d->addStringToVariantMap(&map, QStringLiteral("tax"), QString::number(tax(), 'f', 2));
    d->addStringToVariantMap(&map, QStringLiteral("url"), url().toString());

    return map;
}



QJsonObject Item::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void Item::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void Item::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setSku(json.value(QStringLiteral("sku")).toString());

    setName(json.value(QStringLiteral("name")).toString());

    setDescription(json.value(QStringLiteral("description")).toString());

    setQuantity(json.value(QStringLiteral("quantity")).toInt());

    setPrice(json.value(QStringLiteral("price")).toString().toFloat());

    setCurrency(json.value(QStringLiteral("currency")).toString());

    setTax(json.value(QStringLiteral("tax")).toString().toFloat());

    const QString sUrl = json.value(QStringLiteral("url")).toString();
    if (!sUrl.isEmpty()) {
        setUrl(QUrl(sUrl));
    } else {
        setUrl(QUrl());
    }
}
