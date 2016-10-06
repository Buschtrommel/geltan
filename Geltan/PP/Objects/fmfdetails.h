/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * fmfdetails.h
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
 * \headerfile "fmfdetails.h" <Geltan/PP/Objects/fmfdetails.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
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
     * <TABLE><TR><TD>QString</TD><TD>description() const</TD></TR><TR><TD>void</TD><TD>setDescription(const QString &nDescription)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>descriptionChanged(const QString &description)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
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
        NoFilterType    = 0,
        Accept          = 1,
        Pending         = 2,
        Deny            = 3,
        Report          = 4
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
        NoFilterIdentifier                  = 0,
        AvsNoMatch                          = 1,
        AvsParitalMatch                     = 2,
        AvsUnavailableOrUnsupported         = 3,
        CardSecurityCodeMismatch            = 4,
        MaximumTransactionAmount            = 5,
        UnconfirmedAddress                  = 6,
        CountryMonitor                      = 7,
        LargeOrderNumber                    = 8,
        BillingOrShippingAddressMismatch    = 9,
        RiskyZipCode                        = 10,
        SuspectedFreightForwardedCheck      = 11,
        TotalPurchasePriceMinimum           = 12,
        IpAddressVelocity                   = 13,
        RiskyEmailAddressDomainCheck        = 14,
        RiskyBankIdentificationNumberCheck  = 15,
        RiskyIpAddressRange                 = 16,
        PaypalFraudModel                    = 17
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
     * \brief Sets the type of filter.
     */
    void setFilterType(FilterType nFilterType);
    /*!
     * \brief Sets the filter identifier.
     */
    void setFilterId(FilterIdentifier nFilterId);
    /*!
     * \brief Sets the name of the filter.
     */
    void setName(const QString &nName);
    /*!
     * \brief Sets the description of the filter.
     */
    void setDescription(const QString &nDescription);

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
