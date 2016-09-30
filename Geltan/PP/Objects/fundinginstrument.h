/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payer.h
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

#ifndef FUNDINGINSTRUMENT_H
#define FUNDINGINSTRUMENT_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class FundingInstrumentPrivate;
class CreditCard;
class TokenizedCreditCard;
class BillingInstrument;

/*!
 * \brief A resource representing a Payer's funding instrument.
 *
 * An instance of this schema is valid if and only if it is valid against exactly one of these supported properties.
 *
 * \ppPaymentsApi{funding_instrument}
 *
 * \headerfile "fundinginstrument.h" <Geltan/PP/Objects/fundinginstrument.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-12
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT FundingInstrument : public QObject
{
    Q_OBJECT
    /*!
     * \brief Represents a credit card to fund a payment.
     *
     * \ppApiName{credit_card}
     *
     * \par Access functions:
     * <TABLE><TR><TD>CreditCard*</TD><TD>creditCard() const</TD></TR><TR><TD>void</TD><TD>setCreditCard(CreditCard *nCreditCard)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>creditCardChanged(CreditCard *creditCard)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::CreditCard *creditCard READ creditCard WRITE setCreditCard NOTIFY creditCardChanged)
    /*!
     * \brief A resource representing a credit card that can be used to fund a payment.
     *
     * \ppApiName{credit_card_token}
     *
     * \par Access functions:
     * <TABLE><TR><TD>TokenizedCreditCard*</TD><TD>creditCardToken() const</TD></TR><TR><TD>void</TD><TD>setCreditCardToken(TokenizedCreditCard *nCreditCardToken)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>creditCardTokenChanged(TokenizedCreditCard *creditCardToken)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::TokenizedCreditCard *creditCardToken READ creditCardToken WRITE setCreditCardToken NOTIFY creditCardTokenChanged)
    /*!
     * \brief Billing instrument used to charge the payer.
     *
     * \ppApiName{billing}
     *
     * \par Access functions:
     * <TABLE><TR><TD>BillingInstrument*</TD><TD>billing() const</TD></TR><TR><TD>void</TD><TD>setBilling(BillingInstrument *nBilling)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>billingChanged(BillingInstrument *billing)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::BillingInstrument *billing READ billing WRITE setBilling NOTIFY billingChanged)
public:
    /*!
     * \brief Constructs a new FundingInstrument object.
     */
    explicit FundingInstrument(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new FundingInstrument object from JSON data.
     */
    FundingInstrument(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new FundingInstrument object from JSON data.
     */
    FundingInstrument(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the FundingInstrument object.
     */
    ~FundingInstrument();

    CreditCard *creditCard() const;
    TokenizedCreditCard *creditCardToken() const;
    BillingInstrument *billing() const;

    void setCreditCard(CreditCard *nCreditCard);
    void setCreditCardToken(TokenizedCreditCard *nCreditCardToken);
    void setBilling(BillingInstrument *nBilling);

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
     * \brief Loads data from a QJsonDocument into the FundingInstrument object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the FundingInstrument object.
     */
    void loadFromJson(const QJsonObject &json);

Q_SIGNALS:
    void creditCardChanged(CreditCard *creditCard);
    void creditCardTokenChanged(TokenizedCreditCard *creditCardToken);
    void billingChanged(BillingInstrument *billing);

protected:
    const QScopedPointer<FundingInstrumentPrivate> d_ptr;

private:
    Q_DISABLE_COPY(FundingInstrument)
    Q_DECLARE_PRIVATE(FundingInstrument)

};

}
}


#endif // FUNDINGINSTRUMENT_H
