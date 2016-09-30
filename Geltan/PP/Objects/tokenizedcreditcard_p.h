/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * tokenizedcreditcard_p.h
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

#ifndef TOKENIZEDCREDITCARD_P_H
#define TOKENIZEDCREDITCARD_P_H

#include "tokenizedcreditcard.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class TokenizedCreditCardPrivate : public PPObjectsBasePrivate
{
public:
    TokenizedCreditCardPrivate() :
        type(PayPal::NoCreditCardType),
        expireMonth(0),
        expireYear(0)
    {}

    ~TokenizedCreditCardPrivate() {}

    QString creditCardId;
    QString payerId;
    QString last4;
    PayPal::CreditCardType type;
    quint8 expireMonth;
    quint16 expireYear;
};

}
}

#endif // TOKENIZEDCREDITCARD_P_H
