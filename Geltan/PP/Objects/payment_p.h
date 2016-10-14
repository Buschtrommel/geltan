/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/address.h
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

#ifndef PAYMENT_P_H
#define PAYMENT_P_H

#include "payment.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class PaymentPrivate : public PPObjectsBasePrivate
{
public:
    PaymentPrivate(Payment *parent) :
        q_ptr(parent),
        intent(Payment::NoIntent),
        payer(nullptr),
        state(Payment::NoState),
        redirectUrls(nullptr),
        failureReason(Payment::NoFailureReason)
    {}

    ~PaymentPrivate() {}

    void clearTransactions() {

        if (!transactions.isEmpty()) {

            Q_Q(Payment);

            q->beginRemoveRows(QModelIndex(), 0, transactions.count() - 1);

            qDeleteAll(transactions);
            transactions.clear();

            q->endRemoveRows();
        }
    }

    void clearLinks() {

        if (!links.isEmpty()) {
            Q_Q(Payment);
            qDeleteAll(links);
            links.clear();
            Q_EMIT q->linksChanged(links);
        }

    }

    Payment * const q_ptr;
    Q_DECLARE_PUBLIC(Payment)
    QString id;
    Payment::Intent intent;
    Payer *payer;
    QList<Transaction*> transactions;
    Payment::State state;
    QString experienceProfileId;
    QString noteToPayer;
    RedirectUrls *redirectUrls;
    Payment::FailureReason failureReason;
    QDateTime createTime;
    QDateTime updateTime;
    QList<Link*> links;
};

}
}

#endif // PAYMENT_P_H
