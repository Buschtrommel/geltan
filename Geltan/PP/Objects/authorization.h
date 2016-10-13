/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * authorization.h
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

#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>
#include <QDateTime>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {
namespace PP {



class AuthorizationPrivate;
class PaymentAmount;
class FMFDetails;
class Link;

/*!
 * \brief Contains details about an authorization transaction.
 *
 * \ppPaymentsApi{authorization}
 *
 * \headerfile "authorization.h" <Geltan/PP/Objects/authorization.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Authorization : public QObject
{
    Q_OBJECT
    /*!
     * \brief ID of the authorization transaction.
     *
     * Read only API value.
     *
     * \ppApiName{id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>id() const</TD></TR><TR><TD>void</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>idChanged(const QString &id)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    /*!
     * \brief Amount being authorized.
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
     * \brief Specifies the payment mode of the transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::PaymentModeType</TD><TD>paymentMode() const</TD></TR><TR><TD>void</TD><TD>setPaymentMode(PayPal::PaymentModeType nPaymentMode)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentModeChanged(PayPal::PaymentModeType paymentMode)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::PaymentModeType paymentMode READ paymentMode NOTIFY paymentModeChanged)
    /*!
     * \brief State of the authorization.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::StateType</TD><TD>state() const</TD></TR><TR><TD>void</TD><TD>setState(PayPal::StateType nState)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(PayPal::StateType state)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::StateType state READ state NOTIFY stateChanged)
    /*!
     * \brief Reason code for a transaction state of pending.
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
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::ProtectionEligibility</TD><TD>protectionEligibility() const</TD></TR><TR><TD>void</TD><TD>setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>protectionEligibilityChanged(PayPal::ProtectionEligibility protectionEligibility)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::ProtectionEligibility protectionEligibility READ protectionEligibility NOTIFY protectionEligibilityChanged)
    /*!
     * \brief The kind of seller protection in force for the transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<PayPal::ProtectionEligibilityType></TD><TD>protectionEligibilityType() const</TD></TR><TR><TD>void</TD><TD>setProtectionEligibilityType(QList<PayPal::ProtectionEligibilityType> nProtectionEligibilityType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>protectionEligibilityTypeChanged(PayPal::ProtectionEligibilityType protectionEligibilityType)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::PayPal::ProtectionEligibilityType> protectionEligibilityType READ protectionEligibilityType NOTIFY protectionEligibilityTypeChanged)
    /*!
     * \brief Details of Fraud Management Filter (FMF).
     *
     * \par Access functions:
     * <TABLE><TR><TD>FMFDetails*</TD><TD>fmfDetails() const</TD></TR><TR><TD>void</TD><TD>setFmfDetails(FMFDetails *nFmfDetails)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>fmfDetailsChanged(FMFDetails *fmfDetails)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::FMFDetails *fmfDetails READ fmfDetails NOTIFY fmfDetailsChanged)
    /*!
     * \brief ID of the Payment resource that this transaction is based on.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>parentPayment() const</TD></TR><TR><TD>void</TD><TD>setParentPayment(const QString &nParentPayment)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>parentPaymentChanged(const QString &parentPayment)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString parentPayment READ parentPayment NOTIFY parentPaymentChanged)
    /*!
     * \brief Authorization expiration time and date.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>validUntil() const</TD></TR><TR><TD>void</TD><TD>setValidUntil(const QDateTime &nValidUntil)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>validUntilChanged(const QDateTime &validUntil)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime validUntil READ validUntil NOTIFY validUntilChanged)
    /*!
     * \brief Time of authorization.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>createTime() const</TD></TR><TR><TD>void</TD><TD>setCreateTime(const QDateTime &nCreateTime)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>createTimeChanged(const QDateTime &createTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime createTime READ createTime NOTIFY createTimeChanged)
    /*!
     * \brief Time that the resource was last updated.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>updateTime() const</TD></TR><TR><TD>void</TD><TD>setUpdateTime(const QDateTime &nUpdateTime)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>updateTimeChanged(const QDateTime &updateTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime updateTime READ updateTime NOTIFY updateTimeChanged)
    /*!
     * \brief Identifier to the purchase or transaction unit corresponding to this authorization transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>referenceId() const</TD></TR><TR><TD>void</TD><TD>setReferenceId(const QString &nReferenceId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>referenceIdChanged(const QString &referenceId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString referenceId READ referenceId NOTIFY referenceIdChanged)
    /*!
     * \brief Receipt id is 16 digit number payment identification number returned for guest users to identify the payment.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>receiptId() const</TD></TR><TR><TD>void</TD><TD>setReceiptId(const QString &nReceiptId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>receiptIdChanged(const QString &receiptId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString receiptId READ receiptId NOTIFY receiptIdChanged)
    /*!
     * \brief HATEOAS links related to this call.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Link*></TD><TD>links() const</TD></TR><TR><TD>void</TD><TD>setLinks(const QList<Link*> &nLinks)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>linksChanged(const QList<Link*> &links)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::Link*> links READ links NOTIFY linksChanged)
public:
    /*!
     * \brief Constructs a new empty Authorization object.
     */
    explicit Authorization(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Authorization object from JSON data.
     */
    Authorization(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Authorization object from JSON data.
     */
    Authorization(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Authorization object.
     */
    ~Authorization();

    QString id() const;
    PaymentAmount *amount() const;
    PayPal::PaymentModeType paymentMode() const;
    PayPal::StateType state() const;
    PayPal::ReasonCode reasonCode() const;
    PayPal::ProtectionEligibility protectionEligibility() const;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType() const;
    FMFDetails *fmfDetails() const;
    QString parentPayment() const;
    QDateTime validUntil() const;
    QDateTime createTime() const;
    QDateTime updateTime() const;
    QString referenceId() const;
    QString receiptId() const;
    QList<Link*> links() const;

    /*!
     * \brief Sets the ID of the authorization transaction.
     */
    void setId(const QString &nId);
    void setAmount(PaymentAmount *nAmount);
    /*!
     * \brief Sets the payment mode.
     */
    void setPaymentMode(PayPal::PaymentModeType nPaymentMode);
    /*!
     * \brief Sets the state of the authorization.
     */
    void setState(PayPal::StateType nState);
    /*!
     * \brief Sets the reason code for an authorizatin state of \c pending.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode);
    /*!
     * \brief Sets the level of seller protection in force.
     */
    void setProtectionEligibility(PayPal::ProtectionEligibility nProtectionEligibility);
    /*!
     * \brief Sets the kind of seller protection in force.
     */
    void setProtectionEligibilityType(const QList<PayPal::ProtectionEligibilityType> &nProtectionEligibilityType);
    /*!
     * \brief Sets the details of Fraud Management Filter (FMF).
     */
    void setFmfDetails(FMFDetails *nFmfDetails);
    /*!
     * \brief Sets the ID of a parent payment.
     */
    void setParentPayment(const QString &nParentPayment);
    /*!
     * \brief Sets the expiration time and date.
     */
    void setValidUntil(const QDateTime &nValidUntil);
    /*!
     * \brief Sets the date and time of the authorization.
     */
    void setCreateTime(const QDateTime &nCreateTime);
    /*!
     * \brief Sets the date and time the resource was last updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime);
    /*!
     * \brief Sets the ID of the purchase or transaction unit corresponding to this authorization.
     */
    void setReferenceId(const QString &nReferenceId);
    /*!
     * \brief Sets the 16 digit number payment identification number.
     */
    void setReceiptId(const QString &nReceiptId);
    /*!
     * \brief Sets the HATEOS links related to this call.
     */
    void setLinks(const QList<Link*> &nLinks);

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
     * \brief Loads data from a QJsonDocument into the Authorization object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Authorization object.
     */
    void loadFromJson(const QJsonObject &json);

Q_SIGNALS:
    void idChanged(const QString &id);
    void amountChanged(PaymentAmount *amount);
    void paymentModeChanged(PayPal::PaymentModeType paymentMode);
    void stateChanged(PayPal::StateType state);
    void reasonCodeChanged(PayPal::ReasonCode reasonCode);
    void protectionEligibilityChanged(PayPal::ProtectionEligibility protectionEligibility);
    void protectionEligibilityTypeChanged(const QList<PayPal::ProtectionEligibilityType> &protectionEligibilityType);
    void fmfDetailsChanged(FMFDetails *fmfDetails);
    void parentPaymentChanged(const QString &parentPayment);
    void validUntilChanged(const QDateTime &validUntil);
    void createTimeChanged(const QDateTime &createTime);
    void updateTimeChanged(const QDateTime &updateTime);
    void referenceIdChanged(const QString &referenceId);
    void receiptIdChanged(const QString &receiptId);
    void linksChanged(const QList<Link*> &links);

protected:
    const QScopedPointer<AuthorizationPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Authorization)
    Q_DECLARE_PRIVATE(Authorization)

};

}
}


#endif // AUTHORIZATION_H
