/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payerinfo.h
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

#ifndef PAYERINFO_H
#define PAYERINFO_H

#include <QObject>
#include <QDate>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class PayerInfoPrivate;
class Address;
class ShippingAddress;

/*!
 * \brief Containes detailed information about a Payer.
 *
 * \ppPaymentsApi{payer_info}
 *
 * \headerfile "" <Geltan/PP/Objects/payerinfo.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT PayerInfo : public QObject
{
    Q_OBJECT
    /*!
     * \brief Email address representing the payer.
     *
     * 127 characters max.
     *
     * \ppApiName{email}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>email() const</TD></TR><TR><TD>void</TD><TD>setEmail(const QString &nEmail)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>emailChanged(const QString &email)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    /*!
     * \brief External Remember Me id representing the payer.
     *
     * \ppApiName{external_remember_me_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>externalRememberMeId() const</TD></TR><TR><TD>void</TD><TD>setExternalRememberMeId(const QString &nExternalRememberMeId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>externalRememberMeIdChanged(const QString &externalRememberMeId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString externalRememberMeId READ externalRememberMeId WRITE setExternalRememberMeId NOTIFY externalRememberMeIdChanged)
    /*!
     * \brief Account Number representing the Payer.
     *
     * \ppApiName{buyer_account_number}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>buyerAccountNumber() const</TD></TR><TR><TD>void</TD><TD>setBuyerAccountNumber(const QString &nBuyerAccountNumber)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>buyerAccountNumberChanged(const QString &buyerAccountNumber)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString buyerAccountNumber READ buyerAccountNumber WRITE setBuyerAccountNumber NOTIFY buyerAccountNumberChanged)
    /*!
     * \brief Salutation of the payer.
     *
     * \ppApiName{salutation}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>salutation() const</TD></TR><TR><TD>void</TD><TD>setSalutation(const QString &nSalutation)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>salutationChanged(const QString &salutation)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString salutation READ salutation WRITE setSalutation NOTIFY salutationChanged)
    /*!
     * \brief First name of the payer.
     *
     * \ppApiName{first_name}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>firstName() const</TD></TR><TR><TD>void</TD><TD>setFirstName(const QString &nFirstName)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>firstNameChanged(const QString &firstName)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    /*!
     * \brief Middle name of the payer.
     *
     * \ppApiName{middle_name}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>middleName() const</TD></TR><TR><TD>void</TD><TD>setMiddleName(const QString &nMiddleName)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>middleNameChanged(const QString &middleName)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString middleName READ middleName WRITE setMiddleName NOTIFY middleNameChanged)
    /*!
     * \brief Last name of the payer.
     *
     * \ppApiName{last_name}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>lastName() const</TD></TR><TR><TD>void</TD><TD>setLastName(const QString &nLastName)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>lastNameChanged(const QString &lastName)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    /*!
     * \brief Suffix of the payer.
     *
     * \ppApiName{suffix}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>suffix() const</TD></TR><TR><TD>void</TD><TD>setSuffix(const QString &nSuffix)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>suffixChanged(const QString &suffix)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged)
    /*!
     * \brief PayPal assigned encrypted Payer ID.
     *
     * \ppApiName{payer_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>payerId() const</TD></TR><TR><TD>void</TD><TD>setPayerId(const QString &nPayerId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payerIdChanged(const QString &payerId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString payerId READ payerId WRITE setPayerId NOTIFY payerIdChanged)
    /*!
     * \brief Phone number representing the payer.
     *
     * \ppApiName{phone}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>phone() const</TD></TR><TR><TD>void</TD><TD>setPhone(const QString &nPhone)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>phoneChanged(const QString &phone)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    /*!
     * \brief Phone type.
     *
     * \ppApiName{phone_type}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PhoneType</TD><TD>phoneType() const</TD></TR><TR><TD>void</TD><TD>setPhoneType(PhoneType nPhoneType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>phoneTypeChanged(PhoneType phoneType)</TD></TR></TABLE>
     */
    Q_PROPERTY(PhoneType phoneType READ phoneType WRITE setPhoneType NOTIFY phoneTypeChanged)
    /*!
     * \brief Birth date of the Payer in ISO8601 format (yyyy-mm-dd).
     *
     * \ppApiName{birth_date}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDate</TD><TD>birthDate() const</TD></TR><TR><TD>void</TD><TD>setBirthDate(const QDate &nBirthDate)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>birthDateChanged(const QDate &birthDate)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDate birthDate READ birthDate WRITE setBirthDate NOTIFY birthDateChanged)
    /*!
     * \brief Payer’s tax ID. Only supported when the payment_method is set to paypal.
     *
     * \ppApiName{tax_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>taxId() const</TD></TR><TR><TD>void</TD><TD>setTaxId(const QString &nTaxId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>taxIdChanged(const QString &taxId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString taxId READ taxId WRITE setTaxId NOTIFY taxIdChanged)
    /*!
     * \brief Payer’s tax ID type.
     *
     * \ppApiName{tax_id_type}
     *
     * \par Access functions:
     * <TABLE><TR><TD>TaxIdType</TD><TD>taxIdType() const</TD></TR><TR><TD>void</TD><TD>setTaxIdType(TaxIdType nTaxIdType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>taxIdTypeChanged(TaxIdType taxIdType)</TD></TR></TABLE>
     */
    Q_PROPERTY(TaxIdType taxIdType READ taxIdType WRITE setTaxIdType NOTIFY taxIdTypeChanged)
    /*!
     * \brief Two-letter registered country code of the payer to identify the buyer country.
     *
     * \ppApiName{country_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>countryCode() const</TD></TR><TR><TD>void</TD><TD>setCountryCode(const QString &nCountryCode)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>countryCodeChanged(const QString &countryCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString countryCode READ countryCode WRITE setCountryCode NOTIFY countryCodeChanged)
    /*!
     * \brief Base Address object used as billing address in a payment or extended for Shipping Address.
     *
     * \ppApiName{billing_address}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Address*</TD><TD>billingAddress() const</TD></TR><TR><TD>void</TD><TD>setBillingAddress(Address *nBillingAddress)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>billingAddressChanged(Address *billingAddress)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Address *billingAddress READ billingAddress WRITE setBillingAddress NOTIFY billingAddressChanged)
    /*!
     * \brief Extended Address object used as shipping address in a payment.
     *
     * \ppApiName{shipping_address}
     *
     * \par Access functions:
     * <TABLE><TR><TD>ShippingAddress*</TD><TD>shippingAddress() const</TD></TR><TR><TD>void</TD><TD>setShippingAddress(ShippingAddress *nShippingAddress)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>shippingAddressChanged(ShippingAddress *shippingAddress)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::ShippingAddress *shippingAddress READ shippingAddress WRITE setShippingAddress NOTIFY shippingAddressChanged)
public:
    /*!
     * \brief Constructs a new empty PayerInfo object.
     */
    explicit PayerInfo(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new PayerInfo object from JSON data.
     */
    PayerInfo(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new PayerInfo object from JSON data.
     */
    PayerInfo(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the PayerInfo object.
     */
    ~PayerInfo();

    /*!
     * \brief Defines the type of a phone number.
     */
    enum PhoneType {
        NoPhoneType = 0,
        Home        = 1,
        Work        = 2,
        Mobile      = 3,
        Other       = 4
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(PhoneType)
#else
    Q_ENUMS(PhoneType)
#endif

    /*!
     * \brief Defines the type of the tax id.
     */
    enum TaxIdType {
        NoTaxIdType = 0,
        BR_CPF      = 1,
        BR_CNPJ     = 2
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(TaxIdType)
#else
    Q_ENUMS(TaxIdType)
#endif


    QString email() const;
    QString externalRememberMeId() const;
    QString buyerAccountNumber() const;
    QString salutation() const;
    QString firstName() const;
    QString middleName() const;
    QString lastName() const;
    QString suffix() const;
    QString payerId() const;
    QString phone() const;
    PhoneType phoneType() const;
    QDate birthDate() const;
    QString taxId() const;
    TaxIdType taxIdType() const;
    QString countryCode() const;
    Address *billingAddress() const;
    ShippingAddress *shippingAddress() const;


    void setEmail(const QString &nEmail);
    void setExternalRememberMeId(const QString &nExternalRememberMeId);
    void setBuyerAccountNumber(const QString &nBuyerAccountNumber);
    void setSalutation(const QString &nSalutation);
    void setFirstName(const QString &nFirstName);
    void setMiddleName(const QString &nMiddleName);
    void setLastName(const QString &nLastName);
    void setSuffix(const QString &nSuffix);
    void setPayerId(const QString &nPayerId);
    void setPhone(const QString &nPhone);
    void setPhoneType(PhoneType nPhoneType);
    void setBirthDate(const QDate &nBirthDate);
    void setTaxId(const QString &nTaxId);
    void setTaxIdType(TaxIdType nTaxIdType);
    void setCountryCode(const QString &nCountryCode);
    void setBillingAddress(Address *nBillingAddress);
    void setShippingAddress(ShippingAddress *nShippingAddress);


    /*!
     * \brief Returns a QVariantMap containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API.
     */
    QVariantMap toVariant();

    /*!
     * \brief Returns a QJsonObject containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API.
     */
    QJsonObject toJsonObject();

    /*!
     * \brief Loads data from a QJsonDocument into the PayerInfo object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the PayerInfo object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void emailChanged(const QString &email);
    void externalRememberMeIdChanged(const QString &externalRememberMeId);
    void buyerAccountNumberChanged(const QString &buyerAccountNumber);
    void salutationChanged(const QString &salutation);
    void firstNameChanged(const QString &firstName);
    void middleNameChanged(const QString &middleName);
    void lastNameChanged(const QString &lastName);
    void suffixChanged(const QString &suffix);
    void payerIdChanged(const QString &payerId);
    void phoneChanged(const QString &phone);
    void phoneTypeChanged(PhoneType phoneType);
    void birthDateChanged(const QDate &birthDate);
    void taxIdChanged(const QString &taxId);
    void taxIdTypeChanged(TaxIdType taxId);
    void countryCodeChanged(const QString &countryCode);
    void billingAddressChanged(Address *billingAddress);
    void shippingAddressChanged(const Address &shippingAddress);
    void shippingAddressChanged(ShippingAddress *shippingAddress);


protected:
    PayerInfoPrivate * const d_ptr;


private:
    Q_DISABLE_COPY(PayerInfo)
    Q_DECLARE_PRIVATE(PayerInfo)

};

}
}

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::PayerInfo::PhoneType)
Q_DECLARE_METATYPE(Geltan::PP::PayerInfo::TaxIdType)
#endif

#endif // PAYERINFO_H
