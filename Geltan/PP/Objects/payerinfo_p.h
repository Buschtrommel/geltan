/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payerinfo_p.h
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

#ifndef PAYERINFO_P_H
#define PAYERINFO_P_H

#include "payerinfo.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class PayerInfoPrivate : public PPObjectsBasePrivate
{
public:
    PayerInfoPrivate() :
        phoneType(PayerInfo::NoPhoneType),
        birthDate(QDate()),
        taxIdType(PayerInfo::NoTaxIdType),
        billingAddress(nullptr),
        shippingAddress(nullptr)
    {}

    ~PayerInfoPrivate() {}

    QString email;
    QString externalRememberMeId;
    QString buyerAccountNumber;
    QString salutation;
    QString firstName;
    QString middleName;
    QString lastName;
    QString suffix;
    QString payerId;
    QString phone;
    PayerInfo::PhoneType phoneType;
    QDate birthDate;
    QString taxId;
    PayerInfo::TaxIdType taxIdType;
    QString countryCode;
    Address *billingAddress;
    ShippingAddress *shippingAddress;
};

}
}

#endif // PAYERINFO_P_H
