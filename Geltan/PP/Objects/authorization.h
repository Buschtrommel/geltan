/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/authorization.h
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
#include <QUrl>
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
 */
class GELTANSHARED_EXPORT Authorization : public QObject
{
    Q_OBJECT
    /*!
     * \brief ID of the authorization transaction.
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
     * Contains a pointer to a PaymentAmount object, if any, otherwise contains a nullptr.
     * If created internally, the PaymentAmount object will be a child of the Authorization object and will be destroyed
     * on its destruction.
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
     * \ppApiName{payment_mode}
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
     * \ppApiName{state}
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
     * \brief The kind of seller protections in force for the transaction.
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
     * \brief Details of Fraud Management Filter (FMF).
     *
     * Contains a pointer to a FMFDetails object if any, otherwise contains a nullptr. If created internally, the FMFDetails object
     * will be a child of the Authorization object and will be destroyed on its destruction.
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
     * \brief ID of the Payment resource that this authorization is based on.
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
     * \brief Authorization expiration time and date.
     *
     * \ppApiName{valid_until}
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
     * \ppApiName{create_time}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>createTime() const</TD></TR><TR><TD>void</TD><TD>setCreateTime(const QDateTime &nCreateTime)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>createTimeChanged(const QDateTime &createTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime createTime READ createTime NOTIFY createTimeChanged)
    /*!
     * \brief Time that the authorization was last updated.
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
     * \brief Identifier to the purchase or transaction unit corresponding to this authorization transaction.
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
     * \brief Receipt ID is 16 digit number payment identification number returned for guest users to identify the payment.
     *
     * \ppApiName{receipt_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>receiptId() const</TD></TR><TR><TD>void</TD><TD>setReceiptId(const QString &nReceiptId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>receiptIdChanged(const QString &receiptId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString receiptId READ receiptId NOTIFY receiptIdChanged)
    /*!
     * \brief List of<a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> Link objects related to this call.
     *
     * If created internally, the Link objects will be children of the Authorization object and will be destroyed on the parent's
     * destruction.
     *
     * \ppApiName{links}
     *
     * \sa getLink(), getLinkURL()
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


    void setAmount(PaymentAmount *nAmount);


    /*!
     * \brief Returns the URL of the Link in the list of <a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> links defined by \a rel.
     *
     * If no Link can be found, the returned URL will be invalid.
     */
    Q_INVOKABLE QUrl getLinkURL(const QString &rel) const;

    /*!
     * \brief Returns the Link object in the list of <a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> links defined by \a rel.
     *
     * If no Link can be found, a \c nullptr will be returned.
     */
    Q_INVOKABLE Link* getLink(const QString &rel) const;



    /*!
     * \brief Returns a QVariantMap containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API. Will only contain properties that are not read only.
     */
    QVariantMap toVariant();

    /*!
     * \brief Returns a QJsonObject containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API. Will only contain properties that are not read only.
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
