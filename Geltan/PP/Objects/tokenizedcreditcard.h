/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * tokenizedcreditcard.h
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

#ifndef TOKENIZEDCREDITCARD_H
#define TOKENIZEDCREDITCARD_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {
namespace PP {

class TokenizedCreditCardPrivate;

/*!
 * \brief Contains information about a tokenized credit card.
 *
 * A tokenized credit card is a credit card, that has been stored in the PayPal vault.
 *
 * \ppPaymentsApi{tokenized_credit_card}
 *
 * \headerfile "" <Geltan/PP/Objects/tokenizedcreditcard.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT TokenizedCreditCard : public QObject
{
    Q_OBJECT
    /*!
     * \brief ID of credit card previously stored using /vault/credit-card.
     *
     * \ppApiName{credit_card_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>creditCardId() const</TD></TR><TR><TD>void</TD><TD>setCreditCardId(const QString &nCreditCardId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>creditCardIdChanged(const QString &creditCardId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString creditCardId READ creditCardId WRITE setCreditCardId NOTIFY creditCardIdChanged)
    /*!
     * \brief A unique identifier that you can assign and track when storing a credit card or using a stored credit card. 
     *
     * This ID can help to avoid unintentional use or misuse of credit cards. This ID can be any value you 
     * would like to associate with the saved card, such as a UUID, username, or email address. Required when
     * using a stored credit card if a payer_id was originally provided when storing the credit card in vault.
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
     * \brief Last four digits of the stored credit card number.
     *
     * \ppApiName{last4}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>last4() const</TD></TR><TR><TD>void</TD><TD>setLast4(const QString &nLast4)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>last4Changed(const QString &last4)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString last4 READ last4 WRITE setLast4 NOTIFY last4Changed)
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
public:
    /*!
     * \brief Constructs a new empty TokenizedCreditCard object.
     */
    explicit TokenizedCreditCard(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new TokenizedCreditCard object from JSON data.
     */
    TokenizedCreditCard(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new TokenizedCreditCard object from JSON data.
     */
    TokenizedCreditCard(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the TokenizedCreditCard object.
     */
    ~TokenizedCreditCard();


    QString creditCardId() const;
    QString payerId() const;
    QString last4() const;
    PayPal::CreditCardType type() const;
    quint8 expireMonth() const;
    quint16 expireYear() const;


    void setCreditCardId(const QString &nCreditCardId);
    void setPayerId(const QString &nPayerId);
    void setLast4(const QString &nLast4);
    void setType(PayPal::CreditCardType nType);
    void setExpireMonth(quint8 nExpireMonth);
    void setExpireYear(quint16 nExpireYear);


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
     * \brief Loads data from a QJsonDocument into the TokenizedCreditCard object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the TokenizedCreditCard object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void creditCardIdChanged(const QString &creditCardId);
    void payerIdChanged(const QString &payerId);
    void last4Changed(const QString &last4);
    void typeChanged(PayPal::CreditCardType type);
    void expireMonthChanged(quint8 expireMonth);
    void expireYearChanged(quint16 expireYear);

protected:
    TokenizedCreditCardPrivate * const d_ptr;


private:
    Q_DISABLE_COPY(TokenizedCreditCard)
    Q_DECLARE_PRIVATE(TokenizedCreditCard)

};

}
}

#endif // TOKENIZEDCREDITCARD_H
