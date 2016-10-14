/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/installmentdescription.h
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

#ifndef INSTALLMENTDESCRIPTION_H
#define INSTALLMENTDESCRIPTION_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class InstallmentDescriptionPrivate;
class Currency;

/*!
 * \brief Contains the description of an installment.
 *
 * \ppPaymentsApi{installment_description}
 *
 * \headerfile "" <Geltan/PP/Objects/installmentdescription.h>
 */
class GELTANSHARED_EXPORT InstallmentDescription : public QObject
{
    Q_OBJECT
    /*!
     * \brief Number of installments.
     *
     * \ppApiName{term}
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>term() const</TD></TR><TR><TD>void</TD><TD>setTerm(int nTerm)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>termChanged(int term)</TD></TR></TABLE>
     */
    Q_PROPERTY(int term READ term WRITE setTerm NOTIFY termChanged)
    /*!
     * \brief The monthly payment.
     *
     * Contains a pointer to a Currency object, if any, otherwise contains a nullptr. If created internally, the Currency object will be a child
     * of the InstallmentDescription object and will be destroyed on the parent's destruction.
     *
     * \ppApiName{monthly_payment}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Currency*</TD><TD>monthlyPayment() const</TD></TR><TR><TD>void</TD><TD>setMonthlyPayment(Currency *nMonthlyPayment)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>monthlyPaymentChanged(Currency *monthlyPayment)</TD></TR></TABLE>
     */
    Q_PROPERTY(Currency *monthlyPayment READ monthlyPayment WRITE setMonthlyPayment NOTIFY monthlyPaymentChanged)
    /*!
     * \brief Discount amount applied to the payment, if any.
     *
     * Contains a pointer to a Currency object, if any, otherwise contains a nullptr. If created internally, the Currency object will be a child
     * of the InstallmentDescription object and will be destroyed on the parent's destruction.
     *
     * \ppApiName{discount_amount}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Currency*</TD><TD>discountAmount() const</TD></TR><TR><TD>void</TD><TD>setDiscountAmount(Currency *nDiscountAmount)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>discountAmountChanged(Currency *discountAmount)</TD></TR></TABLE>
     */
    Q_PROPERTY(Currency *discountAmount READ discountAmount WRITE setDiscountAmount NOTIFY discountAmountChanged)
    /*!
     * \brief Discount percentage applied to the payment, if any.
     *
     * \ppApiName{discount_percentage}
     *
     * \par Access functions:
     * <TABLE><TR><TD>double</TD><TD>discountPercentage() const</TD></TR><TR><TD>void</TD><TD>setDiscountPercentage(double nDiscountPercentage)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>discountPercentageChanged(double discountPercentage)</TD></TR></TABLE>
     */
    Q_PROPERTY(double discountPercentage READ discountPercentage WRITE setDiscountPercentage NOTIFY discountPercentageChanged)
public:
    /*!
     * \brief Constructs a new empty InstallmentDescription object.
     */
    explicit InstallmentDescription(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new InstallmentDescription object from JSON data.
     */
    InstallmentDescription(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new InstallmentDescription object from JSON data.
     */
    InstallmentDescription(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the InstallmentDescription object.
     */
    ~InstallmentDescription();


    int term() const;
    Currency *monthlyPayment() const;
    Currency *discountAmount() const;
    double discountPercentage() const;


    void setTerm(int nTerm);
    void setMonthlyPayment(Currency *nMonthlyPayment);
    void setDiscountAmount(Currency *nDiscountAmount);
    void setDiscountPercentage(double nDiscountPercentage);

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
     * \brief Loads data from a QJsonDocument into the InstallmentDescription object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the InstallmentDescription object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void termChanged(int term);
    void monthlyPaymentChanged(Currency *monthlyPayment);
    void discountAmountChanged(Currency *discountAmount);
    void discountPercentageChanged(double discountPercentage);


protected:
    const QScopedPointer<InstallmentDescriptionPrivate> d_ptr;

private:
    Q_DISABLE_COPY(InstallmentDescription)
    Q_DECLARE_PRIVATE(InstallmentDescription)

};

}
}

#endif // INSTALLMENTDESCRIPTION_H
