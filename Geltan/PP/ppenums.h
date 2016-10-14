/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/ppenums.h
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

#ifndef PPENUMS_H
#define PPENUMS_H

#include <QObject>
#include <Geltan/geltan_global.h>

namespace Geltan {

namespace PP {

/*!
 * \brief Provides global used PayPal enumerations.
 *
 * \headerfile "" <Geltan/PP/ppenums.h>
 */
class GELTANSHARED_EXPORT PayPal {
    Q_GADGET
public:
    /*!
     * \brief Defines the used payment method.
     */
    enum PaymentMethod {
        NoPaymentMethod     = 0,    /**< No payment mehtod set. */
        PayPalWallet        = 1,    /**< PayPal wallet payment. */
        CreditCard          = 2,    /**< Direct credit card payment. */
        Bank                = 3,    /**< Bank direct debit. */
        PayUponInvoice      = 4,    /**< Pay upon invoice. */
        Carrier             = 5,    /**< Carrier. */
        AlternatePayment    = 6     /**< Alternate payment method. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(PaymentMethod)
#else
    Q_ENUMS(PaymentMethod)
#endif

    /*!
     * \brief Defines the type of the access token.
     *
     * Access token type as described by the OAuth 2.0 framework in \link https://tools.ietf.org/html/rfc6749#section-7.1 RFC 6749 \endlink.
     */
    enum TokenType {
        NoTokenType = 0,
        Bearer      = 1,
        MAC         = 2
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(TokenType)
#else
    Q_ENUMS(TokenType)
#endif


    /*!
     * \brief Defines the type of a credit card.
     */
    enum CreditCardType {
        NoCreditCardType    = 0,    /**< No credit card set. */
        Visa                = 1,    /**< Visa Card. */
        MasterCard          = 2,    /**< MasterCard. */
        Discover            = 3,    /**< Discover Card. */
        Amex                = 4     /**< American Express. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(CreditCardType)
#else
    Q_ENUMS(CreditCardType)
#endif


    /*!
     * \brief Payment mode type of a transaction.
     */
    enum PaymentModeType {
        NoPaymentMode           = 0,
        InstantTransfer         = 1,
        ManualBankTransfer      = 2,
        DelayedTransfer         = 3,
        Echeck                  = 4
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(PaymentModeType)
#else
    Q_ENUMS(PaymentModeType)
#endif


    /*!
     * \brief State of an authorization, sale, etc. transaction.
     */
    enum StateType {
        NoState                 = 0,    /**< No valid state. */
        Pending                 = 1,    /**< The transaction is pending. */
        Authorized              = 2,    /**< The authorization has successfully completed. */
        PartiallyCaptured       = 3,    /**< The authorization was partially captured. */
        Captured                = 4,    /**< The authorization was fully captured. */
        Expired                 = 5,    /**< The authorization has expired. */
        Voided                  = 6,    /**< The authorization was voided. */
        Completed               = 7,    /**< The transaction has fully completed. */
        PartiallyRefunded       = 8,    /**< The transaction was partially refunded. */
        Refunded                = 9,    /**< The transaction was fully refuned. */
        Denied                  = 10,   /**< The transaction was denied. */
        Failed                  = 11,   /**< The transaction failed. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(StateType)
#else
    Q_ENUMS(StateType)
#endif


    /*!
     * \brief Reason code for a transaction state being Pending or Reversed.
     */
    enum ReasonCode {
        NoReasonCode                            = 0,
        Chargeback                              = 1,
        Guarante                                = 2,
        BuyerComplaint                          = 3,
        Refund                                  = 4,
        UnconfirmedShippingAddress              = 5,
        EcheckReason                            = 6,
        InternationalWithdrawal                 = 7,
        ReceivingPreferenceMandatesManualAction = 8,
        PaymentReview                           = 9,
        RegulatoryReview                        = 10,
        Unilateral                              = 11,
        VerificationRequired                    = 12,
        TransactionApprovedAwaitingFunding      = 13,
        PayerShippingUnconfirmed                = 14,
        MultiCurrency                           = 15,
        RiskReview                              = 16,
        Order                                   = 17,
        Other                                   = 18
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(ReasonCode)
#else
    Q_ENUMS(ReasonCode)
#endif


    /*!
     * \brief Type of seller protection in force for the transaction.
     */
    enum ProtectionEligibility {
        NoProtectionEligibility     = 0,
        Eligible                    = 1,
        PartiallyEligible           = 2,
        Ineligible                  = 3
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(ProtectionEligibility)
#else
    Q_ENUMS(ProtectionEligibility)
#endif


    /*!
     * \brief Kind of seller protection in force for the transaction.
     */
    enum ProtectionEligibilityType {
        NoProtectionEligibilityType = 0,    /**< No valid protection eligibility type. */
        ItemNotReceivedEligible     = 1,    /**< Sellers are protected against claims for items not received. */
        UnauthorizedPaymentEligible = 2     /**< Sellers are protected against claims for unauthorized payments. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(ProtectionEligibilityType)
#else
    Q_ENUMS(ProtectionEligibilityType)
#endif

};

}
}

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::PaymentMethod)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::TokenType)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::CreditCardType)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::PaymentModeType)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::StateType)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::ReasonCode)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::ProtectionEligibility)
Q_DECLARE_METATYPE(Geltan::PP::PayPal::ProtectionEligibilityType)
#endif

#endif // PPENUMS_H
