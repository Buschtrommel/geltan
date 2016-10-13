/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * paymentamount.h
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

#ifndef PAYMENTAMOUNT_H
#define PAYMENTAMOUNT_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class PaymentAmountPrivate;
class Details;

/*!
 * \brief Containes information about a payment amount.
 *
 * \ppPaymentsApi{payment_amount}
 *
 * \headerfile "" <Geltan/PP/Objects/paymentamount.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT PaymentAmount : public QObject
{
    Q_OBJECT
    /*!
     * \brief 3-letter currency code. PayPal does not support all currencies.
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
     * \brief Total amount charged from the payer to the payee.
     *
     * \ppApiName{total}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>total() const</TD></TR><TR><TD>void</TD><TD>setTotal(float nTotal)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>totalChanged(float total)</TD></TR></TABLE>
     */
    Q_PROPERTY(float total READ total WRITE setTotal NOTIFY totalChanged)
    /*!
     * \brief Additional details of the payment amount.
     *
     * For easier access, the properties of the Details object are mapped to corresponding properties
     * in the PaymentAmount object. When setting a new Details object, the signals will be connected to the
     * corresponding signals of the PaymentAmount object. When there was a Details object before, the connections of that
     * object will be released. The old Details object will not be destroyed automatically.
     *
     * \ppApiName{details}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Details*</TD><TD>details() const</TD></TR><TR><TD>void</TD><TD>setDetails(Details *nDetails)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>detailsChanged(Details *details)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Details *details READ details WRITE setDetails NOTIFY detailsChanged)
    /*!
     * \brief Amount of the subtotal of the items. Required if line items are specified.
     *
     * This is part of the Details object. If no Details object is available, a new one will be created as child of the PaymentAmount object.
     *
     * \ppApiName{subtotal}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>subtotal() const</TD></TR><TR><TD>void</TD><TD>setSubtotal(float nSubtotal)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>subtotalChanged(float subtotal)</TD></TR></TABLE>
     */
    Q_PROPERTY(float subtotal READ subtotal WRITE setSubtotal NOTIFY subtotalChanged)
    /*!
     * \brief Amount charged for shipping.
     *
     * This is part of the Details object. If no Details object is available, a new one will be created as child of the PaymentAmount object.
     *
     * \ppApiName{shipping}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>shipping() const</TD></TR><TR><TD>void</TD><TD>setShipping(float nShipping)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>shippingChanged(float shipping)</TD></TR></TABLE>
     */
    Q_PROPERTY(float shipping READ shipping WRITE setShipping NOTIFY shippingChanged)
    /*!
     * \brief Amount charged for tax.
     *
     * This is part of the Details object. If no Details object is available, a new one will be created as child of the PaymentAmount object.
     *
     * \ppApiName{tax}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>tax() const</TD></TR><TR><TD>void</TD><TD>setTax(float nTax)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>taxChanged(float tax)</TD></TR></TABLE>
     */
    Q_PROPERTY(float tax READ tax WRITE setTax NOTIFY taxChanged)
    /*!
     * \brief Amount being charged for the handling fee.
     *
     * This is part of the Details object. If no Details object is available, a new one will be created as child of the PaymentAmount object.
     *
     * \ppApiName{handling_fee}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>handlingFee() const</TD></TR><TR><TD>void</TD><TD>setHandlingFee(float nHandlingFee)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>handlingFeeChanged(float handlingFee)</TD></TR></TABLE>
     */
    Q_PROPERTY(float handlingFee READ handlingFee WRITE setHandlingFee NOTIFY handlingFeeChanged)
    /*!
     * \brief Amount being discounted for the shipping fee.
     *
     * This is part of the Details object. If no Details object is available, a new one will be created as child of the PaymentAmount object.
     *
     * \ppApiName{shipping_discount}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>shippingDiscount() const</TD></TR><TR><TD>void</TD><TD>setShippingDiscount(float nShippingDiscount)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>shippingDiscountChanged(float shippingDiscount)</TD></TR></TABLE>
     */
    Q_PROPERTY(float shippingDiscount READ shippingDiscount WRITE setShippingDiscount NOTIFY shippingDiscountChanged)
    /*!
     * \brief Amount being charged for the insurance fee.
     *
     * This is part of the Details object. If no Details object is available, a new one will be created as child of the PaymentAmount object.
     *
     * \ppApiName{insurance}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>insurance() const</TD></TR><TR><TD>void</TD><TD>setInsurance(float nInsurance)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>insuranceChanged(float insurance)</TD></TR></TABLE>
     */
    Q_PROPERTY(float insurance READ insurance WRITE setInsurance NOTIFY insuranceChanged)
    /*!
     * \brief Amount being charged as gift wrap fee.
     *
     * This is part of the Details object. If no Details object is available, a new one will be created as child of the PaymentAmount object.
     *
     * \ppApiName{gift_wrap}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>giftWrap() const</TD></TR><TR><TD>void</TD><TD>setGiftWrap(float nGiftWrap)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>giftWrapChanged(float giftWrap)</TD></TR></TABLE>
     */
    Q_PROPERTY(float giftWrap READ giftWrap WRITE setGiftWrap NOTIFY giftWrapChanged)
    /*!
     * \brief Returns true if the available data is valid.
     *
     * This will make a rough check of data consistency. Checks if the currency is set and if a Details object
     * is available, it will check if the sum of the detail valus is the same as the total amount.
     *
     * \par Access functions:
     * <TABLE><TR><TD>bool</TD><TD>valid() const</TD></TR><TR><TD>void</TD><TD>setValid(bool nValid)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>validChanged(bool valid)</TD></TR></TABLE>
     */
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
public:
    /*!
     * \brief Constructs a new empty PaymentAmount object.
     */
    explicit PaymentAmount(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new PaymentAmount object and sets the total amount and the currency.
     */
    PaymentAmount(float total, const QString &currency, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new PaymentAmount object from JSON data.
     */
    PaymentAmount(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new PaymentAmount object from JSON data.
     */
    PaymentAmount(const QJsonObject &json, QObject *parent = nullptr);


    /*!
     * \brief Deconstructs the PaymentAmount object.
     */
    ~PaymentAmount();


    QString currency() const;
    float total() const;
    Details *details() const;
    float subtotal() const;
    float shipping() const;
    float tax() const;
    float handlingFee() const;
    float shippingDiscount() const;
    float insurance() const;
    float giftWrap() const;
    bool valid() const;

    void setCurrency(const QString &nCurrency);
    void setTotal(float nTotal);
    void setDetails(Details *nDetails);
    void setSubtotal(float nSubtotal);
    void setShipping(float nShipping);
    void setTax(float nTax);
    void setHandlingFee(float nHandlingFee);
    void setShippingDiscount(float nShippingDiscount);
    void setInsurance(float nInsurance);
    void setGiftWrap(float nGiftWrap);


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
     * \brief Loads data from a QJsonDocument into the PaymentAmount object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the PaymentAmount object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void currencyChanged(const QString &currency);
    void totalChanged(float total);
    void detailsChanged(Details *details);
    void subtotalChanged(float subtotal);
    void shippingChanged(float shipping);
    void taxChanged(float tax);
    void handlingFeeChanged(float handlingFee);
    void shippingDiscountChanged(float shippingDiscount);
    void insuranceChanged(float insurance);
    void giftWrapChanged(float giftWrap);
    void validChanged(bool valid);

protected:
    const QScopedPointer<PaymentAmountPrivate> d_ptr;

private:
    Q_DISABLE_COPY(PaymentAmount)
    Q_DECLARE_PRIVATE(PaymentAmount)

};

}
}

#endif // PAYMENTAMOUNT_H
