/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * refund_p.h
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

#ifndef REFUND_P_H
#define REFUND_P_H

#include "refund.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {


class RefundPrivate : public PPObjectsBasePrivate
{
public:
    RefundPrivate() :
        amount(nullptr),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode)
    {}

    ~RefundPrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    QString id;
    PaymentAmount *amount;
    PayPal::StateType state;
    QString reason;
    QString saleId;
    QString captureId;
    QString parentPayment;
    QString description;
    QDateTime createTime;
    QDateTime updateTime;
    PayPal::ReasonCode reasonCode;
    QList<Link*> links;
};

}
}

#endif // REFUND_P_H
