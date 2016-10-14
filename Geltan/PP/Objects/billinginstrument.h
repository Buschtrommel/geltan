/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/billinginstrument.h
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

#ifndef BILLINGINSTRUMENT_H
#define BILLINGINSTRUMENT_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class InstallmentDescription;
class BillingInstrumentPrivate;

/*!
 * \brief Contains information about a billing instrument.
 *
 * \ppPaymentsApi{billing_instrument}
 *
 * \headerfile "billinginstrument.h" <Geltan/PP/Objects/billinginstrument.h>
 */
class GELTANSHARED_EXPORT BillingInstrument : public QObject
{
    Q_OBJECT
    /*!
     * \brief Identifier of the instrument in PayPal Wallet
     *
     * \ppApiName{billing_agreement_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>billingAgreementId() const</TD></TR><TR><TD>void</TD><TD>setBillingAgreementId(const QString &nBillingAgreementId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>billingAgreementIdChanged(const QString &billingAgreementId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString billingAgreementId READ billingAgreementId WRITE setBillingAgreementId NOTIFY billingAgreementIdChanged)
    /*!
     * \brief A resource describing an installment.
     *
     * Contains a pointer to a InstallmentDescription object, if any, otherwise returns a nullptr.
     * Setting a new InstallmentDescription object, a current one will not be destroyed. If the old one
     * was a child of the BillingInstrument object, it will be destroyed on the parent's destruction.
     *
     * \ppApiName{selected_installment_option}
     *
     * \par Access functions:
     * <TABLE><TR><TD>InstallmentDescription*</TD><TD>selectedInstallmentOption() const</TD></TR><TR><TD>void</TD><TD>setSelectedInstallmentOption(InstallmentDescription *nSelectedInstallmentOption)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>selectedInstallmentOptionChanged(InstallmentDescription *selectedInstallmentOption)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::InstallmentDescription *selectedInstallmentOption READ selectedInstallmentOption WRITE setSelectedInstallmentOption NOTIFY selectedInstallmentOptionChanged)
public:
    /*!
     * \brief Constructs a new empty BillingInstrument object.
     */
    explicit BillingInstrument(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new BillingInstrument object from JSON data.
     */
    BillingInstrument(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new BillingInstrument object from JSON data.
     */
    BillingInstrument(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the BillingInstrument object.
     */
    ~BillingInstrument();


    QString billingAgreementId() const;
    InstallmentDescription *selectedInstallmentOption() const;


    void setBillingAgreementId(const QString &nBillingAgreementId);
    void setSelectedInstallmentOption(InstallmentDescription *nSelectedInstallmentOption);


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
     * \brief Loads data from a QJsonDocument into the BillingInstrument object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the BillingInstrument object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void billingAgreementIdChanged(const QString &billingAgreementId);
    void selectedInstallmentOptionChanged(InstallmentDescription *selectedInstallmentOption);

protected:
    const QScopedPointer<BillingInstrumentPrivate> d_ptr;


private:
    Q_DISABLE_COPY(BillingInstrument)
    Q_DECLARE_PRIVATE(BillingInstrument)

};

}
}

#endif // BILLINGINSTRUMENT_H
