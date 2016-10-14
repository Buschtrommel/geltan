/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/details_p.h
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

#ifndef DETAILS_P_H
#define DETAILS_P_H

#include "details.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class DetailsPrivate : public PPObjectsBasePrivate
{
public:
    DetailsPrivate() :
        subtotal(0.0),
        shipping(0.0),
        tax(0.0),
        handlingFee(0.0),
        shippingDiscount(0.0),
        insurance(0.0),
        giftWrap(0.0)
    {}

    ~DetailsPrivate() {}

    float subtotal;
    float shipping;
    float tax;
    float handlingFee;
    float shippingDiscount;
    float insurance;
    float giftWrap;
};

}
}

#endif // DETAILS_P_H
