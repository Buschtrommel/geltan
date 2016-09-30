/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * paymentoptions.h
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

#ifndef PAYMENTOPTIONS_H
#define PAYMENTOPTIONS_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class PaymentOptionsPrivate;

/*!
 * \brief Contains information about allowed payment options.
 *
 * \ppPaymentsApi{payment_options}
 *
 * \headerfile "" <Geltan/PP/Objects/paymentoptions.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-12
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT PaymentOptions : public QObject
{
    Q_OBJECT
    /*!
     * \brief Payment method requested for this purchase unit.
     *
     * \ppApiName{allowed_payment_method}
     *
     * \par Access functions:
     * <TABLE><TR><TD>AllowedPaymentMethodType</TD><TD>allowedPaymentMethod() const</TD></TR><TR><TD>void</TD><TD>setAllowedPaymentMethod(AllowedPaymentMethodType nAllowedPaymentMethod)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>allowedPaymentMethodChanged(AllowedPaymentMethodType allowedPaymentMethod)</TD></TR></TABLE>
     */
    Q_PROPERTY(AllowedPaymentMethodType allowedPaymentMethod READ allowedPaymentMethod WRITE setAllowedPaymentMethod NOTIFY allowedPaymentMethodChanged)
public:
    /*!
     * \brief Constructs a new empty PaymentOptions object.
     */
    explicit PaymentOptions(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new PaymentOptions object from JSON data.
     */
    PaymentOptions(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new PaymentOptions object from JSON data.
     */
    PaymentOptions(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the PaymentOptions object.
     */
    ~PaymentOptions();

    /*!
     * \brief Type of payment method.
     */
    enum AllowedPaymentMethodType {
        NoAllowedPaymentMethod  = 0,
        Unrestricted            = 1,
        InstantFundingSource    = 2,
        ImmediatePay            = 3
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(AllowedPaymentMethodType)
#else
    Q_ENUMS(AllowedPaymentMethodType)
#endif

    AllowedPaymentMethodType allowedPaymentMethod() const;
    void setAllowedPaymentMethod(AllowedPaymentMethodType nAllowedPaymentMethod);


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
     * \brief Loads data from a QJsonDocument into the PaymentOptions object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the PaymentOptions object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void allowedPaymentMethodChanged(AllowedPaymentMethodType allowedPaymentMethod);

protected:
    const QScopedPointer<PaymentOptionsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(PaymentOptions)
    Q_DECLARE_PRIVATE(PaymentOptions)

};

}
}

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::PaymentOptions::AllowedPaymentMethodType)
#endif


#endif // PAYMENTOPTIONS_H
