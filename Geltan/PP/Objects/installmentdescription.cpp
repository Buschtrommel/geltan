/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/installmentdescription.cpp
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

#include "installmentdescription_p.h"
#include <Geltan/PP/Objects/currency.h>
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


InstallmentDescription::InstallmentDescription(QObject *parent) :
    QObject(parent), d_ptr(new InstallmentDescriptionPrivate)
{
}


InstallmentDescription::InstallmentDescription(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new InstallmentDescriptionPrivate)
{
    loadFromJson(json);
}


InstallmentDescription::InstallmentDescription(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new InstallmentDescriptionPrivate)
{
    loadFromJson(json);
}


InstallmentDescription::~InstallmentDescription()
{
}


int InstallmentDescription::term() const { Q_D(const InstallmentDescription); return d->term; }

void InstallmentDescription::setTerm(int nTerm)
{
    Q_D(InstallmentDescription); 
    if (nTerm != d->term) {
        d->term = nTerm;
#ifdef QT_DEBUG
        qDebug() << "Changed term to" << d->term;
#endif
        Q_EMIT termChanged(term());
    }
}




Currency *InstallmentDescription::monthlyPayment() const { Q_D(const InstallmentDescription); return d->monthlyPayment; }

void InstallmentDescription::setMonthlyPayment(Currency *nMonthlyPayment)
{
    Q_D(InstallmentDescription); 
    if (nMonthlyPayment != d->monthlyPayment) {
        d->monthlyPayment = nMonthlyPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed monthlyPayment to" << d->monthlyPayment;
#endif
        Q_EMIT monthlyPaymentChanged(monthlyPayment());
    }
}




Currency *InstallmentDescription::discountAmount() const { Q_D(const InstallmentDescription); return d->discountAmount; }

void InstallmentDescription::setDiscountAmount(Currency *nDiscountAmount)
{
    Q_D(InstallmentDescription); 
    if (nDiscountAmount != d->discountAmount) {
        d->discountAmount = nDiscountAmount;
#ifdef QT_DEBUG
        qDebug() << "Changed discountAmount to" << d->discountAmount;
#endif
        Q_EMIT discountAmountChanged(discountAmount());
    }
}




double InstallmentDescription::discountPercentage() const { Q_D(const InstallmentDescription); return d->discountPercentage; }

void InstallmentDescription::setDiscountPercentage(double nDiscountPercentage)
{
    Q_D(InstallmentDescription); 
    if (nDiscountPercentage != d->discountPercentage) {
        d->discountPercentage = nDiscountPercentage;
#ifdef QT_DEBUG
        qDebug() << "Changed discountPercentage to" << d->discountPercentage;
#endif
        Q_EMIT discountPercentageChanged(discountPercentage());
    }
}




QVariantMap InstallmentDescription::toVariant()
{
    Q_D(InstallmentDescription);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("term"), QString::number(term()));
    if (monthlyPayment()) {
        d->addMapToVariantMap(&map, QStringLiteral("monthly_payment"), monthlyPayment()->toVariant());
    }
    if (discountAmount()) {
        d->addMapToVariantMap(&map, QStringLiteral("discount_amount"), discountAmount()->toVariant());
    }
    d->addStringToVariantMap(&map, QStringLiteral("discount_percentag"), QString::number(discountPercentage()));

    return map;
}


QJsonObject InstallmentDescription::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void InstallmentDescription::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void InstallmentDescription::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setTerm(json.value(QStringLiteral("term")).toString().toInt());

    const QJsonObject mpo = json.value(QStringLiteral("monthly_payment")).toObject();
    Currency *oldMpo = monthlyPayment();
    if (!mpo.isEmpty()) {
        if (oldMpo) {
            oldMpo->loadFromJson(mpo);
        } else {
            setMonthlyPayment(new Currency(mpo, this));
        }
    } else {
        setMonthlyPayment(nullptr);
        delete oldMpo;
    }

    const QJsonObject dao = json.value(QStringLiteral("discount_amount")).toObject();
    Currency *oldDao = discountAmount();
    if (!dao.isEmpty()) {
        if (oldDao) {
            oldDao->loadFromJson(dao);
        } else {
            setDiscountAmount(new Currency(dao, this));
        }
    } else {
        setDiscountAmount(nullptr);
        delete oldDao;
    }

    setDiscountPercentage(json.value(QStringLiteral("discount_percentag")).toString().toDouble());
}
