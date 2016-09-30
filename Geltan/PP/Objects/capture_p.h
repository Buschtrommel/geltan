/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * capture_p.h
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

#ifndef CAPTURE_P_H
#define CAPTURE_P_H

#include "capture.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {


class CapturePrivate : public PPObjectsBasePrivate
{
public:
    CapturePrivate() :
        amount(nullptr),
        isFinalCapture(false),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode),
        transactionFee(nullptr)
    {}

    ~CapturePrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    QString id;
    PaymentAmount *amount;
    bool isFinalCapture;
    PayPal::StateType state;
    PayPal::ReasonCode reasonCode;
    QString parentPayment;
    QString invoiceNumber;
    Currency *transactionFee;
    QDateTime createTime;
    QDateTime updateTime;
    QList<Link*> links;
};

}
}

#endif // CAPTURE_P_H
