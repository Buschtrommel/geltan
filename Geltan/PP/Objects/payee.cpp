/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payee.cpp
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

#include "payee_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Payee::Payee(QObject *parent) :
    QObject(parent), d_ptr(new PayeePrivate)
{
}


Payee::Payee(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new PayeePrivate)
{
    loadFromJson(json);
}


Payee::Payee(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new PayeePrivate)
{
    loadFromJson(json);
}


Payee::~Payee()
{
}


QString Payee::email() const { Q_D(const Payee); return d->email; }

void Payee::setEmail(const QString &nEmail)
{
    Q_D(Payee); 
    if (nEmail != d->email) {
        d->email = nEmail;
#ifdef QT_DEBUG
        qDebug() << "Changed email to" << d->email;
#endif
        Q_EMIT emailChanged(email());
    }
}




QString Payee::merchantId() const { Q_D(const Payee); return d->merchantId; }

void Payee::setMerchantId(const QString &nMerchantId)
{
    Q_D(Payee); 
    if (nMerchantId != d->merchantId) {
        d->merchantId = nMerchantId;
#ifdef QT_DEBUG
        qDebug() << "Changed merchantId to" << d->merchantId;
#endif
        Q_EMIT merchantIdChanged(merchantId());
    }
}



void Payee::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void Payee::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setEmail(json.value(QStringLiteral("email")).toString());
    setMerchantId(json.value(QStringLiteral("merchant_id")).toString());
}
