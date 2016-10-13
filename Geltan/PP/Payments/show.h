/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/show.h
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

#ifndef SHOWPAYMENT_H
#define SHOWPAYMENT_H

#include <QObject>
#include <Geltan/PP/ppbase.h>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class Payment;

namespace Payments {

class ShowPrivate;

/*!
 * \brief Requests information about a PayPal payment.
 *
 * \headerfile "" <Geltan/PP/Payments/show.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Show : public PPBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Show)
    /*!
     * \brief Will contain the requested Payment object.
     *
     * \par Access functions:
     * <TABLE><TR><TD>Payment*</TD><TD>payment() const</TD></TR><TR><TD>void</TD><TD>setPayment(Payment *nPayment)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentChanged(Payment *payment)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Payment *payment READ payment NOTIFY paymentChanged)
    /*!
     * \brief The ID of the payment to request.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>paymentId() const</TD></TR><TR><TD>void</TD><TD>setPaymentId(const QString &nPaymentId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentIdChanged(const QString &paymentId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString paymentId READ paymentId WRITE setPaymentId NOTIFY paymentIdChanged)
public:
    /*!
     * \brief Constructs a new ShowPayment object.
     */
    Show(QObject *parent = nullptr);

//    /*!
//     * \brief Deconstructs the ShowPayment object.
//     */
//    virtual ~Show();

    /*!
     * \brief Invokes the API call.
     *
     * This expects that paymentId has been set. Starting a new call will delete
     * the currently set payment if it's parent is the ShowPayment object.
     */
    Q_INVOKABLE void call();

    /*!
     * \brief Invokes the API call and sets the payment ID.
     * \overload
     */
    Q_INVOKABLE void call(const QString &paymentId);

    Payment *payment() const;
    QString paymentId() const;

    void setPaymentId(const QString &nPaymentId);

Q_SIGNALS:
    /*!
     * \brief This signal will be emitted when the request was successful.
     */
    void succeeded();

    /*!
     * \brief This signal will be emitted when the request failed.
     */
    void failed();

    void paymentChanged(Payment *payment);
    void paymentIdChanged(const QString &paymentId);

protected:
    void successCallBack() Q_DECL_OVERRIDE;
    void errorCallBack() Q_DECL_OVERRIDE;
    bool checkInput() Q_DECL_OVERRIDE;
    bool checkOutput() Q_DECL_OVERRIDE;

    Show(ShowPrivate &dd, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(Show)
};

}
}
}

#endif // SHOWPAYMENT_H
