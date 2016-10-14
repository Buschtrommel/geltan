/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/fmfdetails.h
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


#ifndef FMFDETAILS_H
#define FMFDETAILS_H

#include <QObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class FMFDetailsPrivate;

/*!
 * \brief Contains details about a Fraud Management Filter.
 *
 * \ppPaymentsApi{fmf_details}
 *
 * \headerfile "" <Geltan/PP/Objects/fmfdetails.h>
 */
class GELTANSHARED_EXPORT FMFDetails : public QObject
{
    Q_OBJECT
    /*!
     * \brief Type of filter.
     *
     * \ppApiName{filter_type}
     *
     * \par Access functions:
     * <TABLE><TR><TD>FilterType</TD><TD>filterType() const</TD></TR><TR><TD>void</TD><TD>setFilterType(FilterType nFilterType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>filterTypeChanged(FilterType filterType)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::FMFDetails::FilterType filterType READ filterType NOTIFY filterTypeChanged)
    /*!
     * \brief Filter identifier.
     *
     * \ppApiName{filter_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>FilterIdentifier</TD><TD>filterId() const</TD></TR><TR><TD>void</TD><TD>setFilterId(FilterIdentifier nFilterId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>filterIdChanged(FilterIdentifier filterId)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::FMFDetails::FilterIdentifier filterId READ filterId NOTIFY filterIdChanged)
    /*!
     * \brief Name of the filter.
     *
     * \ppApiName{name}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>name() const</TD></TR><TR><TD>void</TD><TD>setName(const QString &nName)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>nameChanged(const QString &name)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    /*!
     * \brief Description of the filter.
     *
     * \ppApiName{description}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>description() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>descriptionChanged(const QString &description)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
public:
    /*!
     * \brief Constructs a new empty FMFDetails object.
     */
    explicit FMFDetails(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new empty FMFDetails object from JSON data.
     */
    FMFDetails(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new empty FMFDetails object from JSON data.
     */
    FMFDetails(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the FMFDetails object.
     */
    ~FMFDetails();

    /*!
     * \brief Type of filter.
     */
    enum FilterType {
        NO_FILTER_TYP   = 0,
        ACCEPT          = 1,
        PENDING         = 2,
        DENY            = 3,
        REPORT          = 4
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(FilterType)
#else
    Q_ENUMS(FilterType)
#endif


    /*!
     * \brief Identifier of filter.
     */
    enum FilterIdentifier {
        NO_FILTER_IDENTIFIER                    = 0,
        AVS_NO_MATCH                            = 1,
        AVS_PARTIAL_MATCH                       = 2,
        AVS_UNAVAILABLE_OR_UNSUPPORTED          = 3,
        CARD_SECURITY_CODE_MISMATCH             = 4,
        MAXIMUM_TRANSACTION_AMOUNT              = 5,
        UNCONFIRMED_ADDRESS                     = 6,
        COUNTRY_MONITOR                         = 7,
        LARGE_ORDER_NUMBER                      = 8,
        BILLING_OR_SHIPPING_ADDRESS_MISMATCH    = 9,
        RISKY_ZIP_CODE                          = 10,
        SUSPECTED_FREIGHT_FORWARDER_CHECK       = 11,
        TOTAL_PURCHASE_PRICE_MINIMUM            = 12,
        IP_ADDRESS_VELOCITY                     = 13,
        RISKY_EMAIL_ADDRESS_DOMAIN_CHECK        = 14,
        RISKY_BANK_IDENTIFICATION_NUMBER_CHECK  = 15,
        RISKY_IP_ADDRESS_RANGE                  = 16,
        PAYPAL_FRAUD_MODEL                      = 17
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(FilterIdentifier)
#else
    Q_ENUMS(FilterIdentifier)
#endif

    FilterType filterType() const;
    FilterIdentifier filterId() const;
    QString name() const;
    QString description() const;

    /*!
     * \brief Loads data from a QJsonDocument into the FMFDetails object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the FMFDetails object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void filterTypeChanged(FilterType filterType);
    void filterIdChanged(FilterIdentifier filterId);
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);

protected:
    const QScopedPointer<FMFDetailsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(FMFDetails)
    Q_DECLARE_PRIVATE(FMFDetails)

};

}
}
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::FMFDetails::FilterType)
Q_DECLARE_METATYPE(Geltan::PP::FMFDetails::FilterIdentifier)
#endif

#endif // FMFDETAILS_H
