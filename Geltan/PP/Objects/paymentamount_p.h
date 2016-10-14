/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/paymentamount_p.h
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

#ifndef PAYMENTAMOUNT_P_H
#define PAYMENTAMOUNT_P_H

#include "paymentamount.h"
#include "ppobjectsbase_p.h"
#include "details.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

namespace Geltan {
namespace PP {

class PaymentAmountPrivate : public PPObjectsBasePrivate
{
public:
    PaymentAmountPrivate(PaymentAmount *parent) :
        q_ptr(parent),
        total(0.0),
        details(nullptr),
        valid(false)
    {
        currency.reserve(3);
    }

    ~PaymentAmountPrivate() {}

    void checkValidity()
    {
        bool _v = true;

        if (total == 0.0f || currency.length() != 3) {
            _v = false;
        }

        if (details && _v) {
            float calcTotal = details->subtotal();
            calcTotal += details->tax();
            calcTotal += details->shipping();
            calcTotal += details->insurance();
            calcTotal += details->handlingFee();
            calcTotal += details->shippingDiscount();
            calcTotal += details->giftWrap();

            if ((calcTotal > 0.0f) && (total != calcTotal)) {
                _v = false;
            }
        }

        if (valid != _v) {
            valid = _v;
            Q_Q(PaymentAmount);
            Q_EMIT q->validChanged(valid);
        }
    }

    void updateTotal()
    {
        if (details) {
            Q_Q(PaymentAmount);

            float calcTotal = details->subtotal();
            calcTotal += details->tax();
            calcTotal += details->shipping();
            calcTotal += details->insurance();
            calcTotal += details->handlingFee();
            calcTotal += details->shippingDiscount();
            calcTotal += details->giftWrap();

            if (total != calcTotal) {
                total = calcTotal;
                Q_EMIT q->totalChanged(total);
            }

            if (total == 0.0f || currency.length() != 3) {
                bool _v = false;
                if (valid != _v) {
                    valid = _v;
                    Q_EMIT q->validChanged(valid);
                }
            }
        }
    }

    PaymentAmount * const q_ptr;
    Q_DECLARE_PUBLIC(PaymentAmount)
    QString currency;
    float total;
    Details *details;
    bool valid;
};

}
}

#endif // PAYMENTAMOUNT_P_H
