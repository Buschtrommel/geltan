/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/execute.h
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

#ifndef EXECUTEPAYMENT_H
#define EXECUTEPAYMENT_H

#include <QObject>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppbase.h>

class QUrl;

namespace Geltan {
namespace PP {

class Payment;
class Transaction;

namespace Payments {

class ExecutePrivate;

/*!
 * \brief Executes a PayPal payment.
 *
 * \headerfile "" <Geltan/PP/Payments/execute.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-27
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Execute : public PPBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Execute)
    /*!
     * \brief Payment object to execute.
     *
     * \par Access functions:
     * <TABLE><TR><TD>Payment*</TD><TD>payment() const</TD></TR><TR><TD>void</TD><TD>setPayment(Payment *nPayment)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentChanged(Payment *payment)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Payment *payment READ payment WRITE setPayment NOTIFY paymentChanged)
    /*!
     * \brief The ID of the payer, passed in the return_url by PayPal.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>payerId() const</TD></TR><TR><TD>void</TD><TD>setPayerId(const QString &nPayerId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payerIdChanged(const QString &payerId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString payerId READ payerId WRITE setPayerId NOTIFY payerIdChanged)
    /*!
     * \brief The ID of the payment to execute.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>paymentId() const</TD></TR><TR><TD>void</TD><TD>setPaymentId(const QString &nPaymentId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentIdChanged(const QString &paymentId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString paymentId READ paymentId WRITE setPaymentId NOTIFY paymentIdChanged)
    /*!
     * \brief Transactional details if updating a payment.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Transaction*></TD><TD>transactions() const</TD></TR><TR><TD>void</TD><TD>setTransactions(const QList<Transaction*> &nTransactions)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>transactionsChanged(const QList<Transaction*> &transactions)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::Transaction*> transactions READ transactions WRITE setTransactions NOTIFY transactionsChanged)
public:
    /*!
     * \brief Constructs a new Execute object.
     */
    explicit Execute(QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Execute object.
     */
    virtual ~Execute();

    /*!
     * \brief Invokes the API call.
     *
     * This expects that payerId and paymentId are set.
     */
    Q_INVOKABLE void call();

    /*!
     * \brief Sets paymentId and payerId and invokes the API call.
     */
    Q_INVOKABLE void call(const QString &paymentId, const QString &payerId);

    /*!
     * \brief Tries to extract paymentId and payerId from a return_url and invokes the API call.
     *
     * The return URL has to contain the query values \a paymentId and \a PayerID.
     */
    Q_INVOKABLE void call(const QUrl &returnUrl);

    Payment *payment() const;
    QString payerId() const;
    QString paymentId() const;
    QList<Transaction*> transactions() const;

    void setPayment(Payment *nPayment);
    void setPayerId(const QString &nPayerId);
    void setPaymentId(const QString &nPaymentId);
    void setTransactions(const QList<Transaction*> &nTransactions);

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
    void payerIdChanged(const QString &payerId);
    void paymentIdChanged(const QString &paymentId);
    void transactionsChanged(const QList<Transaction*> &transactions);

protected:
    void successCallBack() Q_DECL_OVERRIDE;
    void errorCallBack() Q_DECL_OVERRIDE;
    bool checkInput() Q_DECL_OVERRIDE;
    bool checkOutput() Q_DECL_OVERRIDE;

    Execute(ExecutePrivate &dd, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(Execute)
};

}
}
}

#endif // EXECUTEPAYMENT_H
