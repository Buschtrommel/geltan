/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * address_p.h
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

namespace Geltan {
namespace PP {

class AddressPrivate : public PPObjectsBasePrivate
{
public:
    AddressPrivate() :
        normalizationStatus(Address::Unknown),
        status(Address::NoStatus)
    {}

    ~AddressPrivate() {}

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
