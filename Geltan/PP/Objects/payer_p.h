/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payer_p.h
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

#ifndef PAYER_P_H
#define PAYER_P_H

#include "payer.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class PayerPrivate : public PPObjectsBasePrivate
{
public:
    PayerPrivate(Payer *parent) :
        q_ptr(parent),
        paymentMethod(PayPal::NoPaymentMethod),
        status(Payer::NoStatus),
        externalSelectedFundingInstrumentType(Payer::NoFundingInstrumentType),
        payerInfo(nullptr)
    {}

    ~PayerPrivate() {}

    void clearFundingInstruments()
    {
        if (!fundingInstruments.isEmpty()) {
            Q_Q(Payer);

            q->beginRemoveRows(QModelIndex(), 0, fundingInstruments.count() - 1);

            qDeleteAll(fundingInstruments);
            fundingInstruments.clear();

            q->endMoveRows();
        }
    }

    Payer * const q_ptr;
    Q_DECLARE_PUBLIC(Payer)
    PayPal::PaymentMethod paymentMethod;
    Payer::Status status;
    QList<FundingInstrument*> fundingInstruments;
    Payer::FundingInstrumentType externalSelectedFundingInstrumentType;
    PayerInfo *payerInfo;
};

}
}

#endif // PAYER_P_H
