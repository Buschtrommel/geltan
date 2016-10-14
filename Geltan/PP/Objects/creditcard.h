/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/creditcard.h
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

#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <QObject>
#include <QDateTime>
#include <QVariantMap>
#include <QJsonObject>
#include <QUrl>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {
namespace PP {

class Address;
class Link;
class CreditCardPrivate;

/*!
 * \brief Contains information about a credit card.
 *
 * \ppPaymentsApi{credit_card}
 *
 * \headerfile "creditcard.h" <Geltan/PP/Objects/creditcard.h>
 */
class GELTANSHARED_EXPORT CreditCard : public QObject
{
    Q_OBJECT
    /*!
     * \brief Credit card number.
     *
     * Numeric characters only, with no spaces or punctuation. The string must conform with modulo and length
     * required by each credit card type.
     *
     * \ppApiName{number}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>number() const</TD></TR><TR><TD>void</TD><TD>setNumber(const QString &nNumber)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>numberChanged(const QString &number)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
    /*!
     * \brief Credit card type.
     *
     * \ppApiName{type}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::CreditCardType</TD><TD>type() const</TD></TR><TR><TD>void</TD><TD>setType(PayPal::CreditCardType nType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>typeChanged(PayPal::CreditCardType type)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::CreditCardType type READ type WRITE setType NOTIFY typeChanged)
    /*!
     * \brief Expiration month with no leading zero.
     *
     * \ppApiName{expire_month}
     *
     * \par Access functions:
     * <TABLE><TR><TD>quint8</TD><TD>expireMonth() const</TD></TR><TR><TD>void</TD><TD>setExpireMonth(quint8 nExpireMonth)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>expireMonthChanged(quint8 expireMonth)</TD></TR></TABLE>
     */
    Q_PROPERTY(quint8 expireMonth READ expireMonth WRITE setExpireMonth NOTIFY expireMonthChanged)
    /*!
     * \brief 4-digit expiration year.
     *
     * \ppApiName{expire_year}
     *
     * \par Access functions:
     * <TABLE><TR><TD>quint16</TD><TD>expireYear() const</TD></TR><TR><TD>void</TD><TD>setExpireYear(quint16 nExpireYear)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>expireYearChanged(quint16 expireYear)</TD></TR></TABLE>
     */
    Q_PROPERTY(quint16 expireYear READ expireYear WRITE setExpireYear NOTIFY expireYearChanged)
    /*!
     * \brief 3-4 digit card validation code.
     *
     * \ppApiName{cvv2}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>cvv2() const</TD></TR><TR><TD>void</TD><TD>setCvv2(const QString &nCvv2)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>cvv2Changed(const QString &cvv2)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString cvv2 READ cvv2 WRITE setCvv2 NOTIFY cvv2Changed)
    /*!
     * \brief Cardholder's first name.
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
     * \brief Cardholder's last name.
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
     * \brief Billing Address associated with this card.
     *
     * Contains a pointer to an Address object, if any, otherwise contains a nullptr. If created internally, the Address object will be a child of
     * the CreditCard object and will be destroyed on the parent's destruction.
     *
     * \ppApiName{billing_address}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Address*</TD><TD>billingAddress() const</TD></TR><TR><TD>void</TD><TD>setBillingAddress(Address *nBillingAddress)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>billingAddressChanged(Address *billingAddress)</TD></TR></TABLE>
     */
    Q_PROPERTY(Address *billingAddress READ billingAddress WRITE setBillingAddress NOTIFY billingAddressChanged)
    /*!
     * \brief A unique identifier of the customer to whom this bank account belongs.
     *
     * Generated and provided by the facilitator. This is now used in favor of payer_id when creating or using 
     * a stored funding instrument in the vault.
     *
     * \ppApiName{external_customer_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>externalCustomerId() const</TD></TR><TR><TD>void</TD><TD>setExternalCustomerId(const QString &nExternalCustomerId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>externalCustomerIdChanged(const QString &externalCustomerId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString externalCustomerId READ externalCustomerId WRITE setExternalCustomerId NOTIFY externalCustomerIdChanged)
    /*!
     * \brief State of the credit card funding instrument.
     *
     * \ppApiName{state}
     *
     * \par Access functions:
     * <TABLE><TR><TD>State</TD><TD>state() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(State state)</TD></TR></TABLE>
     */
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    /*!
     * \brief Funding instrument expiration date.
     *
     * \ppApiName{valid_until}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>validUntil() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>validUntilChanged(const QDateTime &validUntil)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime validUntil READ validUntil NOTIFY validUntilChanged)
    /*!
     * \brief List of <a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> Link related to this call.
     *
     * \ppApiName{links}
     *
     * \sa getLink(), getLinkURL()
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Link*></TD><TD>links() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>linksChanged(const QList<Link*> &links)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Link*> links READ links NOTIFY linksChanged)
public:
    /*!
     * \brief Constructs a new empty CreditCard object.
     */
    explicit CreditCard(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new CreditCard object from JSON data.
     */
    CreditCard(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new CreditCard object from JSON data.
     */
    CreditCard(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the CreditCard object.
     */
    ~CreditCard();

    /*!
     * \brief State of the credit card funding instrument.
     */
    enum State {
        NoState = 0,
        Ok      = 1,
        Expired = 2
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(State)
#else
    Q_ENUMS(State)
#endif


    QString number() const;
    PayPal::CreditCardType type() const;
    quint8 expireMonth() const;
    quint16 expireYear() const;
    QString cvv2() const;
    QString firstName() const;
    QString lastName() const;
    Address *billingAddress() const;
    QString externalCustomerId() const;
    State state() const;
    QDateTime validUntil() const;
    QList<Link*> links() const;


    void setNumber(const QString &nNumber);
    void setType(PayPal::CreditCardType nType);
    void setExpireMonth(quint8 nExpireMonth);
    void setExpireYear(quint16 nExpireYear);
    void setCvv2(const QString &nCvv2);
    void setFirstName(const QString &nFirstName);
    void setLastName(const QString &nLastName);
    void setBillingAddress(Address *nBillingAddress);
    void setExternalCustomerId(const QString &nExternalCustomerId);
    /*!
     * \brief Sets the state of the credit card funding instrument.
     */
    void setState(State nState);
    /*!
     * \brief Sets the funding instrument expiration date.
     */
    void setValidUntil(const QDateTime &nValidUntil);
    /*!
     * \brief Sets the HATEOAS links for realted calls.
     */
    void setLinks(const QList<Link*> &nLinks);

    /*!
     * \brief Returns the URL of the Link in the list of <a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> links defined by \a rel.
     *
     * If no Link can be found, the returned URL will be invalid.
     */
    Q_INVOKABLE QUrl getLinkURL(const QString &rel) const;

    /*!
     * \brief Returns the Link in the list of <a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> links defined by \a rel.
     *
     * If no Link can be found, a \c nullptr will be returned.
     */
    Q_INVOKABLE Link* getLink(const QString &rel) const;


    /*!
     * \brief Returns a QVariantMap containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API. Will only contain properties that are not read only.
     */
    QVariantMap toVariant();

    /*!
     * \brief Returns a QJsonObject containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API. Will only contain properties that are not read only.
     */
    QJsonObject toJsonObject();

    /*!
     * \brief Loads data from a QJsonDocument into the CreditCard object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the CreditCard object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void numberChanged(const QString &number);
    void typeChanged(PayPal::CreditCardType type);
    void expireMonthChanged(quint8 expireMonth);
    void expireYearChanged(quint16 expireYear);
    void cvv2Changed(const QString &cvv2);
    void firstNameChanged(const QString &firstName);
    void lastNameChanged(const QString &lastName);
    void billingAddressChanged(Address *billingAddress);
    void externalCustomerIdChanged(const QString &externalCustomerId);
    void stateChanged(State state);
    void validUntilChanged(const QDateTime &validUntil);
    void linksChanged(const QList<Link*> &links);


protected:
    const QScopedPointer<CreditCardPrivate> d_ptr;

private:
    Q_DISABLE_COPY(CreditCard)
    Q_DECLARE_PRIVATE(CreditCard)

};

}
}
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::CreditCard::State)
#endif

#endif // CREDITCARD_H
