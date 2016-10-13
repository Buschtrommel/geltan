/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/create.h
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

#ifndef CREATEPAYMENT_H
#define CREATEPAYMENT_H

#include <QObject>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppbase.h>

namespace Geltan {
namespace PP {

class Payment;

namespace Payments {

class CreatePrivate;


/*!
 * \brief Create new PayPal payment.
 *
 * \headerfile "" <Geltan/PP/Payments/create.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Create : public PPBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Create)
    /*!
     * \brief The payment that should be created.
     *
     * This object will be updated with the data received from the API if the request was successful.
     *
     * \par Access functions:
     * <TABLE><TR><TD>Payment*</TD><TD>payment() const</TD></TR><TR><TD>void</TD><TD>setPayment(Payment *nPayment)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentChanged(Payment *payment)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Payment *payment READ payment WRITE setPayment NOTIFY paymentChanged)
public:
    /*!
     * \brief Constructs a new Create object.
     */
    Create(QObject *parent = nullptr);

//    /*!
//     * \brief Deconstructs the Create object.
//     */
//    virtual ~Create();

    /*!
     * \brief Invokes the API call.
     */
    Q_INVOKABLE void call();

    Payment *payment() const;
    void setPayment(Payment *nPayment);

    /*!
     * \brief Creates a new empty/invalid Payment object and returns a pointer to it.
     *
     * If there is already a payment set, it will be deleted if this Create object is the parent object.
     * If a new payment is created, the Create object will be the parent object. Also a new Payer object
     * will be created as child of the Payment object. The Payer object will be empty.
     */
    Q_INVOKABLE Geltan::PP::Payment *newPayment();

Q_SIGNALS:
    void paymentChanged(Payment *payment);
    /*!
     * \brief This signal will be emitted when the request was successful.
     */
    void succeeded();
    /*!
     * \brief This signal will be emitted when the request failed.
     */
    void failed();

protected:
    void successCallBack() Q_DECL_OVERRIDE;
    void errorCallBack() Q_DECL_OVERRIDE;
    bool checkInput() Q_DECL_OVERRIDE;
    bool checkOutput() Q_DECL_OVERRIDE;

    Create(CreatePrivate &dd, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(Create)
};

}
}
}

#endif // CREATEPAYMENT_H
