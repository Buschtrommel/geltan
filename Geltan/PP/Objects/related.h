/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/related.h
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

#ifndef RELATED_H
#define RELATED_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class RelatedPrivate;
class Sale;
class Authorization;
class Order;
class Capture;
class Refund;

/*!
 * \brief Container class for financial transactions.
 *
 * Each one representing a financial transaction (Sale, Authorization, Capture, Refund) related to the payment.
 *
 * \ppPaymentsApi{related}
 *
 * \headerfile "" <Geltan/PP/Objects/related.h>
 */
class GELTANSHARED_EXPORT Related : public QObject
{
    Q_OBJECT
    /*!
     * \brief A sale transaction. This is the resource that is returned as a part related resources in Payment.
     *
     * \ppApiName{sale}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Sale*</TD><TD>sale() const</TD></TR><TR><TD>void</TD><TD>setSale(Sale *nSale)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>saleChanged(Sale *sale)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Sale *sale READ sale WRITE setSale NOTIFY saleChanged)
    /*!
     * \brief An authorization transaction.
     *
     * \ppApiName{authorization}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Authorization*</TD><TD>authorization() const</TD></TR><TR><TD>void</TD><TD>setAuthorization(Authorization *nAuthorization)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>authorizationChanged(Authorization *authorization)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Authorization *authorization READ authorization WRITE setAuthorization NOTIFY authorizationChanged)
    /*!
     * \brief An order transaction.
     *
     * \ppApiName{order}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Order*</TD><TD>order() const</TD></TR><TR><TD>void</TD><TD>setOrder(Order *nOrder)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>orderChanged(Order *order)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Order *order READ order WRITE setOrder NOTIFY orderChanged)
    /*!
     * \brief A capture transaction.
     *
     * \ppApiName{capture}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Capture*</TD><TD>capture() const</TD></TR><TR><TD>void</TD><TD>setCapture(Capture *nCapture)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>captureChanged(Capture *capture)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Capture *capture READ capture WRITE setCapture NOTIFY captureChanged)
    /*!
     * \brief A refund transaction.
     *
     * \ppApiName{refund}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Refund*</TD><TD>refund() const</TD></TR><TR><TD>void</TD><TD>setRefund(Refund *nRefund)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>refundChanged(Refund *refund)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Refund *refund READ refund WRITE setRefund NOTIFY refundChanged)
public:
    /*!
     * \brief Constructs a new empty Related object.
     */
    explicit Related(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Related object from JSON data.
     */
    Related(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Related object from JSON data.
     */
    Related(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Related object.
     */
    ~Related();

    Sale *sale() const;
    Authorization *authorization() const;
    Order *order() const;
    Capture *capture() const;
    Refund *refund() const;

    void setSale(Sale *nSale);
    void setAuthorization(Authorization *nAuthorization);
    void setOrder(Order *nOrder);
    void setCapture(Capture *nCapture);
    void setRefund(Refund *nRefund);


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
     * \brief Loads data from a QJsonDocument into the Related object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Related object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void saleChanged(Sale *sale);
    void authorizationChanged(Authorization *authorization);
    void orderChanged(Order *order);
    void captureChanged(Capture *capture);
    void refundChanged(Refund *refund);

protected:
    const QScopedPointer<RelatedPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Related)
    Q_DECLARE_PRIVATE(Related)

};

}
}


#endif // RELATED_H
