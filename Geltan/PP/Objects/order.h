/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * order.h
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

#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {
namespace PP {



class OrderPrivate;
class PaymentAmount;
class FMFDetails;
class Link;

/*!
 * \brief Contains details about an order transaction.
 *
 * \ppPaymentsApi{order}
 *
 * \headerfile "" <Geltan/PP/Objects/order.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Order : public QObject
{
    Q_OBJECT
    /*!
     * \brief Identifier of the order transaction.
     *
     * \ppApiName{id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>id() const</TD></TR><TR><TD>void</TD><TD>setId(const QString &nId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>idChanged(const QString &id)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    /*!
     * \brief Identifier to the purchase unit associated with this object.
     *
     * \ppApiName{reference_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>referenceId() const</TD></TR><TR><TD>void</TD><TD>setReferenceId(const QString &nReferenceId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>referenceIdChanged(const QString &referenceId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString referenceId READ referenceId NOTIFY referenceIdChanged)
    /*!
     * \brief Amount being collected.
     *
     * \ppApiName{amount}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PaymentAmount*</TD><TD>amount() const</TD></TR><TR><TD>void</TD><TD>setAmount(PaymentAmount *nAmount)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>amountChanged(PaymentAmount *amount)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PaymentAmount *amount READ amount WRITE setAmount NOTIFY amountChanged)
    /*!
     * \brief Specifies payment mode of the transaction
     *
     * \ppApiName{payment_mode}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::PaymentModeType</TD><TD>paymentMode() const</TD></TR><TR><TD>void</TD><TD>setPaymentMode(PayPal::PaymentModeType nPaymentMode)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentModeChanged(PayPal::PaymentModeType paymentMode)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::PaymentModeType paymentMode READ paymentMode NOTIFY paymentModeChanged)
    /*!
     * \brief State of the order transaction.
     *
     * \ppApiName{state}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::StateType</TD><TD>state() const</TD></TR><TR><TD>void</TD><TD>setState(PayPal::StateType nState)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(PayPal::StateType state)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::StateType state READ state NOTIFY stateChanged)
    /*!
     * \brief Reason code for the transaction state being Pending or Reversed.
     *
     * This field will replace pending_reason field eventually. Only supported when the payment_method is set to paypal.
     *
     * \ppApiName{reason_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::ReasonCode</TD><TD>reasonCode() const</TD></TR><TR><TD>void</TD><TD>setReasonCode(PayPal::ReasonCode nReasonCode)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>reasonCodeChanged(PayPal::ReasonCode reasonCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::ReasonCode reasonCode READ reasonCode NOTIFY reasonCodeChanged)
    /*!
     * \brief The level of seller protection in force for the transaction.
     *
     * \ppApiName{protection_eligibility}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::ProtectionEligibility</TD><TD>protectionEligibility() const</TD></TR><TR><TD>void</TD><TD>setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>protectionEligibilityChanged(PayPal::ProtectionEligibility protectionEligibility)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::ProtectionEligibility protectionEligibility READ protectionEligibility NOTIFY protectionEligibilityChanged)
    /*!
     * \brief The kind of seller protection in force for the transaction.
     *
     * This property is returned only when the protection_eligibility property is set to ELIGIBLEor PARTIALLY_ELIGIBLE.
     * Only supported when the payment_method is set to paypal. Allowed values:
     * ITEM_NOT_RECEIVED_ELIGIBLE- Sellers are protected against claims for items not received.
     * UNAUTHORIZED_PAYMENT_ELIGIBLE- Sellers are protected against claims for unauthorized payments.
     * One or both of the allowed values can be returned.
     *
     * \ppApiName{protection_eligibility_type}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<PayPal::ProtectionEligibilityType></TD><TD>protectionEligibilityType() const</TD></TR><TR><TD>void</TD><TD>setProtectionEligibilityType(QList<PayPal::ProtectionEligibilityType> nProtectionEligibilityType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>protectionEligibilityTypeChanged(PayPal::ProtectionEligibilityType protectionEligibilityType)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::PayPal::ProtectionEligibilityType> protectionEligibilityType READ protectionEligibilityType NOTIFY protectionEligibilityTypeChanged)
    /*!
     * \brief ID of the Payment resource that this transaction is based on.
     *
     * \ppApiName{parent_payment}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>parentPayment() const</TD></TR><TR><TD>void</TD><TD>setParentPayment(const QString &nParentPayment)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>parentPaymentChanged(const QString &parentPayment)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString parentPayment READ parentPayment NOTIFY parentPaymentChanged)
    /*!
     * \brief Details of Fraud Management Filter (FMF).
     *
     * \ppApiName{fmf_details}
     *
     * \par Access functions:
     * <TABLE><TR><TD>FMFDetails*</TD><TD>fmfDetails() const</TD></TR><TR><TD>void</TD><TD>setFmfDetails(FMFDetails *nFmfDetails)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>fmfDetailsChanged(FMFDetails *fmfDetails)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::FMFDetails *fmfDetails READ fmfDetails NOTIFY fmfDetailsChanged)
    /*!
     * \brief Time the resource was created.
     *
     * \ppApiName{create_time}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>createTime() const</TD></TR><TR><TD>void</TD><TD>setCreateTime(const QDateTime &nCreateTime)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>createTimeChanged(const QDateTime &createTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime createTime READ createTime NOTIFY createTimeChanged)
    /*!
     * \brief Time the resouce was last updated.
     *
     * \ppApiName{update_time}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>updateTime() const</TD></TR><TR><TD>void</TD><TD>setUpdateTime(const QDateTime &nUpdateTime)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>updateTimeChanged(const QDateTime &updateTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime updateTime READ updateTime NOTIFY updateTimeChanged)
    /*!
     * \brief HATEOAS links related to this call.
     *
     * \ppApiName{links}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Link*></TD><TD>links() const</TD></TR><TR><TD>void</TD><TD>setLinks(const QList<Link*> &nLinks)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>linksChanged(const QList<Link*> &links)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::Link*> links READ links NOTIFY linksChanged)
public:
    /*!
     * \brief Constructs a new empty Order object.
     */
    explicit Order(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Order object from JSON data.
     */
    Order(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Order object from JSON data.
     */
    Order(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Order object.
     */
    ~Order();

    QString id() const;
    QString referenceId() const;
    PaymentAmount *amount() const;
    PayPal::PaymentModeType paymentMode() const;
    PayPal::StateType state() const;
    PayPal::ReasonCode reasonCode() const;
    PayPal::ProtectionEligibility protectionEligibility() const;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType() const;
    QString parentPayment() const;
    FMFDetails *fmfDetails() const;
    QDateTime createTime() const;
    QDateTime updateTime() const;
    QList<Link*> links() const;

    /*!
     * \brief Sets the identifier of the order transaction.
     */
    void setId(const QString &nId);
    /*!
     * \brief Sets the reference id of the order transaction.
     */
    void setReferenceId(const QString &nReferenceId);
    /*!
     * \brief Sets the amount object.
     */
    void setAmount(PaymentAmount *nAmount);
    /*!
     * \brief Sets the payment mode of the transaction.
     */
    void setPaymentMode(PayPal::PaymentModeType nPaymentMode);
    /*!
     * \brief Sets the state of the transaction.
     */
    void setState(PayPal::StateType nState);
    /*!
     * \brief Sets the reason code of the transaction.
     *
     * Only supported when the \a payment_mehtod is set to \c paypal.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode);
    /*!
     * \brief Sets the level of seller protection in force.
     */
    void setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility);
    /*!
     * \brief Sets the kind of seller protection in force.
     */
    void setProtectionEligibilityType(QList<PayPal::ProtectionEligibilityType> nProtectionEligibilityType);
    /*!
     * \brief Sets the ID of the payment resource that this transaction is based on.
     */
    void setParentPayment(const QString &nParentPayment);
    /*!
     * \brief Sets the details of Fraud Management Filter.
     */
    void setFmfDetails(FMFDetails *nFmfDetails);
    /*!
     * \brief Sets the time the resource was created.
     */
    void setCreateTime(const QDateTime &nCreateTime);
    /*!
     * \brief Sets the time the resource was last updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime);
    /*!
     * \brief Sets the HATEOAS links related to this call.
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
     * \brief Loads data from a QJsonDocument into the Order object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Order object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void idChanged(const QString &id);
    void referenceIdChanged(const QString &referenceId);
    void amountChanged(PaymentAmount *amount);
    void paymentModeChanged(PayPal::PaymentModeType paymentMode);
    void stateChanged(PayPal::StateType state);
    void reasonCodeChanged(PayPal::ReasonCode reasonCode);
    void protectionEligibilityChanged(PayPal::ProtectionEligibility protectionEligibility);
    void protectionEligibilityTypeChanged(QList<PayPal::ProtectionEligibilityType> protectionEligibilityType);
    void parentPaymentChanged(const QString &parentPayment);
    void fmfDetailsChanged(FMFDetails *fmfDetails);
    void createTimeChanged(const QDateTime &createTime);
    void updateTimeChanged(const QDateTime &updateTime);
    void linksChanged(const QList<Link*> &links);

protected:
    const QScopedPointer<OrderPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Order)
    Q_DECLARE_PRIVATE(Order)

};

}
}


#endif // ORDER_H
