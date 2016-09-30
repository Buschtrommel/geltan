/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * details.h
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

#ifndef DETAILS_H
#define DETAILS_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class DetailsPrivate;

/*!
 * \brief Contains details about a price / amount.
 *
 * \ppPaymentsApi{details}
 *
 * \headerfile "details.h" <Geltan/PP/Objects/details.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Details : public QObject
{
    Q_OBJECT
    /*!
     * \brief Amount of the subtotal of the items. Required if line items are specified.
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
     * \ppApiName{gift_wrap}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>giftWrap() const</TD></TR><TR><TD>void</TD><TD>setGiftWrap(float nGiftWrap)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>giftWrapChanged(float giftWrap)</TD></TR></TABLE>
     */
    Q_PROPERTY(float giftWrap READ giftWrap WRITE setGiftWrap NOTIFY giftWrapChanged)
public:
    /*!
     * \brief Constructs a new empty Details object.
     */
    explicit Details(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Details object from JSON data.
     */
    Details(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Details object from JSON data.
     */
    Details(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Details object from the given arguments.
     */
    Details(float subtotal, float shipping, float tax, float handlingFee, float shippingDiscount, float insurance, float giftWrap, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Details object.
     */
    ~Details();

    float subtotal() const;
    float shipping() const;
    float tax() const;
    float handlingFee() const;
    float shippingDiscount() const;
    float insurance() const;
    float giftWrap() const;

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
     * \brief Loads data from a QJsonDocument into the Details object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Details object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void subtotalChanged(float subtotal);
    void shippingChanged(float shipping);
    void taxChanged(float tax);
    void handlingFeeChanged(float handlingFee);
    void shippingDiscountChanged(float shippingDiscount);
    void insuranceChanged(float insurance);
    void giftWrapChanged(float giftWrap);

protected:
    const QScopedPointer<DetailsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Details)
    Q_DECLARE_PRIVATE(Details)

};

}
}

#endif // DETAILS_H
