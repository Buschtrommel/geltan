/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * refund.h
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

#ifndef REFUND_H
#define REFUND_H

#include <QObject>
#include <QDateTime>
#include <QVariantMap>
#include <QJsonObject>
#include <QUrl>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {
namespace PP {

class RefundPrivate;
class PaymentAmount;
class Link;

/*!
 * \brief Contains details about a refund transaction.
 *
 * \ppPaymentsApi{refund}
 *
 * \headerfile "" <Geltan/PP/Objects/refund.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Refund : public QObject
{
    Q_OBJECT
    /*!
     * \brief ID of the refund transaction.
     *
     * \ppApiName{id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>id() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>idChanged(const QString &id)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    /*!
     * \brief Details including both refunded amount (to payer) and refunded fee (to payee).
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
     * \brief State of the refund.
     *
     * \ppApiName{state}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::StateType</TD><TD>state() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(PayPal::StateType state)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::StateType state READ state NOTIFY stateChanged)
    /*!
     * \brief Reason description for the Sale transaction being refunded.
     *
     * \ppApiName{reason}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>reason() const</TD></TR><TR><TD>void</TD><TD>setReason(const QString &nReason)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>reasonChanged(const QString &reason)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString reason READ reason WRITE setReason NOTIFY reasonChanged)
    /*!
     * \brief ID of the Sale transaction being refunded.
     *
     * \ppApiName{sale_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>saleId() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>saleIdChanged(const QString &saleId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString saleId READ saleId NOTIFY saleIdChanged)
    /*!
     * \brief ID of the sale transaction being refunded.
     *
     * \ppApiName{capture_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>captureId() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>captureIdChanged(const QString &captureId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString captureId READ captureId NOTIFY captureIdChanged)
    /*!
     * \brief ID of the payment resource on which this transaction is based.
     *
     * \ppApiName{parent_payment}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>parentPayment() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>parentPaymentChanged(const QString &parentPayment)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString parentPayment READ parentPayment NOTIFY parentPaymentChanged)
    /*!
     * \brief Description of what is being refunded for.
     *
     * \ppApiName{description}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>description() const</TD></TR><TR><TD>void</TD><TD>setDescription(const QString &nDescription)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>descriptionChanged(const QString &description)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    /*!
     * \brief Time of refund.
     *
     * \ppApiName{create_time}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>createTime() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>createTimeChanged(const QDateTime &createTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime createTime READ createTime NOTIFY createTimeChanged)
    /*!
     * \brief Time that the resource was last updated.
     *
     * \ppApiName{update_time}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>updateTime() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>updateTimeChanged(const QDateTime &updateTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime updateTime READ updateTime NOTIFY updateTimeChanged)
    /*!
     * \brief The reason code for the refund state being pending.
     *
     * \ppApiName{reason_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::ReasonCode</TD><TD>reasonCode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>reasonCodeChanged(PayPal::ReasonCode reasonCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::ReasonCode reasonCode READ reasonCode NOTIFY reasonCodeChanged)
    /*!
     * \brief HATEOAS links related to this call.
     *
     * \ppApiName{links}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Link*></TD><TD>links() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>linksChanged(const QList<Link*> &links)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::Link*> links READ links NOTIFY linksChanged)
public:
    /*!
     * \brief Constructs a new empty Refund object.
     */
    explicit Refund(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Refund object from JSON data.
     */
    Refund(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Refund object from JSON data.
     */
    Refund(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Refund object.
     */
    ~Refund();

    QString id() const;
    PaymentAmount *amount() const;
    PayPal::StateType state() const;
    QString reason() const;
    QString saleId() const;
    QString captureId() const;
    QString parentPayment() const;
    QString description() const;
    QDateTime createTime() const;
    QDateTime updateTime() const;
    PayPal::ReasonCode reasonCode() const;
    QList<Link*> links() const;


    /*!
     * \brief Sets the ID of the refund transaction.
     *
     * 17 charactes max.
     */
    void setId(const QString &nId);
    void setAmount(PaymentAmount *nAmount);
    /*!
     * \brief Sets the state of the refund.
     */
    void setState(PayPal::StateType nState);
    void setReason(const QString &nReason);
    /*!
     * \brief Sets the ID of the Sale transaction being refunded.
     */
    void setSaleId(const QString &nSaleId);
    /*!
     * \brief Sets the ID of the Capture transaction being refunded.
     */
    void setCaptureId(const QString &nCaptureId);
    /*!
     * \brief Sets the ID of the payment resource on which this transaction is based.
     */
    void setParentPayment(const QString &nParentPayment);
    void setDescription(const QString &nDescription);
    /*!
     * \brief Sets date and time the refund was created.
     */
    void setCreateTime(const QDateTime &nCreateTime);
    /*!
     * \brief Sets date and time the refund was updated.
     */
    void setUpdateTime(const QDateTime &nUpdateTime);
    /*!
     * \brief Sets the reason code if the state is pending.
     */
    void setReasonCode(PayPal::ReasonCode nReasonCode);
    /*!
     * \brief Sets the list of HATEOAS links related to this call.
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
     * \brief Loads data from a QJsonDocument into the Refund object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Refund object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void idChanged(const QString &id);
    void amountChanged(PaymentAmount *amount);
    void stateChanged(PayPal::StateType state);
    void reasonChanged(const QString &reason);
    void saleIdChanged(const QString &saleId);
    void captureIdChanged(const QString &captureId);
    void parentPaymentChanged(const QString &parentPayment);
    void descriptionChanged(const QString &description);
    void createTimeChanged(const QDateTime &createTime);
    void updateTimeChanged(const QDateTime &updateTime);
    void reasonCodeChanged(PayPal::ReasonCode reasonCode);
    void linksChanged(const QList<Link*> &links);

protected:
    const QScopedPointer<RefundPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Refund)
    Q_DECLARE_PRIVATE(Refund)

};

}
}


#endif // REFUND_H
