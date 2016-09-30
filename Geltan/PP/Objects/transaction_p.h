/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * transaction_p.h
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

#ifndef TRANSACTION_P_H
#define TRANSACTION_P_H

#include "transaction.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {


class TransactionPrivate : public PPObjectsBasePrivate
{
public:
    TransactionPrivate(Transaction *parent) :
        q_ptr(parent),
        amount(nullptr),
        paymentOptions(nullptr),
        itemList(nullptr),
        payee(nullptr)
    {}

    ~TransactionPrivate() {}

    void clear() {

        if (!relatedResources.isEmpty()) {

            Q_Q(Transaction);

            q->beginRemoveRows(QModelIndex(), 0, relatedResources.count() - 1);

            qDeleteAll(relatedResources);
            relatedResources.clear();

            q->endRemoveRows();

        }
    }

    Transaction * const q_ptr;
    Q_DECLARE_PUBLIC(Transaction)
    QString referenceId;
    PaymentAmount *amount;
    QString description;
    QString noteToPayee;
    QString custom;
    QString invoiceNumber;
    QString softDescriptor;
    PaymentOptions *paymentOptions;
    ItemList *itemList;
    QUrl notifyUrl;
    QUrl orderUrl;
    QList<Related*> relatedResources;
    Payee *payee;
};

}
}

#endif // TRANSACTION_P_H
