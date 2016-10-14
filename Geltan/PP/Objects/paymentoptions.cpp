/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/paymentoptions.cpp
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

#include "paymentoptions_p.h"
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


PaymentOptions::PaymentOptions(QObject *parent) :
    QObject(parent), d_ptr(new PaymentOptionsPrivate)
{
}


PaymentOptions::PaymentOptions(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new PaymentOptionsPrivate)
{
    loadFromJson(json);
}


PaymentOptions::PaymentOptions(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new PaymentOptionsPrivate)
{
    loadFromJson(json);
}



PaymentOptions::~PaymentOptions()
{
}


PaymentOptions::AllowedPaymentMethodType PaymentOptions::allowedPaymentMethod() const { Q_D(const PaymentOptions); return d->allowedPaymentMethod; }

void PaymentOptions::setAllowedPaymentMethod(AllowedPaymentMethodType nAllowedPaymentMethod)
{
    Q_D(PaymentOptions); 
    if (nAllowedPaymentMethod != d->allowedPaymentMethod) {
        d->allowedPaymentMethod = nAllowedPaymentMethod;
#ifdef QT_DEBUG
        qDebug() << "Changed allowedPaymentMethod to" << d->allowedPaymentMethod;
#endif
        Q_EMIT allowedPaymentMethodChanged(allowedPaymentMethod());
    }
}




QVariantMap PaymentOptions::toVariant()
{
    Q_D(PaymentOptions);

    QVariantMap map;

    QString apm; // allowed payment method

    switch(allowedPaymentMethod()) {
    case Unrestricted:
        apm = QStringLiteral("UNRESTRICTED");
        break;
    case InstantFundingSource:
        apm = QStringLiteral("INSTANT_FUNDING_SOURCE");
        break;
    case ImmediatePay:
        apm = QStringLiteral("IMMEDIATE_PAY");
        break;
    default:
        break;
    }

    d->addStringToVariantMap(&map, QStringLiteral("allowed_payment_method"), apm);

    return map;
}




QJsonObject PaymentOptions::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void PaymentOptions::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void PaymentOptions::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    const QString apm = json.value(QStringLiteral("allowed_payment_method")).toString();
    if (apm == QLatin1String("UNRESTRICTED")) {
        setAllowedPaymentMethod(Unrestricted);
    } else if (apm == QLatin1String("INSTANT_FUNDING_SOURCE")) {
        setAllowedPaymentMethod(InstantFundingSource);
    } else if (apm == QLatin1String("IMMEDIATE_PAY")) {
        setAllowedPaymentMethod(ImmediatePay);
    } else {
        setAllowedPaymentMethod(NoAllowedPaymentMethod);
    }
}
