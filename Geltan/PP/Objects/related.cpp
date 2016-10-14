/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/related.cpp
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

#include "related_p.h"
#include <Geltan/PP/Objects/sale.h>
#include <Geltan/PP/Objects/authorization.h>
#include <Geltan/PP/Objects/order.h>
#include <Geltan/PP/Objects/capture.h>
#include <Geltan/PP/Objects/refund.h>
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Related::Related(QObject *parent) :
    QObject(parent), d_ptr(new RelatedPrivate)
{
}



Related::Related(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new RelatedPrivate)
{
    loadFromJson(json);
}



Related::Related(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new RelatedPrivate)
{
    loadFromJson(json);
}



Related::~Related()
{
}


Sale *Related::sale() const { Q_D(const Related); return d->sale; }

void Related::setSale(Sale *nSale)
{
    Q_D(Related); 
    if (nSale != d->sale) {
        d->sale = nSale;
#ifdef QT_DEBUG
        qDebug() << "Changed sale to" << d->sale;
#endif
        Q_EMIT saleChanged(sale());
    }
}




Authorization *Related::authorization() const { Q_D(const Related); return d->authorization; }

void Related::setAuthorization(Authorization *nAuthorization)
{
    Q_D(Related); 
    if (nAuthorization != d->authorization) {
        d->authorization = nAuthorization;
#ifdef QT_DEBUG
        qDebug() << "Changed authorization to" << d->authorization;
#endif
        Q_EMIT authorizationChanged(authorization());
    }
}




Order *Related::order() const { Q_D(const Related); return d->order; }

void Related::setOrder(Order *nOrder)
{
    Q_D(Related); 
    if (nOrder != d->order) {
        d->order = nOrder;
#ifdef QT_DEBUG
        qDebug() << "Changed order to" << d->order;
#endif
        Q_EMIT orderChanged(order());
    }
}




Capture *Related::capture() const { Q_D(const Related); return d->capture; }

void Related::setCapture(Capture *nCapture)
{
    Q_D(Related); 
    if (nCapture != d->capture) {
        d->capture = nCapture;
#ifdef QT_DEBUG
        qDebug() << "Changed capture to" << d->capture;
#endif
        Q_EMIT captureChanged(capture());
    }
}




Refund *Related::refund() const { Q_D(const Related); return d->refund; }

void Related::setRefund(Refund *nRefund)
{
    Q_D(Related); 
    if (nRefund != d->refund) {
        d->refund = nRefund;
#ifdef QT_DEBUG
        qDebug() << "Changed refund to" << d->refund;
#endif
        Q_EMIT refundChanged(refund());
    }
}




QVariantMap Related::toVariant()
{
    Q_D(Related);

    QVariantMap map;

    if (authorization()) {
        d->addMapToVariantMap(&map, QStringLiteral("authorization"), authorization()->toVariant());
    }

    if (capture()) {
        d->addMapToVariantMap(&map, QStringLiteral("capture"), capture()->toVariant());
    }

    if (refund()) {
        d->addMapToVariantMap(&map, QStringLiteral("refund"), refund()->toVariant());
    }

    return map;
}



QJsonObject Related::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void Related::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void Related::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    const QJsonObject so = json.value(QStringLiteral("sale")).toObject();
    Sale *oldSo = sale();
    if (!so.isEmpty()) {
        if (oldSo) {
            oldSo->loadFromJson(so);
        } else {
            setSale(new Sale(so, this));
        }
    } else {
        setSale(nullptr);
        delete oldSo;
    }


    const QJsonObject ao = json.value(QStringLiteral("authorization")).toObject();
    Authorization *oldAo = authorization();
    if (!ao.isEmpty()) {
        if (oldAo) {
            oldAo->loadFromJson(ao);
        } else {
            setAuthorization(new Authorization(ao, this));
        }
    } else {
        setAuthorization(nullptr);
        delete oldAo;
    }


    const QJsonObject oo = json.value(QStringLiteral("order")).toObject();
    Order *oldOo = order();
    if (!oo.isEmpty()) {
        if (oldOo) {
            oldOo->loadFromJson(oo);
        } else {
            setOrder(new Order(oo, this));
        }
    } else {
        setOrder(nullptr);
        delete oldOo;
    }


    const QJsonObject co = json.value(QStringLiteral("capture")).toObject();
    Capture *oldCo = capture();
    if (!co.isEmpty()) {
        if (oldCo) {
            oldCo->loadFromJson(co);
        } else {
            setCapture(new Capture(co, this));
        }
    } else {
        setCapture(nullptr);
        delete oldCo;
    }


    const QJsonObject ro = json.value(QStringLiteral("refund")).toObject();
    Refund *oldRo = refund();
    if (!ro.isEmpty()) {
        if (oldRo) {
            oldRo->loadFromJson(ro);
        } else {
            setRefund(new Refund(ro, this));
        }
    } else {
        setRefund(nullptr);
        delete oldRo;
    }
}
