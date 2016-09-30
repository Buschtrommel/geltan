/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payee.h
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

#ifndef PAYEE_H
#define PAYEE_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class PayeePrivate;

/*!
 * \brief The Payee class.
 */
class GELTANSHARED_EXPORT Payee : public QObject
{
    Q_OBJECT
    /*!
     * \brief Email address associated with the payee's PayPal account.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>email() const</TD></TR><TR><TD>void</TD><TD>setEmail(const QString &nEmail)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>emailChanged(const QString &email)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    /*!
     * \brief Encrypted PayPal account identfier for the payee.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>merchantId() const</TD></TR><TR><TD>void</TD><TD>setMerchantId(const QString &nMerchantId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>merchantIdChanged(const QString &merchantId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString merchantId READ merchantId WRITE setMerchantId NOTIFY merchantIdChanged)
public:
    /*!
     * \brief Constructs a new Payee object.
     */
    explicit Payee(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Payee object from JSON data.
     */
    Payee(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Payee object from JSON data.
     */
    Payee(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Payee object.
     */
    ~Payee();

    QString email() const;
    QString merchantId() const;

    void setEmail(const QString &nEmail);
    void setMerchantId(const QString &nMerchantId);

    /*!
     * \brief Loads data from a QJsonDocument into the Payee object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Payee object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void emailChanged(const QString &email);
    void merchantIdChanged(const QString &merchantId);

protected:
    const QScopedPointer<PayeePrivate> d_ptr;

private:
    Q_DISABLE_COPY(Payee)
    Q_DECLARE_PRIVATE(Payee)

};

}
}


#endif // PAYEE_H
