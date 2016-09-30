/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * fmfdetails.cpp
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


#include "fmfdetails_p.h"
#include <QJsonDocument>
#include <QJsonObject>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


FMFDetails::FMFDetails(QObject *parent) :
    QObject(parent), d_ptr(new FMFDetailsPrivate)
{
}


FMFDetails::FMFDetails(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new FMFDetailsPrivate)
{
    loadFromJson(json);
}


FMFDetails::FMFDetails(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new FMFDetailsPrivate)
{
    loadFromJson(json);
}


FMFDetails::~FMFDetails()
{
}


FMFDetails::FilterType FMFDetails::filterType() const { Q_D(const FMFDetails); return d->filterType; }

void FMFDetails::setFilterType(FilterType nFilterType)
{
    Q_D(FMFDetails); 
    if (nFilterType != d->filterType) {
        d->filterType = nFilterType;
#ifdef QT_DEBUG
        qDebug() << "Changed filterType to" << d->filterType;
#endif
        Q_EMIT filterTypeChanged(filterType());
    }
}




FMFDetails::FilterIdentifier FMFDetails::filterId() const { Q_D(const FMFDetails); return d->filterId; }

void FMFDetails::setFilterId(FilterIdentifier nFilterId)
{
    Q_D(FMFDetails); 
    if (nFilterId != d->filterId) {
        d->filterId = nFilterId;
#ifdef QT_DEBUG
        qDebug() << "Changed filterId to" << d->filterId;
#endif
        Q_EMIT filterIdChanged(filterId());
    }
}




QString FMFDetails::name() const { Q_D(const FMFDetails); return d->name; }

void FMFDetails::setName(const QString &nName)
{
    Q_D(FMFDetails); 
    if (nName != d->name) {
        d->name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << d->name;
#endif
        Q_EMIT nameChanged(name());
    }
}




QString FMFDetails::description() const { Q_D(const FMFDetails); return d->description; }

void FMFDetails::setDescription(const QString &nDescription)
{
    Q_D(FMFDetails); 
    if (nDescription != d->description) {
        d->description = nDescription;
#ifdef QT_DEBUG
        qDebug() << "Changed description to" << d->description;
#endif
        Q_EMIT descriptionChanged(description());
    }
}




void FMFDetails::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void FMFDetails::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    const QString ft = json.value(QStringLiteral("filter_type")).toString();
    if (ft == QLatin1String("ACCEPT")) {
        setFilterType(Accept);
    } else if (ft == QLatin1String("PENDING")) {
        setFilterType(Pending);
    } else if (ft == QLatin1String("DENY")) {
        setFilterType(Deny);
    } else if (ft == QLatin1String("REPORT")) {
        setFilterType(Report);
    } else {
        setFilterType(NoFilterType);
    }


    const QString fi = json.value(QStringLiteral("filter_id")).toString();
    if (fi == QLatin1String("AVS_NO_MATCH")) {
        setFilterId(AvsNoMatch);
    } else if (fi == QLatin1String("AVS_PARTIAL_MATCH")) {
        setFilterId(AvsParitalMatch);
    } else if (fi == QLatin1String("AVS_UNAVAILABLE_OR_UNSUPPORTED")) {
        setFilterId(AvsUnavailableOrUnsupported);
    } else if (fi == QLatin1String("CARD_SECURITY_CODE_MISMATCH")) {
        setFilterId(CardSecurityCodeMismatch);
    } else if (fi == QLatin1String("MAXIMUM_TRANSACTION_AMOUNT")) {
        setFilterId(MaximumTransactionAmount);
    } else if (fi == QLatin1String("UNCONFIRMED_ADDRESS")) {
        setFilterId(UnconfirmedAddress);
    } else if (fi == QLatin1String("COUNTRY_MONITOR")) {
        setFilterId(CountryMonitor);
    } else if (fi == QLatin1String("LARGE_ORDER_NUMBER")) {
        setFilterId(LargeOrderNumber);
    } else if (fi == QLatin1String("BILLING_OR_SHIPPING_ADDRESS_MISMATCH")) {
        setFilterId(BillingOrShippingAddressMismatch);
    } else if (fi == QLatin1String("RISKY_ZIP_CODE")) {
        setFilterId(RiskyZipCode);
    } else if (fi == QLatin1String("SUSPECTED_FREIGHT_FORWARDER_CHECK")) {
        setFilterId(SuspectedFreightForwardedCheck);
    } else if (fi == QLatin1String("TOTAL_PURCHASE_PRICE_MINIMUM")) {
        setFilterId(TotalPurchasePriceMinimum);
    } else if (fi == QLatin1String("IP_ADDRESS_VELOCITY")) {
        setFilterId(IpAddressVelocity);
    } else if (fi == QLatin1String("RISKY_EMAIL_ADDRESS_DOMAIN_CHECK")) {
        setFilterId(RiskyEmailAddressDomainCheck);
    } else if (fi == QLatin1String("RISKY_BANK_IDENTIFICATION_NUMBER_CHECK")) {
        setFilterId(RiskyBankIdentificationNumberCheck);
    } else if (fi == QLatin1String("RISKY_IP_ADDRESS_RANGE")) {
        setFilterId(RiskyIpAddressRange);
    } else if (fi == QLatin1String("PAYPAL_FRAUD_MODEL")) {
        setFilterId(PaypalFraudModel);
    } else {
        setFilterId(NoFilterIdentifier);
    }

    setName(json.value(QStringLiteral("name")).toString());

    setDescription(json.value(QStringLiteral("description")).toString());
}
