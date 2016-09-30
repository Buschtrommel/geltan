/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * capture.h
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

#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QDateTime>
#include <QVariantMap>
#include <QJsonObject>
#include <QUrl>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {
namespace PP {

class CapturePrivate;
class PaymentAmount;
class Currency;
class Link;

/*!
 * \brief Contains details about a capture transaction.
 *
 * \ppPaymentsApi{capture}
 *
 * \headerfile "capture.h" <Geltan/PP/Objects/capture.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Capture : public QObject
{
    Q_OBJECT
    /*!
     * \brief The ID of the capture transaction.
     *
     * \ppApiName{id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>id() const</TD></TR><TR><TD>void</TD><TD>setId(const QString &nId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>idChanged(const QString &id)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    /*!
     * \brief Amount being captured.
     *
     * \ppApiName{amount}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PaymentAmount*</TD><TD>amount() const</TD></TR><TR><TD>void</TD><TD>setAmount(PaymentAmount *nAmount)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>amountChanged(PaymentAmount *amount)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(Geltan::PP::PaymentAmount *amount READ amount WRITE setAmount NOTIFY amountChanged)
    /*!
     * \brief Indicates whether to release all remaining funds that the authorization holds in the funding instrument.
     *
     * \ppApiName{is_final_capture}
     *
     * \par Access functions:
     * <TABLE><TR><TD>bool</TD><TD>isFinalCapture() const</TD></TR><TR><TD>void</TD><TD>setIsFinalCapture(bool nIsFinalCapture)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>isFinalCaptureChanged(bool isFinalCapture)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(bool isFinalCapture READ isFinalCapture WRITE setIsFinalCapture NOTIFY isFinalCaptureChanged)
    /*!
     * \brief The state of the capture.
     *
     * \ppApiName{state}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::StateType</TD><TD>state() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(PayPal::StateType state)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(Geltan::PP::PayPal::StateType state READ state NOTIFY stateChanged)
    /*!
     * \brief The reason code that describes why the transaction state is pending or reversed.
     *
     * \ppApiName{reason_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::ReasonCode</TD><TD>reasonCode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>reasonCodeChanged(PayPal::ReasonCode reasonCode)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(Geltan::PP::PayPal::ReasonCode reasonCode READ reasonCode NOTIFY reasonCodeChanged)
    /*!
     * \brief The ID of the payment on which this transaction is based.
     *
     * \ppApiName{parent_payment}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>parentPayment() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>parentPaymentChanged(const QString &parentPayment)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(QString parentPayment READ parentPayment NOTIFY parentPaymentChanged)
    /*!
     * \brief The invoice number to track this payment.
     *
     * Max length: 127.
     *
     * \ppApiName{invoice_number}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>invoiceNumber() const</TD></TR><TR><TD>void</TD><TD>setInvoiceNumber(const QString &nInvoiceNumber)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>invoiceNumberChanged(const QString &invoiceNumber)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(QString invoiceNumber READ invoiceNumber WRITE setInvoiceNumber NOTIFY invoiceNumberChanged)
    /*!
     * \brief Transaction fee applicable for this payment.
     *
     * \ppApiName{transaction_fee}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Currency*</TD><TD>transactionFee() const</TD></TR><TR><TD>void</TD><TD>setTransactionFee(Currency *nTransactionFee)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>transactionFeeChanged(Currency *transactionFee)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(Geltan::PP::Currency *transactionFee READ transactionFee WRITE setTransactionFee NOTIFY transactionFeeChanged)
    /*!
     * \brief The date and time of capture.
     *
     * \ppApiName{create_time}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>createTime() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>createTimeChanged(const QDateTime &createTime)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(QDateTime createTime READ createTime NOTIFY createTimeChanged)
    /*!
     * \brief The date and time when the resource was last updated.
     *
     * \ppApiName{update_time}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>updateTime() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>updateTimeChanged(const QDateTime &updateTime)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(QDateTime updateTime READ updateTime NOTIFY updateTimeChanged)
    /*!
     * \brief HATEOAS links related to this call.
     *
     * \ppApiName{links}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Link*></TD><TD>links() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>linksChanged(const QList<Link*> &links)</TD></TR></TABLE>
     *
     * \since 0.0.1
     */
    Q_PROPERTY(QList<Geltan::PP::Link*> links READ links NOTIFY linksChanged)
public:
    /*!
     * \brief Constructs a new empty Capture object.
     */
    explicit Capture(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Capture object from JSON data.
     */
    Capture(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Capture object from JSON data.
     */
    Capture(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Capture object.
     */
    ~Capture();

    QString id() const;
    PaymentAmount *amount() const;
    bool isFinalCapture() const;
    PayPal::StateType state() const;
    PayPal::ReasonCode reasonCode() const;
    QString parentPayment() const;
    QString invoiceNumber() const;
    Currency *transactionFee() const;
    QDateTime createTime() const;
    QDateTime updateTime() const;
    QList<Link*> links() const;


    /*!
     * \brief Sets the ID of the capture transaction.
     */
    void setId(const QString &nId);
    void setAmount(PaymentAmount *nAmount);
    void setIsFinalCapture(bool nIsFinalCapture);
    /*!
     * \brief Sets the state of the capture transaction.
     */
    void setState(PayPal::StateType nState);
    /*!
     * \brief Sets the reason code if state is \c pending or \c reversed.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode);
    /*!
     * \brief Set the ID of the payment on which this transaction is based.
     */
    void setParentPayment(const QString &nParentPayment);
    void setInvoiceNumber(const QString &nInvoiceNumber);
    void setTransactionFee(Currency *nTransactionFee);
    /*!
     * \brief Sets the date and time of capture.
     */
    void setCreateTime(const QDateTime &nCreateTime);
    /*!
     * \brief Sets the date and time when the resource was last updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime);
    /*!
     * \brief Sets the HATEOAS links of the capture for related calls.
     */
    void setLinks(const QList<Link*> &nLinks);

    /*!
     * \brief Returns the URL of the Link in the list of HATEOAS links defined by \a rel.
     *
     * If no Link can be found, the returned URL will be invalid.
     */
    Q_INVOKABLE QUrl getLinkURL(const QString &rel) const;

    /*!
     * \brief Returns the Link in the list of HATEOAS links defined by \a rel.
     *
     * If no Link can be found, a \c nullptr will be returned.
     */
    Q_INVOKABLE Link* getLink(const QString &rel) const;


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
     * \brief Loads data from a QJsonDocument into the Capture object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Capture object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void idChanged(const QString &id);
    void amountChanged(PaymentAmount *amount);
    void isFinalCaptureChanged(bool isFinalCapture);
    void stateChanged(PayPal::StateType state);
    void reasonCodeChanged(PayPal::ReasonCode reasonCode);
    void parentPaymentChanged(const QString &parentPayment);
    void invoiceNumberChanged(const QString &invoiceNumber);
    void transactionFeeChanged(Currency *transactionFee);
    void createTimeChanged(const QDateTime &createTime);
    void updateTimeChanged(const QDateTime &updateTime);
    void linksChanged(const QList<Link*> &links);

protected:
    const QScopedPointer<CapturePrivate> d_ptr;

private:
    Q_DISABLE_COPY(Capture)
    Q_DECLARE_PRIVATE(Capture)

};

}
}


#endif // CAPTURE_H
