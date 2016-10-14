/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/address_p.h
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

#ifndef ADDRESS_P_H
#define ADDRESS_P_H

#include "address.h"
#include "ppobjectsbase_p.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {

class AddressPrivate : public PPObjectsBasePrivate
{
public:
    AddressPrivate(Address *parent) :
        q_ptr(parent),
        normalizationStatus(Address::UNKNOWN),
        status(Address::NO_STATUS)
    {}

    ~AddressPrivate() {}

    /*!
     * \brief Sets the address normalization status.
     */
    void setNormalizationStatus(Address::NormalizationStatus nNormalizationStatus)
    {
        if (nNormalizationStatus != normalizationStatus) {
            Q_Q(Address);
            normalizationStatus = nNormalizationStatus;
#ifdef QT_DEBUG
            qDebug() << "Changed normalizationStatus to" << normalizationStatus;
#endif
            Q_EMIT q->normalizationStatusChanged(normalizationStatus);
        }
    }


    Address * const q_ptr;
    Q_DECLARE_PUBLIC(Address)
    QString line1;
    QString line2;
    QString city;
    QString countryCode;
    QString postalCode;
    QString state;
    QString phone;
    Address::NormalizationStatus normalizationStatus;
    Address::Status status;
    QString type;
};

}
}

#endif // ADDRESS_P_H
