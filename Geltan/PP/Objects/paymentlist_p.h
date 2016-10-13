/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/paymentlist_p.h
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

#ifndef PAYMENTLIST_P_H
#define PAYMENTLIST_P_H

#include "paymentlist.h"
#include "payment.h"

namespace Geltan {
namespace PP {

class PaymentListPrivate
{
public:
    PaymentListPrivate(PaymentList *parent) :
        q_ptr(parent),
        count(0)
    {}

    ~PaymentListPrivate() {}

    void clear()
    {
        Q_Q(PaymentList);

        if (!payments.isEmpty()) {

            q->beginRemoveRows(QModelIndex(), 0, payments.count() - 1);

            qDeleteAll(payments);
            payments.clear();

            q->endRemoveRows();
        }

        count = 0;
        Q_EMIT q->countChanged(0);
        nextId.clear();
        Q_EMIT q->nextIdChanged(nextId);
    }

    PaymentList * const q_ptr;
    Q_DECLARE_PUBLIC(PaymentList)
    QList<Payment*> payments;
    int count;
    QString nextId;
};


}
}

#endif // PAYMENTLIST_P_H
