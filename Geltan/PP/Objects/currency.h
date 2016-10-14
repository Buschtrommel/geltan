/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/currency.h
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

#ifndef CURRENCY_H
#define CURRENCY_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class CurrencyPrivate;

/*!
 * \brief Base object for all financial value related fields (balance, payment due, etc.)
 *
 * \ppPaymentsApi{currency}
 *
 * \headerfile "currency.h" <Geltan/PP/Objects/currency.h>
 */
class GELTANSHARED_EXPORT Currency : public QObject
{
    Q_OBJECT
    /*!
     * \brief 3 letter currency code as defined by <a href="https://en.wikipedia.org/wiki/ISO_4217">ISO 4217</a>.
     *
     * \ppApiName{currency}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>currency() const</TD></TR><TR><TD>void</TD><TD>setCurrency(const QString &nCurrency)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>currencyChanged(const QString &currency)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString currency READ currency WRITE setCurrency NOTIFY currencyChanged)
    /*!
     * \brief Amount up to N digit after the decimals separator as defined in <a href="https://en.wikipedia.org/wiki/ISO_4217">ISO 4217</a> for the appropriate currency code.
     *
     * \ppApiName{value}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>value() const</TD></TR><TR><TD>void</TD><TD>setValue(float nValue)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>valueChanged(float value)</TD></TR></TABLE>
     */
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
public:
    /*!
     * \brief Constructs a new empty Currency object.
     */
    explicit Currency(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Currency object from JSON data.
     */
    Currency(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Currency object from JSON data.
     */
    Currency(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Currency object.
     */
    ~Currency();


    QString currency() const;
    float value() const;


    void setCurrency(const QString &nCurrency);
    void setValue(float nValue);


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
     * \brief Loads data from a QJsonDocument into the Currency object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Currency object.
     */
    void loadFromJson(const QJsonObject &json);

Q_SIGNALS:
    void currencyChanged(const QString &currency);
    void valueChanged(float value);


protected:
    const QScopedPointer<CurrencyPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Currency)
    Q_DECLARE_PRIVATE(Currency)

};

}
}

#endif // CURRENCY_H
