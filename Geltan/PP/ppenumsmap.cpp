/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * ppenumsmap.cpp
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

#include "ppenumsmap.h"

using namespace Geltan;
using namespace PP;

PPEnumsMap::PPEnumsMap()
{

}



PayPal::PaymentMethod PPEnumsMap::paymentMethodTokenToEnum(const QString &token) const
{
    if (token == QLatin1String("credit_card")) {
        return PayPal::CreditCard;
    } else if (token == QLatin1String("bank")) {
        return PayPal::Bank;
    } else if (token == QLatin1String("paypal")) {
        return PayPal::PayPalWallet;
    } else if (token == QLatin1String("pay_upon_invoice")) {
        return PayPal::PayUponInvoice;
    } else if (token == QLatin1String("carrier")) {
        return PayPal::Carrier;
    } else if (token == QLatin1String("alternate_payment")) {
        return PayPal::AlternatePayment;
    } else {
        return PayPal::NoPaymentMethod;
    }
}



QString PPEnumsMap::paymentMethodEnumToToken(PayPal::PaymentMethod enumeration) const
{
    switch(enumeration) {
    case PayPal::CreditCard:
        return QStringLiteral("credit_card");
    case PayPal::Bank:
        return QStringLiteral("bank");
    case PayPal::PayPalWallet:
        return QStringLiteral("paypal");
    case PayPal::PayUponInvoice:
        return QStringLiteral("pay_upon_invoice");
    case PayPal::Carrier:
        return QStringLiteral("carrier");
    case PayPal::AlternatePayment:
        return QStringLiteral("alternate_payment");
    default:
        return QString();
    }
}



PayPal::CreditCardType PPEnumsMap::creditCardTypeTokenToEnum(const QString &token) const
{
    if (token == QLatin1String("visa")) {
        return PayPal::Visa;
    } else if (token == QLatin1String("mastercard")) {
        return PayPal::MasterCard;
    } else if (token == QLatin1String("discover")) {
        return PayPal::Discover;
    } else if (token == QLatin1String("amex")) {
        return PayPal::Amex;
    } else {
        return PayPal::NoCreditCardType;
    }
}



QString PPEnumsMap::creditCardTypeEnumToToken(PayPal::CreditCardType enumeration) const
{
    switch(enumeration) {
    case PayPal::Visa:
        return QStringLiteral("visa");
    case PayPal::MasterCard:
        return QStringLiteral("mastercard");
    case PayPal::Discover:
        return QStringLiteral("discover");
    case PayPal::Amex:
        return QStringLiteral("amex");
    default:
        return QString();
    }
}



PayPal::PaymentModeType PPEnumsMap::paymentModeTypeTokenToEnum(const QString &token) const
{
    if (token == QLatin1String("INSTANT_TRANSFER")) {
        return PayPal::InstantTransfer;
    } else if (token == QLatin1String("MANUAL_BANK_TRANSFER")) {
        return PayPal::ManualBankTransfer;
    } else if (token == QLatin1String("DELAYED_TRANSFER")) {
        return PayPal::ManualBankTransfer;
    } else if (token == QLatin1String("ECHECK")) {
        return PayPal::ManualBankTransfer;
    } else {
        return PayPal::NoPaymentMode;
    }
}


QString PPEnumsMap::paymentModeTypeEnumToToken(PayPal::PaymentModeType enumeration) const
{
    switch(enumeration) {
    case PayPal::InstantTransfer:
        return QStringLiteral("INSTANT_TRANSFER");
    case PayPal::ManualBankTransfer:
        return QStringLiteral("MANUAL_BANK_TRANSFER");
    case PayPal::DelayedTransfer:
        return QStringLiteral("DELAYED_TRANSFER");
    case PayPal::Echeck:
        return QStringLiteral("ECHECK");
    default:
        return QString();
    }
}



PayPal::StateType PPEnumsMap::stateTypeTokenToEnum(const QString &token) const
{
    if (token == QLatin1String("pending")) {
        return PayPal::Pending;
    } else if (token == QLatin1String("authorized")) {
        return PayPal::Authorized;
    } else if (token == QLatin1String("partially_captured")) {
        return PayPal::PartiallyCaptured;
    } else if (token == QLatin1String("captured")) {
        return PayPal::Captured;
    } else if (token == QLatin1String("expired")) {
        return PayPal::Expired;
    } else if (token == QLatin1String("voided")) {
        return PayPal::Voided;
    } else if (token == QLatin1String("completed")) {
        return PayPal::Completed;
    } else if (token == QLatin1String("partially_refunded")) {
        return PayPal::PartiallyRefunded;
    } else if (token == QLatin1String("refunded")) {
        return PayPal::Refunded;
    } else if (token == QLatin1String("denied")) {
        return PayPal::Denied;
    } else if (token == QLatin1String("failed")) {
        return PayPal::Failed;
    } else {
        return PayPal::NoState;
    }
}



QString PPEnumsMap::stateTypeEnumToToken(PayPal::StateType enumeration) const
{
    switch(enumeration) {
    case PayPal::Pending:
        return QStringLiteral("pending");
    case PayPal::Authorized:
        return QStringLiteral("authorized");
    case PayPal::PartiallyCaptured:
        return QStringLiteral("partially_captured");
    case PayPal::Captured:
        return QStringLiteral("captured");
    case PayPal::Expired:
        return QStringLiteral("expired");
    case PayPal::Voided:
        return QStringLiteral("voided");
    case PayPal::Completed:
        return QStringLiteral("completed");
    case PayPal::PartiallyRefunded:
        return QStringLiteral("partially_refunded");
    case PayPal::Refunded:
        return QStringLiteral("refunded");
    case PayPal::Denied:
        return QStringLiteral("denied");
    case PayPal::Failed:
        return QStringLiteral("failed");
    default:
        return QString();
    }
}



PayPal::ReasonCode PPEnumsMap::reasonCodeTokenToEnum(const QString &token) const
{
    if (token == QLatin1String("CHARGEBACK")) {
        return PayPal::Chargeback;
    } else if (token == QLatin1String("GUARANTEE")) {
        return PayPal::Guarante;
    } else if (token == QLatin1String("BUYER_COMPLAINT")) {
        return PayPal::BuyerComplaint;
    } else if (token == QLatin1String("REFUND")) {
        return PayPal::Refund;
    } else if (token == QLatin1String("UNCONFIRMED_SHIPPING_ADDRESS")) {
        return PayPal::UnconfirmedShippingAddress;
    } else if (token == QLatin1String("ECHECK")) {
        return PayPal::EcheckReason;
    } else if (token == QLatin1String("INTERNATIONAL_WITHDRAWAL")) {
        return PayPal::InternationalWithdrawal;
    } else if (token == QLatin1String("RECEIVING_PREFERENCE_MANDATES_MANUAL_ACTION")) {
        return PayPal::ReceivingPreferenceMandatesManualAction;
    } else if (token == QLatin1String("PAYMENT_REVIEW")) {
        return PayPal::PaymentReview;
    } else if (token == QLatin1String("REGULATORY_REVIEW")) {
        return PayPal::RegulatoryReview;
    } else if (token == QLatin1String("UNILATERAL")) {
        return PayPal::Unilateral;
    } else if (token == QLatin1String("VERIFICATION_REQUIRED")) {
        return PayPal::VerificationRequired;
    } else if (token == QLatin1String("TRANSACTION_APPROVED_AWAITING_FUNDING")) {
        return PayPal::TransactionApprovedAwaitingFunding;
    } else if (token == QLatin1String("PAYER_SHIPPING_UNCONFIRMED")) {
        return PayPal::PayerShippingUnconfirmed;
    } else if (token == QLatin1String("MULTI_CURRENCY")) {
        return PayPal::MultiCurrency;
    } else if (token == QLatin1String("RISK_REVIEW")) {
        return PayPal::RiskReview;
    } else if (token == QLatin1String("ORDER")) {
        return PayPal::Order;
    } else if (token == QLatin1String("OTHER")) {
        return PayPal::Other;
    } else {
        return PayPal::NoReasonCode;
    }
}



QString PPEnumsMap::reasonCodeEnumToToken(PayPal::ReasonCode enumeration) const
{
    switch(enumeration) {
    case PayPal::Chargeback:
        return QStringLiteral("CHARGEBACK");
    case PayPal::Guarante:
        return QStringLiteral("GUARANTEE");
    case PayPal::BuyerComplaint:
        return QStringLiteral("BUYER_COMPLAINT");
    case PayPal::Refund:
        return QStringLiteral("REFUND");
    case PayPal::UnconfirmedShippingAddress:
        return QStringLiteral("UNCONFIRMED_SHIPPING_ADDRESS");
    case PayPal::EcheckReason:
        return QStringLiteral("ECHECK");
    case PayPal::InternationalWithdrawal:
        return QStringLiteral("INTERNATIONAL_WITHDRAWAL");
    case PayPal::ReceivingPreferenceMandatesManualAction:
        return QStringLiteral("RECEIVING_PREFERENCE_MANDATES_MANUAL_ACTION");
    case PayPal::PaymentReview:
        return QStringLiteral("PAYMENT_REVIEW");
    case PayPal::RegulatoryReview:
        return QStringLiteral("REGULATORY_REVIEW");
    case PayPal::Unilateral:
        return QStringLiteral("UNILATERAL");
    case PayPal::VerificationRequired:
        return QStringLiteral("VERIFICATION_REQUIRED");
    case PayPal::TransactionApprovedAwaitingFunding:
        return QStringLiteral("TRANSACTION_APPROVED_AWAITING_FUNDING");
    case PayPal::PayerShippingUnconfirmed:
        return QStringLiteral("PAYER_SHIPPING_UNCONFIRMED");
    case PayPal::MultiCurrency:
        return QStringLiteral("MULTI_CURRENCY");
    case PayPal::RiskReview:
        return QStringLiteral("RISK_REVIEW");
    case PayPal::Order:
        return QStringLiteral("ORDER");
    case PayPal::Other:
        return QStringLiteral("OTHER");
    default:
        return QString();
    }
}



PayPal::ProtectionEligibility PPEnumsMap::protectionEligibilityTokenToEnum(const QString &token) const
{
    if (token == QLatin1String("ELIGIBLE")) {
        return PayPal::Eligible;
    } else if (token == QLatin1String("PARTIALLY_ELIGIBLE")) {
        return PayPal::PartiallyEligible;
    } else if (token == QLatin1String("INELIGIBLE")) {
        return PayPal::Ineligible;
    } else {
        return PayPal::NoProtectionEligibility;
    }
}



QString PPEnumsMap::protectionEligibilityEnumToToken(PayPal::ProtectionEligibility enumeration) const
{
    switch(enumeration) {
    case PayPal::Eligible:
        return QStringLiteral("ELIGIBLE");
    case PayPal::PartiallyEligible:
        return QStringLiteral("PARTIALLY_ELIGIBLE");
    case PayPal::Ineligible:
        return QStringLiteral("INELIGIBLE");
    default:
        return QString();
    }
}



PayPal::ProtectionEligibilityType PPEnumsMap::protectionEligibilityTypeTokenToEnum(const QString &token) const
{
    if (token == QLatin1String("ITEM_NOT_RECEIVED_ELIGIBLE")) {
        return PayPal::ItemNotReceivedEligible;
    } else if (token == QLatin1String("UNAUTHORIZED_PAYMENT_ELIGIBLE")) {
        return PayPal::UnauthorizedPaymentEligible;
    } else {
        return PayPal::NoProtectionEligibilityType;
    }
}



QString PPEnumsMap::protectionEligibilityTypeEnumToToken(PayPal::ProtectionEligibilityType enumeration) const
{
    switch(enumeration) {
    case PayPal::ItemNotReceivedEligible:
        return QStringLiteral("ITEM_NOT_RECEIVED_ELIGIBLE");
    case PayPal::UnauthorizedPaymentEligible:
        return QStringLiteral("UNAUTHORIZED_PAYMENT_ELIGIBLE");
    default:
        return QString();
    }
}
