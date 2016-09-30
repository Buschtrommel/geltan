/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * ppenumsmap.h
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

#ifndef PPENUMSMAP_H
#define PPENUMSMAP_H

#include <Geltan/PP/ppenums.h>

namespace Geltan {

namespace PP {

/*!
 * \brief Helper class to convert JSON token strings into enumerations and vice versa.

 * \headerfile "" <Geltan/PP/ppenumsmap.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-22
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class PPEnumsMap
{
public:
    /*!
     * \brief Constructs a new PPEnumsMap object.
     */
    PPEnumsMap();

    /*!
     * \brief Converts a string into PayPal::PaymentMethod.
     */
    PayPal::PaymentMethod paymentMethodTokenToEnum(const QString &token) const;
    /*!
     * \brief Converts a PayPal::PaymentMethod into a string representation.
     */
    QString paymentMethodEnumToToken(PayPal::PaymentMethod enumeration) const;

    /*!
     * \brief Converts a string into PayPal::CreditCardType.
     */
    PayPal::CreditCardType creditCardTypeTokenToEnum(const QString &token) const;
    /*!
     * \brief Converts a PayPal::CreditCardType into a string representation.
     */
    QString creditCardTypeEnumToToken(PayPal::CreditCardType enumeration) const;

    /*!
     * \brief Converts a string into PayPal::PaymentModeType.
     */
    PayPal::PaymentModeType paymentModeTypeTokenToEnum(const QString &token) const;
    /*!
     * \brief Conerts a PayPal::PaymentModeType into a string representation.
     */
    QString paymentModeTypeEnumToToken(PayPal::PaymentModeType enumeration) const;

    /*!
     * \brief Converts a string into PayPal::StateType.
     */
    PayPal::StateType stateTypeTokenToEnum(const QString &token) const;
    /*!
     * \brief Converts a PayPal::StateType into a string representation.
     */
    QString stateTypeEnumToToken(PayPal::StateType enumeration) const;

    /*!
     * \brief Converts a string into PayPal::ReasonCode.
     */
    PayPal::ReasonCode reasonCodeTokenToEnum(const QString &token) const;
    /*!
     * \brief Converts a PayPal::ReasonCode into a string representation.
     */
    QString reasonCodeEnumToToken(PayPal::ReasonCode enumeration) const;

    /*!
     * \brief Converts a string into PayPal::ProtectionEligibility.
     */
    PayPal::ProtectionEligibility protectionEligibilityTokenToEnum(const QString &token) const;
    /*!
     * \brief Converts a PayPal::ProtectionEligibility into a string representation.
     */
    QString protectionEligibilityEnumToToken(PayPal::ProtectionEligibility enumeration) const;

    /*!
     * \brief Converts a string into PayPal::ProtectionEligibilityType.
     */
    PayPal::ProtectionEligibilityType protectionEligibilityTypeTokenToEnum(const QString &token) const;
    /*!
     * \brief Converts a PayPal::ProtectionEligibilityType into a string representation.
     */
    QString protectionEligibilityTypeEnumToToken(PayPal::ProtectionEligibilityType enumeration) const;
};

}

}

#endif // PPENUMSMAP_H
