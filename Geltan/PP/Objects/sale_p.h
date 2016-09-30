/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * sale.h
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

#ifndef SALE_P_H
#define SALE_P_H

#include "sale.h"

namespace Geltan {
namespace PP {


class SalePrivate
{
public:
    SalePrivate() :
        amount(nullptr),
        paymentMode(PayPal::NoPaymentMode),
        state(PayPal::NoState),
        reasonCode(PayPal::NoReasonCode),
        protectionEligibility(PayPal::NoProtectionEligibility),
        paymentHoldStatus(Sale::NoPaymentHoldStatus),
        transactionFee(nullptr),
        receivableAmount(nullptr),
        exchangeRate(0.0),
        fmfDetails(nullptr),
        processorResponse(nullptr)
    {}

    ~SalePrivate() {}

    void clearLinks()
    {
        if (!links.isEmpty()) {
            qDeleteAll(links);
            links.clear();
        }
    }

    QString id;
    QString purchaseUnitReferenceId;
    PaymentAmount *amount;
    PayPal::PaymentModeType paymentMode;
    PayPal::StateType state;
    PayPal::ReasonCode reasonCode;
    PayPal::ProtectionEligibility protectionEligibility;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType;
    QDateTime clearingTime;
    Sale::PaymentHoldStatus paymentHoldStatus;
    QStringList paymentHoldReasons;
    Currency *transactionFee;
    Currency *receivableAmount;
    float exchangeRate;
    FMFDetails *fmfDetails;
    QString receiptId;
    QString parentPayment;
    ProcessorResponse *processorResponse;
    QString billingAgreementId;
    QDateTime createTime;
    QDateTime updateTime;
    QList<Link*> links;
};

}
}

#endif // SALE_P_H
