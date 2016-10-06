/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/show_p.h
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

#ifndef SHOWPAYMENT_P_H
#define SHOWPAYMENT_P_H

#include "show.h"
#include "../ppbase_p.h"
#include "../Objects/payment.h"

namespace Geltan {
namespace PP {
namespace Payments {

class ShowPrivate : public PPBasePrivate {
public:
    Payment *payment;
    QString paymentId;
};

}
}
}

#endif // SHOWPAYMENT_P_H
