/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/creditcard_p.h
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

#ifndef CREDITCARD_P_H
#define CREDITCARD_P_H

#include "creditcard.h"
#include "address.h"
#include "link.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class CreditCardPrivate : public PPObjectsBasePrivate
{
public:
    CreditCardPrivate() :
        type(PayPal::NoCreditCardType),
        expireMonth(0),
        expireYear(0),
        billingAddress(nullptr),
        state(CreditCard::NoState)
    {}

    ~CreditCardPrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    QString number;
    PayPal::CreditCardType type;
    quint8 expireMonth;
    quint16 expireYear;
    QString cvv2;
    QString firstName;
    QString lastName;
    Address *billingAddress;
    QString externalCustomerId;
    CreditCard::State state;
    QDateTime validUntil;
    QList<Link*> links;
};

}
}

#endif // CREDITCARD_P_H
