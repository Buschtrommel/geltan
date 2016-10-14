/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/paymentoptions_p.h
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

#ifndef PAYMENTOPTIONS_P_H
#define PAYMENTOPTIONS_P_H

#include "paymentoptions.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {


class PaymentOptionsPrivate : public PPObjectsBasePrivate
{
public:
    PaymentOptionsPrivate() :
        allowedPaymentMethod(PaymentOptions::NoAllowedPaymentMethod)
    {}

    ~PaymentOptionsPrivate() {}

    PaymentOptions::AllowedPaymentMethodType allowedPaymentMethod;
};

}
}

#endif // PAYMENTOPTIONS_P_H
