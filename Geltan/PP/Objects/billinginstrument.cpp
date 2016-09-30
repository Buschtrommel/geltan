/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * billinginstrument.cpp
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

#include "billinginstrument_p.h"
#include <QJsonDocument>
#include <Geltan/PP/Objects/installmentdescription.h>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


BillingInstrument::BillingInstrument(QObject *parent) :
    QObject(parent), d_ptr(new BillingInstrumentPrivate)
{
}


BillingInstrument::BillingInstrument(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new BillingInstrumentPrivate)
{
    loadFromJson(json);
}


BillingInstrument::BillingInstrument(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new BillingInstrumentPrivate)
{
    loadFromJson(json);
}


BillingInstrument::~BillingInstrument()
{
    delete d_ptr;
}


QString BillingInstrument::billingAgreementId() const { Q_D(const BillingInstrument); return d->billingAgreementId; }

void BillingInstrument::setBillingAgreementId(const QString &nBillingAgreementId)
{
    Q_D(BillingInstrument); 
    if (nBillingAgreementId != d->billingAgreementId) {
        d->billingAgreementId = nBillingAgreementId;
#ifdef QT_DEBUG
        qDebug() << "Changed billingAgreementId to" << d->billingAgreementId;
#endif
        Q_EMIT billingAgreementIdChanged(billingAgreementId());
    }
}




InstallmentDescription *BillingInstrument::selectedInstallmentOption() const { Q_D(const BillingInstrument); return d->selectedInstallmentOption; }

void BillingInstrument::setSelectedInstallmentOption(InstallmentDescription *nSelectedInstallmentOption)
{
    Q_D(BillingInstrument); 
    if (nSelectedInstallmentOption != d->selectedInstallmentOption) {
        d->selectedInstallmentOption = nSelectedInstallmentOption;
#ifdef QT_DEBUG
        qDebug() << "Changed selectedInstallmentOption to" << d->selectedInstallmentOption;
#endif
        Q_EMIT selectedInstallmentOptionChanged(selectedInstallmentOption());
    }
}




QVariantMap BillingInstrument::toVariant()
{
    Q_D(BillingInstrument);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("billing_agreement_id"), billingAgreementId());
    if (selectedInstallmentOption()) {
        d->addMapToVariantMap(&map, QStringLiteral("selected_installment_option"), selectedInstallmentOption()->toVariant());
    }

    return map;
}



QJsonObject BillingInstrument::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void BillingInstrument::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void BillingInstrument::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setBillingAgreementId(json.value(QStringLiteral("billing_agreement_id")).toString());

    const QJsonObject sio = json.value(QStringLiteral("selected_installment_option")).toObject();
    InstallmentDescription *oldSio = selectedInstallmentOption();
    if (!sio.isEmpty()) {
        if (oldSio) {
            oldSio->loadFromJson(sio);
        } else {
            setSelectedInstallmentOption(new InstallmentDescription(sio, this));
        }
    } else {
        setSelectedInstallmentOption(nullptr);
        delete oldSio;
    }
}
