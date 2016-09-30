/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * shippingaddress.h
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

#ifndef SHIPPINGADDRESS_H
#define SHIPPINGADDRESS_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/Objects/address.h>

namespace Geltan {
namespace PP {

class ShippingAddressPrivate;


/*!
 * \brief Extended Address object used as shipping address in a payment.
 *
 * \ppPaymentsApi{shipping_address}
 *
 * \headerfile "" <Geltan/PP/Objects/shippingaddress.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT ShippingAddress : public Address
{
    Q_OBJECT
    /*!
     * \brief Name of the recipient at this address.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>recipientName() const</TD></TR><TR><TD>void</TD><TD>setRecipientName(const QString &nRecipientName)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>recipientNameChanged(const QString &recipientName)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString recipientName READ recipientName WRITE setRecipientName NOTIFY recipientNameChanged)
public:
    /*!
     * \brief Constructs a new empty ShippingAddress object.
     */
    explicit ShippingAddress(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new ShippingAddress object from JSON data.
     */
    ShippingAddress(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new ShippingAddress object from JSON data.
     */
    ShippingAddress(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the ShippingAddress object.
     */
    ~ShippingAddress();


    QString recipientName() const;
    void setRecipientName(const QString &nRecipientName);


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
     * \brief Loads data from a QJsonDocument into the ShippingAddress object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the ShippingAddress object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void recipientNameChanged(const QString &recipientName);

protected:
    const QScopedPointer<ShippingAddressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(ShippingAddress)
    Q_DECLARE_PRIVATE(ShippingAddress)

};

}
}


#endif // SHIPPINGADDRESS_H
