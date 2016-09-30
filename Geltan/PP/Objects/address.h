/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * address.h
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

#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class AddressPrivate;

/*!
 * \brief Contains basic address data.
 *
 * Some properties have a limited length. When using toVariant() or toJsonObject(), these limitations
 * will be applied to the stored values.
 *
 * \ppPaymentsApi{address}
 *
 * \headerfile "address.h" <Geltan/PP/Objects/address.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Address : public QObject
{
    Q_OBJECT
    /*!
     * \brief Line 1 of the address (e.g., Number, street, etc).
     *
     * 100 characters max.
     *
     * \ppApiName{line1}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>line1() const</TD></TR><TR><TD>void</TD><TD>setLine1(const QString &nLine1)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>line1Changed(const QString &line1)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString line1 READ line1 WRITE setLine1 NOTIFY line1Changed)
    /*!
     * \brief Line 2 of the address (e.g., Suite, apt #, etc).
     *
     * 100 characters max.
     *
     * \ppApiName{line2}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>line2() const</TD></TR><TR><TD>void</TD><TD>setLine2(const QString &nLine2)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>line2Changed(const QString &line2)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString line2 READ line2 WRITE setLine2 NOTIFY line2Changed)
    /*!
     * \brief City name.
     *
     * 50 characters max.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>city() const</TD></TR><TR><TD>void</TD><TD>setCity(const QString &nCity)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>cityChanged(const QString &city)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)
    /*!
     * \brief 2-letter country code.
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
     * \brief Zip code or equivalent.
     *
     * Usually required for countries that have them. 20 characters max. Required in certain countries.
     *
     * \ppApiName{country_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>postalCode() const</TD></TR><TR><TD>void</TD><TD>setPostalCode(const QString &nPostalCode)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>postalCodeChanged(const QString &postalCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString postalCode READ postalCode WRITE setPostalCode NOTIFY postalCodeChanged)
    /*!
     * \brief 2-letter code for US states, and equivalent for other countries.
     *
     * 100 characters max.
     *
     * \ppApiName{state}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>state() const</TD></TR><TR><TD>void</TD><TD>setState(const QString &nState)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(const QString &state)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    /*!
     * \brief Phone number in E.123 format.
     *
     * 50 characters max.
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
     * \brief Address normalization status, returned only for payers from Brazil.
     *
     * \ppApiName{normalization_status}
     *
     * \par Access functions:
     * <TABLE><TR><TD>NormalizationStatus</TD><TD>normalizationStatus() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>normalizationStatusChanged(NormalizationStatus normalizationStatus)</TD></TR></TABLE>
     */
    Q_PROPERTY(NormalizationStatus normalizationStatus READ normalizationStatus NOTIFY normalizationStatusChanged)
    /*!
     * \brief Address status.
     *
     * \ppApiName{status}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Status</TD><TD>status() const</TD></TR><TR><TD>void</TD><TD>setStatus(Status nStatus)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>statusChanged(Status status)</TD></TR></TABLE>
     */
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    /*!
     * \brief Type of address.
     *
     * E.g., HOME_OR_WORK, GIFT etc.
     *
     * \ppApiName{type}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>type() const</TD></TR><TR><TD>void</TD><TD>setType(const QString &nType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>typeChanged(const QString &type)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
public:
    /*!
     * \brief Constructs a new empty Address object.
     */
    explicit Address(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Address object from JSON data.
     */
    Address(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Address object from JSON data.
     */
    Address(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Address object.
     */
    ~Address();

    /*!
     * \brief Address normalization status, returned only for payers from Brazil.
     */
    enum NormalizationStatus {
        Unknown                     = 0,
        UnnormalizedUserPreferred   = 1,
        Normalized                  = 2,
        Unnormalized                = 3
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(NormalizationStatus)
#else
    Q_ENUMS(NormalizationStatus)
#endif

    /*!
     * \brief Address status.
     */
    enum Status {
        NoStatus    = 0,
        Confirmed   = 1,
        Unconfirmed = 2
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(Status)
#else
    Q_ENUMS(Status)
#endif

    QString line1() const;
    QString line2() const;
    QString city() const;
    QString countryCode() const;
    QString postalCode() const;
    QString state() const;
    QString phone() const;
    NormalizationStatus normalizationStatus() const;
    Status status() const;
    QString type() const;

    void setLine1(const QString &nLine1);
    void setLine2(const QString &nLine2);
    void setCity(const QString &nCity);
    void setCountryCode(const QString &nCountryCode);
    void setPostalCode(const QString &nPostalCode);
    void setState(const QString &nState);
    void setPhone(const QString &nPhone);
    /*!
     * \brief Sets the address normalization status.
     */
    void setNormalizationStatus(NormalizationStatus nNormalizationStatus);
    void setStatus(Status nStatus);
    void setType(const QString &nType);


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
     * \brief Loads data from a QJsonDocument into the Address object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Address object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void line1Changed(const QString &line1);
    void line2Changed(const QString &line2);
    void cityChanged(const QString &city);
    void countryCodeChanged(const QString &countryCode);
    void postalCodeChanged(const QString &postalCode);
    void stateChanged(const QString &state);
    void phoneChanged(const QString &phone);
    void normalizationStatusChanged(NormalizationStatus normalizationStatus);
    void statusChanged(Status status);
    void typeChanged(const QString &type);

protected:
    const QScopedPointer<AddressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Address)
    Q_DECLARE_PRIVATE(Address)

};

}
}
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::Address::NormalizationStatus)
Q_DECLARE_METATYPE(Geltan::PP::Address::Status)
#endif

#endif // ADDRESS_H
