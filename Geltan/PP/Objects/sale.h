/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/sale.h
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

#ifndef SALE_H
#define SALE_H

#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>
#include <Geltan/PP/ppenumsmap.h>

namespace Geltan {
namespace PP {

class SalePrivate;
class PaymentAmount;
class Currency;
class FMFDetails;
class ProcessorResponse;
class Link;

/*!
 * \brief Contains details about a sale transaction
 *
 * \ppPaymentsApi{sale}
 *
 * \headerfile "" <Geltan/PP/Objects/sale.h>
 */
class GELTANSHARED_EXPORT Sale : public QObject
{
    Q_OBJECT
    /*!
     * \brief Identifier of the sale transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>id() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>idChanged(const QString &id)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    /*!
     * \brief Identifier of the purchased unit associated with this object.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>purchaseUnitReferenceId() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>purchaseUnitReferenceIdChanged(const QString &purchaseUnitReferenceId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString purchaseUnitReferenceId READ purchaseUnitReferenceId NOTIFY purchaseUnitReferenceIdChanged)
    /*!
     * \brief Amount being collected.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PaymentAmount*</TD><TD>amount() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>amountChanged(PaymentAmount *amount)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PaymentAmount *amount READ amount NOTIFY amountChanged)
    /*!
     * \brief Specifies payment mode of the transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::PaymentModeType</TD><TD>paymentMode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentModeChanged(PayPal::PaymentModeType paymentMode)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::PaymentModeType paymentMode READ paymentMode NOTIFY paymentModeChanged)
    /*!
     * \brief State of the sale transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::StateType</TD><TD>state() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(PayPal::StateType state)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::StateType state READ state NOTIFY stateChanged)
    /*!
     * \brief Reason code for the transaction state being Pending or Reversed.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::ReasonCode</TD><TD>reasonCode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>reasonCodeChanged(PayPal::ReasonCode reasonCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::ReasonCode reasonCode READ reasonCode NOTIFY reasonCodeChanged)
    /*!
     * \brief The level of seller protection in force for the transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::ProtectionEligibility</TD><TD>protectionEligibility() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>protectionEligibilityChanged(PayPal::ProtectionEligibility protectionEligibility)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::ProtectionEligibility protectionEligibility READ protectionEligibility NOTIFY protectionEligibilityChanged)
    /*!
     * \brief The kind of seller protection in force for the transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<PayPal::ProtectionEligibilityType></TD><TD>protectionEligibilityType() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>protectionEligibilityTypeChanged(QList<PayPal::ProtectionEligibilityType> protectionEligibilityType)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::PayPal::ProtectionEligibilityType> protectionEligibilityType READ protectionEligibilityType NOTIFY protectionEligibilityTypeChanged)
    /*!
     * \brief Expected clearing time for eCheck Transactions.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>clearingTime() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>clearingTimeChanged(const QDateTime &clearingTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime clearingTime READ clearingTime NOTIFY clearingTimeChanged)
    /*!
     * \brief Status of the Recipient Fund.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PaymentHoldStatus</TD><TD>paymentHoldStatus() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentHoldStatusChanged(PaymentHoldStatus paymentHoldStatus)</TD></TR></TABLE>
     */
    Q_PROPERTY(PaymentHoldStatus paymentHoldStatus READ paymentHoldStatus NOTIFY paymentHoldStatusChanged)
    /*!
     * \brief Reasons for PayPal holding recipient fund.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QStringList</TD><TD>paymentHoldReasons() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentHoldReasonsChanged(const QStringList &paymentHoldReasons)</TD></TR></TABLE>
     */
    Q_PROPERTY(QStringList paymentHoldReasons READ paymentHoldReasons NOTIFY paymentHoldReasonsChanged)
    /*!
     * \brief Transaction fee charged by PayPal for this transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>Currency*</TD><TD>transactionFee() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>transactionFeeChanged(Currency *transactionFee)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Currency *transactionFee READ transactionFee NOTIFY transactionFeeChanged)
    /*!
     * \brief Net amount the merchant receives for this transaction in their receivable currency.
     *
     * Returned only in cross-currency use cases where a merchant bills a buyer in a non-primary currency for that buyer.
     *
     * \par Access functions:
     * <TABLE><TR><TD>Currency*</TD><TD>receivableAmount() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>receivableAmountChanged(Currency *receivableAmount)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Currency *receivableAmount READ receivableAmount NOTIFY receivableAmountChanged)
    /*!
     * \brief Exchange rate applied for this transaction.
     *
     * Returned only in cross-currency use cases where a merchant bills a buyer in a non-primary currency for that buyer.
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>exchangeRate() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>exchangeRateChanged(float exchangeRate)</TD></TR></TABLE>
     */
    Q_PROPERTY(float exchangeRate READ exchangeRate NOTIFY exchangeRateChanged)
    /*!
     * \brief Fraud Management Filter (FMF) details applied for the payment that could result in accept, deny, or pending action.
     *
     * Returned in a payment response only if the merchant has enabled FMF in the profile settings and one
     * of the fraud filters was triggered based on those settings. See \link https://paypal.github.io/docs/classic/fmf/integration-guide/FMFSummary/ Fraud Management Filters Summary \endlink for more information.
     *
     * \par Access functions:
     * <TABLE><TR><TD>FMFDetails*</TD><TD>fmfDetails() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>fmfDetailsChanged(FMFDetails *fmfDetails)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::FMFDetails *fmfDetails READ fmfDetails NOTIFY fmfDetailsChanged)
    /*!
     * \brief Receipt id is a payment identification number returned for guest users to identify the payment.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>receiptId() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>receiptIdChanged(const QString &receiptId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString receiptId READ receiptId NOTIFY receiptIdChanged)
    /*!
     * \brief ID of the payment resource on which this transaction is based.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>parentPayment() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>parentPaymentChanged(const QString &parentPayment)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString parentPayment READ parentPayment NOTIFY parentPaymentChanged)
    /*!
     * \brief Response codes returned by the processor concerning the submitted payment.
     *
     * Only supported when the \c payment_method is set to \c credit_card.
     *
     * \par Access functions:
     * <TABLE><TR><TD>ProcessorResponse*</TD><TD>processorResponse() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>processorResponseChanged(ProcessorResponse *processorResponse)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::ProcessorResponse *processorResponse READ processorResponse NOTIFY processorResponseChanged)
    /*!
     * \brief ID of the billing agreement used as reference to execute this transaction.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>billingAgreementId() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>billingAgreementIdChanged(const QString &billingAgreementId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString billingAgreementId READ billingAgreementId NOTIFY billingAgreementIdChanged)
    /*!
     * \brief Time of sale.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>createTime() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>createTimeChanged(const QDateTime &createTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime createTime READ createTime NOTIFY createTimeChanged)
    /*!
     * \brief Time the resource was last updated.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>updateTime() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>updateTimeChanged(const QDateTime &updateTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime updateTime READ updateTime NOTIFY updateTimeChanged)
    /*!
     * \brief HATEOAS links related to this call.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Link*></TD><TD>links() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>linksChanged(const QList<Link*> &links)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::Link*> links READ links NOTIFY linksChanged)
public:
    /*!
     * \brief Constructs a new empty Sale object.
     */
    explicit Sale(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Sale object from JSON data.
     */
    Sale(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Sale object from JSON data.
     */
    Sale(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Sale object.
     */
    ~Sale();

    /*!
     * \brief Status of the Recipient Fund.
     */
    enum PaymentHoldStatus {
        NO_PAYMENT_HOLD_STATUS  = 0,
        HELD                    = 1
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(PaymentHoldStatus)
#else
    Q_ENUMS(PaymentHoldStatus)
#endif

    QString id() const;
    QString purchaseUnitReferenceId() const;
    PaymentAmount *amount() const;
    PayPal::PaymentModeType paymentMode() const;
    PayPal::StateType state() const;
    PayPal::ReasonCode reasonCode() const;
    PayPal::ProtectionEligibility protectionEligibility() const;
    QList<PayPal::ProtectionEligibilityType> protectionEligibilityType() const;
    QDateTime clearingTime() const;
    PaymentHoldStatus paymentHoldStatus() const;
    QStringList paymentHoldReasons() const;
    Currency *transactionFee() const;
    Currency *receivableAmount() const;
    float exchangeRate() const;
    FMFDetails *fmfDetails() const;
    QString receiptId() const;
    QString parentPayment() const;
    ProcessorResponse *processorResponse() const;
    QString billingAgreementId() const;
    QDateTime createTime() const;
    QDateTime updateTime() const;
    QList<Link*> links() const;


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
     * \brief Loads data from a QJsonDocument into the Sale object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Sale object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void idChanged(const QString &id);
    void purchaseUnitReferenceIdChanged(const QString &purchaseUnitReferenceId);
    void amountChanged(PaymentAmount *amount);
    void paymentModeChanged(PayPal::PaymentModeType paymentMode);
    void stateChanged(PayPal::StateType state);
    void reasonCodeChanged(PayPal::ReasonCode reasonCode);
    void protectionEligibilityChanged(PayPal::ProtectionEligibility protectionEligibility);
    void protectionEligibilityTypeChanged(const QList<PayPal::ProtectionEligibilityType> &protectionEligibilityType);
    void clearingTimeChanged(const QDateTime &clearingTime);
    void paymentHoldStatusChanged(PaymentHoldStatus paymentHoldStatus);
    void paymentHoldReasonsChanged(const QStringList &paymentHoldReasons);
    void transactionFeeChanged(Currency *transactionFee);
    void receivableAmountChanged(Currency *receivableAmount);
    void exchangeRateChanged(float exchangeRate);
    void fmfDetailsChanged(FMFDetails *fmfDetails);
    void receiptIdChanged(const QString &receiptId);
    void parentPaymentChanged(const QString &parentPayment);
    void processorResponseChanged(ProcessorResponse *processorResponse);
    void billingAgreementIdChanged(const QString &billingAgreementId);
    void createTimeChanged(const QDateTime &createTime);
    void updateTimeChanged(const QDateTime &updateTime);
    void linksChanged(const QList<Link*> &links);

protected:
    const QScopedPointer<SalePrivate> d_ptr;

private:
    Q_DISABLE_COPY(Sale)
    Q_DECLARE_PRIVATE(Sale)

};

}
}

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::Sale::PaymentHoldStatus)
#endif

#endif // SALE_H
