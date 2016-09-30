/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payerinfo.cpp
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

#include "payerinfo_p.h"
#include <Geltan/PP/Objects/shippingaddress.h>
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


PayerInfo::PayerInfo(QObject *parent) :
    QObject(parent), d_ptr(new PayerInfoPrivate)
{
}


PayerInfo::PayerInfo(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new PayerInfoPrivate)
{
    loadFromJson(json);
}


PayerInfo::PayerInfo(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new PayerInfoPrivate)
{
    loadFromJson(json);
}


PayerInfo::~PayerInfo()
{
    delete d_ptr;
}


QString PayerInfo::email() const { Q_D(const PayerInfo); return d->email; }

void PayerInfo::setEmail(const QString &nEmail)
{
    Q_D(PayerInfo); 
    if (nEmail != d->email) {
        d->email = nEmail;
#ifdef QT_DEBUG
        qDebug() << "Changed email to" << d->email;
#endif
        Q_EMIT emailChanged(email());
    }
}




QString PayerInfo::externalRememberMeId() const { Q_D(const PayerInfo); return d->externalRememberMeId; }

void PayerInfo::setExternalRememberMeId(const QString &nExternalRememberMeId)
{
    Q_D(PayerInfo); 
    if (nExternalRememberMeId != d->externalRememberMeId) {
        d->externalRememberMeId = nExternalRememberMeId;
#ifdef QT_DEBUG
        qDebug() << "Changed externalRememberId to" << d->externalRememberMeId;
#endif
        Q_EMIT externalRememberMeIdChanged(externalRememberMeId());
    }
}




QString PayerInfo::buyerAccountNumber() const { Q_D(const PayerInfo); return d->buyerAccountNumber; }

void PayerInfo::setBuyerAccountNumber(const QString &nBuyerAccountNumber)
{
    Q_D(PayerInfo); 
    if (nBuyerAccountNumber != d->buyerAccountNumber) {
        d->buyerAccountNumber = nBuyerAccountNumber;
#ifdef QT_DEBUG
        qDebug() << "Changed buyerAccountNumber to" << d->buyerAccountNumber;
#endif
        Q_EMIT buyerAccountNumberChanged(buyerAccountNumber());
    }
}




QString PayerInfo::salutation() const { Q_D(const PayerInfo); return d->salutation; }

void PayerInfo::setSalutation(const QString &nSalutation)
{
    Q_D(PayerInfo); 
    if (nSalutation != d->salutation) {
        d->salutation = nSalutation;
#ifdef QT_DEBUG
        qDebug() << "Changed salutation to" << d->salutation;
#endif
        Q_EMIT salutationChanged(salutation());
    }
}




QString PayerInfo::firstName() const { Q_D(const PayerInfo); return d->firstName; }

void PayerInfo::setFirstName(const QString &nFirstName)
{
    Q_D(PayerInfo); 
    if (nFirstName != d->firstName) {
        d->firstName = nFirstName;
#ifdef QT_DEBUG
        qDebug() << "Changed firstName to" << d->firstName;
#endif
        Q_EMIT firstNameChanged(firstName());
    }
}




QString PayerInfo::middleName() const { Q_D(const PayerInfo); return d->middleName; }

void PayerInfo::setMiddleName(const QString &nMiddleName)
{
    Q_D(PayerInfo); 
    if (nMiddleName != d->middleName) {
        d->middleName = nMiddleName;
#ifdef QT_DEBUG
        qDebug() << "Changed middleName to" << d->middleName;
#endif
        Q_EMIT middleNameChanged(middleName());
    }
}




QString PayerInfo::lastName() const { Q_D(const PayerInfo); return d->lastName; }

void PayerInfo::setLastName(const QString &nLastName)
{
    Q_D(PayerInfo); 
    if (nLastName != d->lastName) {
        d->lastName = nLastName;
#ifdef QT_DEBUG
        qDebug() << "Changed lastName to" << d->lastName;
#endif
        Q_EMIT lastNameChanged(lastName());
    }
}




QString PayerInfo::suffix() const { Q_D(const PayerInfo); return d->suffix; }

void PayerInfo::setSuffix(const QString &nSuffix)
{
    Q_D(PayerInfo); 
    if (nSuffix != d->suffix) {
        d->suffix = nSuffix;
#ifdef QT_DEBUG
        qDebug() << "Changed suffix to" << d->suffix;
#endif
        Q_EMIT suffixChanged(suffix());
    }
}




QString PayerInfo::payerId() const { Q_D(const PayerInfo); return d->payerId; }

void PayerInfo::setPayerId(const QString &nPayerId)
{
    Q_D(PayerInfo); 
    if (nPayerId != d->payerId) {
        d->payerId = nPayerId;
#ifdef QT_DEBUG
        qDebug() << "Changed payerId to" << d->payerId;
#endif
        Q_EMIT payerIdChanged(payerId());
    }
}




QString PayerInfo::phone() const { Q_D(const PayerInfo); return d->phone; }

void PayerInfo::setPhone(const QString &nPhone)
{
    Q_D(PayerInfo); 
    if (nPhone != d->phone) {
        d->phone = nPhone;
#ifdef QT_DEBUG
        qDebug() << "Changed phone to" << d->phone;
#endif
        Q_EMIT phoneChanged(phone());
    }
}




PayerInfo::PhoneType PayerInfo::phoneType() const { Q_D(const PayerInfo); return d->phoneType; }

void PayerInfo::setPhoneType(PhoneType nPhoneType)
{
    Q_D(PayerInfo); 
    if (nPhoneType != d->phoneType) {
        d->phoneType = nPhoneType;
#ifdef QT_DEBUG
        qDebug() << "Changed phoneType to" << d->phoneType;
#endif
        Q_EMIT phoneTypeChanged(phoneType());
    }
}




QDate PayerInfo::birthDate() const { Q_D(const PayerInfo); return d->birthDate; }

void PayerInfo::setBirthDate(const QDate &nBirthDate)
{
    Q_D(PayerInfo); 
    if (nBirthDate != d->birthDate) {
        d->birthDate = nBirthDate;
#ifdef QT_DEBUG
        qDebug() << "Changed birthDate to" << d->birthDate;
#endif
        Q_EMIT birthDateChanged(birthDate());
    }
}



QString PayerInfo::taxId() const { Q_D(const PayerInfo); return d->taxId; }

void PayerInfo::setTaxId(const QString &nTaxId)
{
    Q_D(PayerInfo);
    if (nTaxId != d->taxId) {
        d->taxId = nTaxId;
#ifdef QT_DEBUG
        qDebug() << "Changed taxId to" << d->taxId;
#endif
        Q_EMIT taxIdChanged(taxId());
    }
}



PayerInfo::TaxIdType PayerInfo::taxIdType() const { Q_D(const PayerInfo); return d->taxIdType; }

void PayerInfo::setTaxIdType(TaxIdType nTaxIdType)
{
    Q_D(PayerInfo); 
    if (nTaxIdType != d->taxIdType) {
        d->taxIdType = nTaxIdType;
#ifdef QT_DEBUG
        qDebug() << "Changed taxId to" << d->taxIdType;
#endif
        Q_EMIT taxIdTypeChanged(taxIdType());
    }
}




QString PayerInfo::countryCode() const { Q_D(const PayerInfo); return d->countryCode; }

void PayerInfo::setCountryCode(const QString &nCountryCode)
{
    Q_D(PayerInfo); 
    if (nCountryCode != d->countryCode) {
        d->countryCode = nCountryCode;
#ifdef QT_DEBUG
        qDebug() << "Changed countryCode to" << d->countryCode;
#endif
        Q_EMIT countryCodeChanged(countryCode());
    }
}




Address *PayerInfo::billingAddress() const { Q_D(const PayerInfo); return d->billingAddress; }

void PayerInfo::setBillingAddress(Address *nBillingAddress)
{
    Q_D(PayerInfo); 
    if (nBillingAddress != d->billingAddress) {
        d->billingAddress = nBillingAddress;
#ifdef QT_DEBUG
        qDebug() << "Changed billingAddress to" << d->billingAddress;
#endif
        Q_EMIT billingAddressChanged(billingAddress());
    }
}





ShippingAddress *PayerInfo::shippingAddress() const { Q_D(const PayerInfo); return d->shippingAddress; }

void PayerInfo::setShippingAddress(ShippingAddress *nShippingAddress)
{
    Q_D(PayerInfo);
    if (nShippingAddress != d->shippingAddress) {
        d->shippingAddress = nShippingAddress;
#ifdef QT_DEBUG
        qDebug() << "Changed shippingAddress to" << d->shippingAddress;
#endif
        Q_EMIT shippingAddressChanged(shippingAddress());
    }
}




QVariantMap PayerInfo::toVariant()
{
    Q_D(PayerInfo);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("email"), email(), 127);
    d->addStringToVariantMap(&map, QStringLiteral("external_remember_me_id"), externalRememberMeId());
    d->addStringToVariantMap(&map, QStringLiteral("buyer_account_number"), buyerAccountNumber());
    d->addPhoneNumberToVariantMap(&map, QStringLiteral("phone"), phone());

    QString pt; // phone type

    switch(phoneType()) {
    case Home:
        pt = QStringLiteral("HOME");
        break;
    case Work:
        pt = QStringLiteral("WORK");
        break;
    case Mobile:
        pt = QStringLiteral("MOBILE");
        break;
    case Other:
        pt = QStringLiteral("OTHER");
        break;
    default:
        break;
    }

    d->addStringToVariantMap(&map, QStringLiteral("phone_type"), pt);
    d->addStringToVariantMap(&map, QStringLiteral("birth_date"), birthDate().toString(QStringLiteral("yyyy-MM-dd")));
    d->addStringToVariantMap(&map, QStringLiteral("tax_id"), taxId(), 14);

    QString tit; // tax id type

    switch(taxIdType()) {
    case BR_CPF:
        tit = QStringLiteral("BR_CPF");
        break;
    case BR_CNPJ:
        tit = QStringLiteral("BR_CNPJ");
        break;
    default:
        break;
    }

    d->addStringToVariantMap(&map, QStringLiteral("tax_id_type"), tit);
    d->addStringToVariantMap(&map, QStringLiteral("country_code"), countryCode(), 2);

    if (billingAddress()) {
        d->addMapToVariantMap(&map, QStringLiteral("billing_address"), billingAddress()->toVariant());
    }

    return map;
}



void PayerInfo::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void PayerInfo::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setEmail(json.value(QStringLiteral("email")).toString());

    setExternalRememberMeId(json.value(QStringLiteral("external_remember_me_id")).toString());

    setBuyerAccountNumber(json.value(QStringLiteral("buyer_account_number")).toString());

    setSalutation(json.value(QStringLiteral("salutation")).toString());

    setFirstName(json.value(QStringLiteral("first_name")).toString());

    setMiddleName(json.value(QStringLiteral("middle_name")).toString());

    setLastName(json.value(QStringLiteral("last_name")).toString());

    setSuffix(json.value(QStringLiteral("suffix")).toString());

    setPayerId(json.value(QStringLiteral("payer_id")).toString());

    setPhone(json.value(QStringLiteral("phone")).toString());

    const QString pt = json.value(QStringLiteral("phone_type")).toString();
    if (pt == QLatin1String("HOME")) {
        setPhoneType(Home);
    } else if (pt == QLatin1String("WORK")) {
        setPhoneType(Work);
    } else if (pt == QLatin1String("Mobile")) {
        setPhoneType(Mobile);
    } else if (pt == QLatin1String("OTHER")) {
        setPhoneType(Other);
    } else {
        setPhoneType(NoPhoneType);
    }

    setTaxId(json.value(QStringLiteral("tax_id")).toString());

    const QString tit = json.value(QStringLiteral("tax_id_type")).toString();
    if (tit == QLatin1String("BR_CPF")) {
        setTaxIdType(BR_CPF);
    } else if (tit == QLatin1String("BR_CNPJ")) {
        setTaxIdType(BR_CNPJ);
    } else {
        setTaxIdType(NoTaxIdType);
    }

    setCountryCode(json.value(QStringLiteral("country_code")).toString());

    const QJsonObject bao = json.value(QStringLiteral("billing_address")).toObject();
    Address *oldBao = billingAddress();
    if (!bao.isEmpty()) {
        if (oldBao) {
            oldBao->loadFromJson(bao);
        } else {
            setBillingAddress(new Address(bao, this));
        }
    } else {
        setBillingAddress(nullptr);
        delete oldBao;
    }

    const QJsonObject sao = json.value(QStringLiteral("shipping_address")).toObject();
    ShippingAddress *oldSao = shippingAddress();
    if (!sao.isEmpty()) {
        if (oldSao) {
            oldSao->loadFromJson(sao);
        } else {
            setShippingAddress(new ShippingAddress(sao, this));
        }
    } else {
        setShippingAddress(nullptr);
        delete oldSao;
    }
}
