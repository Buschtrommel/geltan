/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/fmfdetails_p.h
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


#ifndef FMFDETAILS_P_H
#define FMFDETAILS_P_H

#include "fmfdetails.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {


class FMFDetailsPrivate
{
public:
    FMFDetailsPrivate(FMFDetails *parent) :
        q_ptr(parent),
        filterType(FMFDetails::NO_FILTER_TYP),
        filterId(FMFDetails::NO_FILTER_IDENTIFIER)
    {}

    ~FMFDetailsPrivate() {}

    void setFilterType(const QString &ft)
    {
        if (ft == QLatin1String("ACCEPT")) {
            setFilterType(FMFDetails::ACCEPT);
        } else if (ft == QLatin1String("PENDING")) {
            setFilterType(FMFDetails::PENDING);
        } else if (ft == QLatin1String("DENY")) {
            setFilterType(FMFDetails::DENY);
        } else if (ft == QLatin1String("REPORT")) {
            setFilterType(FMFDetails::REPORT);
        } else {
            setFilterType(FMFDetails::NO_FILTER_TYP);
        }
    }

    void setFilterType(FMFDetails::FilterType nFilterType)
    {
        if (filterType != nFilterType) {
            Q_Q(FMFDetails);
            filterType = nFilterType;
#ifdef QT_DEBUG
            qDebug() << "Changed filterType to" << filterType;
#endif
            Q_EMIT q->filterTypeChanged(filterType);
        }
    }

    void setFilterId(const QString &fi)
    {
        if (fi == QLatin1String("AVS_NO_MATCH")) {
            setFilterId(FMFDetails::AVS_NO_MATCH);
        } else if (fi == QLatin1String("AVS_PARTIAL_MATCH")) {
            setFilterId(FMFDetails::AVS_PARTIAL_MATCH);
        } else if (fi == QLatin1String("AVS_UNAVAILABLE_OR_UNSUPPORTED")) {
            setFilterId(FMFDetails::AVS_UNAVAILABLE_OR_UNSUPPORTED);
        } else if (fi == QLatin1String("CARD_SECURITY_CODE_MISMATCH")) {
            setFilterId(FMFDetails::CARD_SECURITY_CODE_MISMATCH);
        } else if (fi == QLatin1String("MAXIMUM_TRANSACTION_AMOUNT")) {
            setFilterId(FMFDetails::MAXIMUM_TRANSACTION_AMOUNT);
        } else if (fi == QLatin1String("UNCONFIRMED_ADDRESS")) {
            setFilterId(FMFDetails::UNCONFIRMED_ADDRESS);
        } else if (fi == QLatin1String("COUNTRY_MONITOR")) {
            setFilterId(FMFDetails::COUNTRY_MONITOR);
        } else if (fi == QLatin1String("LARGE_ORDER_NUMBER")) {
            setFilterId(FMFDetails::LARGE_ORDER_NUMBER);
        } else if (fi == QLatin1String("BILLING_OR_SHIPPING_ADDRESS_MISMATCH")) {
            setFilterId(FMFDetails::BILLING_OR_SHIPPING_ADDRESS_MISMATCH);
        } else if (fi == QLatin1String("RISKY_ZIP_CODE")) {
            setFilterId(FMFDetails::RISKY_ZIP_CODE);
        } else if (fi == QLatin1String("SUSPECTED_FREIGHT_FORWARDER_CHECK")) {
            setFilterId(FMFDetails::SUSPECTED_FREIGHT_FORWARDER_CHECK);
        } else if (fi == QLatin1String("TOTAL_PURCHASE_PRICE_MINIMUM")) {
            setFilterId(FMFDetails::TOTAL_PURCHASE_PRICE_MINIMUM);
        } else if (fi == QLatin1String("IP_ADDRESS_VELOCITY")) {
            setFilterId(FMFDetails::IP_ADDRESS_VELOCITY);
        } else if (fi == QLatin1String("RISKY_EMAIL_ADDRESS_DOMAIN_CHECK")) {
            setFilterId(FMFDetails::RISKY_EMAIL_ADDRESS_DOMAIN_CHECK);
        } else if (fi == QLatin1String("RISKY_BANK_IDENTIFICATION_NUMBER_CHECK")) {
            setFilterId(FMFDetails::RISKY_BANK_IDENTIFICATION_NUMBER_CHECK);
        } else if (fi == QLatin1String("RISKY_IP_ADDRESS_RANGE")) {
            setFilterId(FMFDetails::RISKY_IP_ADDRESS_RANGE);
        } else if (fi == QLatin1String("PAYPAL_FRAUD_MODEL")) {
            setFilterId(FMFDetails::PAYPAL_FRAUD_MODEL);
        } else {
            setFilterId(FMFDetails::NO_FILTER_IDENTIFIER);
        }
    }

    void setFilterId(FMFDetails::FilterIdentifier nFilterId)
    {
        if (filterId != nFilterId) {
            Q_Q(FMFDetails);
            filterId = nFilterId;
#ifdef QT_DEBUG
            qDebug() << "Changed filterId to" << filterId;
#endif
            Q_EMIT q->filterIdChanged(filterId);
        }
    }

    void setName(const QString &nName)
    {
        if (name != nName) {
            Q_Q(FMFDetails);
            name = nName;
#ifdef QT_DEBUG
            qDebug() << "Changed name to" << name;
#endif
            Q_EMIT q->nameChanged(name);
        }
    }

    void setDescription(const QString &nDescription)
    {
        if (description != nDescription) {
            Q_Q(FMFDetails);
            description = nDescription;
#ifdef QT_DEBUG
            qDebug() << "Changed description to" << description;
#endif
            Q_EMIT q->descriptionChanged(description);
        }
    }


    FMFDetails * const q_ptr;
    Q_DECLARE_PUBLIC(FMFDetails)
    FMFDetails::FilterType filterType;
    FMFDetails::FilterIdentifier filterId;
    QString name;
    QString description;
};

}
}

#endif // FMFDETAILS_P_H
