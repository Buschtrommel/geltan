/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * authorization_p.h
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

#ifndef AUTHORIZATION_P_H
#define AUTHORIZATION_P_H

#include "authorization.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {


class AuthorizationPrivate : public PPObjectsBasePrivate
{
public:
    AuthorizationPrivate() :
        amount(nullptr),
        paymentMode(PayPal::NoPaymentMode),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode),
        protectionEligibility(PayPal::NoProtectionEligibility),
        fmfDetails(nullptr)
    {}

    ~AuthorizationPrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    QString id;
    PaymentAmount *amount;
    PayPal::PaymentModeType paymentMode;
    PayPal::StateType state;
    PayPal::ReasonCode reasonCode;
    PayPal::ProtectionEligibility protectionEligibility;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType;
    FMFDetails *fmfDetails;
    QString parentPayment;
    QDateTime validUntil;
    QDateTime createTime;
    QDateTime updateTime;
    QString referenceId;
    QString receiptId;
    QList<Link*> links;
};

}
}

#endif // AUTHORIZATION_P_H
