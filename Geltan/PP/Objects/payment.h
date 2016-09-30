/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * address.h
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

#ifndef PAYMENT_H
#define PAYMENT_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QAbstractListModel>
#include <QDateTime>
#include <QUrl>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class PaymentPrivate;
class Payer;
class Transaction;
class RedirectUrls;
class Link;

/*!
 * \brief Contains information about a specific payment process.
 *
 * \ppPaymentsApi{payment}
 *
 * \headerfile "" <Geltan/PP/Objects/payment.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-12
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Payment : public QAbstractListModel
{
    Q_OBJECT
    /*!
     * \brief Identifier of the payment resource created.
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
     * \brief Payment intent.
     *
     * \ppApiName{intent}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Intent</TD><TD>intent() const</TD></TR><TR><TD>void</TD><TD>setIntent(Intent nIntent)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>intentChanged(Intent intent)</TD></TR></TABLE>
     */
    Q_PROPERTY(Intent intent READ intent WRITE setIntent NOTIFY intentChanged)
    /*!
     * \brief A resource representing a Payer that funds a payment.
     *
     * \ppApiName{payer}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Payer*</TD><TD>payer() const</TD></TR><TR><TD>void</TD><TD>setPayer(Payer *nPayer)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payerChanged(Payer *payer)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Payer *payer READ payer WRITE setPayer NOTIFY payerChanged)
    /*!
     * \brief A transaction defines the contract of a payment - what is the payment for and who is fulfilling it.
     *
     * \ppApiName{transactions}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Transaction*></TD><TD>transactions() const</TD></TR><TR><TD>void</TD><TD>setTransactions(const QList<Transaction*> &nTransactions)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>transactionsChanged(const QList<Transaction*> &transactions)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::Transaction*> transactions READ transactions WRITE setTransactions NOTIFY transactionsChanged)
    /*!
     * \brief The state of the payment, authorization, or order transaction.
     *
     * \ppApiName{state}
     *
     * \par Access functions:
     * <TABLE><TR><TD>State</TD><TD>state() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>stateChanged(State state)</TD></TR></TABLE>
     */
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    /*!
     * \brief PayPal generated identifier for the merchant's payment experience profile.
     *
     * Refer to this \link https://developer.paypal.com/docs/api/#payment-experience link \endlink to create experience profile ID.
     *
     * \ppApiName{experience_profile_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>experienceProfileId() const</TD></TR><TR><TD>void</TD><TD>setExperienceProfileId(const QString &nExperienceProfileId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>experienceProfileIdChanged(const QString &experienceProfileId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString experienceProfileId READ experienceProfileId WRITE setExperienceProfileId NOTIFY experienceProfileIdChanged)
    /*!
     * \brief Free-form field for the use of clients to pass in a message to the payer.
     *
     * \ppApiName{note_to_payer}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>noteToPayer() const</TD></TR><TR><TD>void</TD><TD>setNoteToPayer(const QString &nNoteToPayer)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>noteToPayerChanged(const QString &noteToPayer)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString noteToPayer READ noteToPayer WRITE setNoteToPayer NOTIFY noteToPayerChanged)
    /*!
     * \brief Set of redirect URLs you provide only for PayPal-based payments.
     *
     * \ppApiName{redirect_urls}
     *
     * \par Access functions:
     * <TABLE><TR><TD>RedirectUrls*</TD><TD>redirectUrls() const</TD></TR><TR><TD>void</TD><TD>setRedirectUrls(RedirectUrls *nRedirectUrls)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>redirectUrlsChanged(RedirectUrls *redirectUrls)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::RedirectUrls *redirectUrls READ redirectUrls WRITE setRedirectUrls NOTIFY redirectUrlsChanged)
    /*!
     * \brief Failure reason code returned when the payment failed for some valid reasons.
     *
     * \ppApiName{failure_reason}
     *
     * \par Access functions:
     * <TABLE><TR><TD>FailureReason</TD><TD>failureReason() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>failureReasonChanged(FailureReason failureReason)</TD></TR></TABLE>
     */
    Q_PROPERTY(FailureReason failureReason READ failureReason NOTIFY failureReasonChanged)
    /*!
     * \brief Payment creation time as defined in RFC 3339 Section 5.6.
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
     * \brief Payment update time as defined in RFC 3339 Section 5.6.
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
     * \brief Constructs a new Payment object.
     */
    explicit Payment(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Payment object from JSON data.
     */
    Payment(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Payment object from JSON data.
     */
    Payment(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Payment object.
     */
    ~Payment();

    /*!
     * \brief Payment intent.
     */
    enum Intent {
        NoIntent    = 0,    /**< No intent defined. */
        Sale        = 1,    /**< Sale intent. */
        Authorize   = 2,    /**< Authorization intent. */
        Order       = 3     /**< Order intent. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(Intent)
#else
    Q_ENUMS(Intent)
#endif



    /*!
     * \brief The state of the payment.
     */
    enum State {
        NoState     = 0,    /**< No state defined. */
        Created     = 1,    /**< The payment has been created. */
        Approved    = 2,    /**< The payment has been approved. */
        Failed      = 3     /**< The payment failed. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(State)
#else
    Q_ENUMS(State)
#endif


    /*!
     * \brief Failure reason code returned when the payment failed some valid reasons.
     */
    enum FailureReason {
        NoFailureReason             = 0,    /**< No valid failure reason / no failure. */
        UnableToCompleteTransaction = 1,    /**< Unable to complete the transaction. */
        InvalidPaymentMethod        = 2,    /**< The payment method is invalid. */
        PayerCannotPay              = 3,    /**< The payer can not pay. */
        CannotPayThisPayee          = 4,    /**< The payee can not be payed. */
        RedirectRequired            = 5,    /**< A redirect is required. */
        PayeeFilterRestrictions     = 6     /**< Payee filter restrictions let the payment fail. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(FailureReason)
#else
    Q_ENUMS(FailureReason)
#endif


    /*!
     * \brief Model roles.
     *
     * To use the model data in QML, use the enumeration name starting lowercase.
     */
    enum Roles {
        Item = Qt::UserRole + 1 /**< Returns the transaction item itself. */
    };


    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractListModel.
     */
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;


    QString id() const;
    Intent intent() const;
    Payer *payer() const;
    QList<Transaction*> transactions() const;
    State state() const;
    QString experienceProfileId() const;
    QString noteToPayer() const;
    RedirectUrls *redirectUrls() const;
    FailureReason failureReason() const;
    QDateTime createTime() const;
    QDateTime updateTime() const;
    QList<Link*> links() const;

    /*!
     * \brief Sets the payment ID.
     */
    void setId(const QString &nId);
    void setIntent(Intent nIntent);
    void setPayer(Payer *nPayer);
    void setTransactions(const QList<Transaction*> &nTransactions);
    /*!
     * \brief Sets the payment state.
     */
    void setState(State nState);
    void setExperienceProfileId(const QString &nExperienceProfileId);
    void setNoteToPayer(const QString &nNoteToPayer);
    void setRedirectUrls(RedirectUrls *nRedirectUrls);
    /*!
     * \brief Sets the failure reason.
     */
    void setFailureReason(FailureReason nFailureReason);
    /*!
     * \brief Sets the creation time of the payment.
     */
    void setCreateTime(const QDateTime &nCreateTime);
    /*!
     * \brief Sets the update time of the payment.
     */
    void setUpdateTime(const QDateTime &nUpdateTime);
    /*!
     * \brief Sets the HATEOAS links of the payment for related calls.
     */
    void setLinks(const QList<Link*> &nLinks);

    /*!
     * \brief Adds a new Transaction to the list of transactions.
     *
     * If the transaction is living in another thread, it will be tried to move it
     * to the model's thread. If that fails, the transaction will not be added. If the
     * move was successful, the model Payment object will be set as parent of the Transaction.
     *
     * Returns true if the item has been added successful.
     */
    Q_INVOKABLE bool addTransaction(Transaction *nTransaction);

    /*!
     * \brief Adds a list of Transaction objects to the current list of transactions.
     *
     * If the transactions are living in another thread, they will be tried to be moved
     * to the model's thread. If that fails, the transaction will not be added. If the
     * move was successful, the model Payment object will be set as parent of each Transaction
     * in the list.
     */
    Q_INVOKABLE void addTransactions(const QList<Transaction*> &nTransactions);

    /*!
     * \brief Adds a new empty Transaction to the list of transactions and returns the pointer to it.
     *
     * The Payment object will be set as parent for the new transaction. If it fails
     * to add a new transaction, a \c nullptr will be returned. This will also create an empty PaymentAmount
     * object as child of the new Transaction object.
     */
    Q_INVOKABLE Geltan::PP::Transaction *addNewTransaction();

    /*!
     * \brief Adds a new Transaction and sets the amount, currency and description and returns the pointer to the new Transaction.
     *
     * The Payment object will be set as parent for the new transaction. If it fails
     * to add a new transaction, a \c nullptr will be returned. This will also create a new PaymentAmount
     * object as child of the Transaction object and sets the total and currency to the PaymentAmount object.
     */
    Q_INVOKABLE Geltan::PP::Transaction *addNewTransaction(float total, const QString &currency, const QString &description = QString());

    /*!
     * \brief Removes the Transaction at index \a idx from the model and deletes it.
     */
    Q_INVOKABLE void removeTransaction(int idx);

    /*!
     * \brief Removes the Transaction identified by its pointer from the model.
     */
    Q_INVOKABLE void removeTransaction(Transaction *transaction);

    /*!
     * \brief Removes the Transaction at index \a idx from the model and returns the pointer to it.
     *
     * The parent object of the Transaction will be set to a \c nullptr. If the transaction can not
     * be found, a \c nullptr will be returned.
     */
    Q_INVOKABLE Transaction* takeTransaction(int idx);

    /*!
     * \brief Removes the Transaction identified by tis pointer from the model and returns the pointer to it.
     *
     * The parent object of the Transaction will be set to \c nullptr. If the transaction can not
     * be found, a \c nullptr will be returned.
     */
    Q_INVOKABLE Transaction* takeTransaction(Transaction *transaction);

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
     * \brief Adds the redirect URLs to the payment object.
     *
     * If no RedirectUrls object is available, a new one will be created.
     */
    Q_INVOKABLE void addRedirectUrls(const QUrl &returnUrl, const QUrl &cancelUrl);


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
     * \brief Returns a QJsonDocument containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API.
     */
    QJsonDocument toJsonDocument();

    /*!
     * \brief Returns a binary representation of the Payment in JSON format.
     *
     * \sa QJsonDocument::toBinaryData()
     */
    QByteArray toBinaryData();

    /*!
     * \brief Converts the Payment object data to a UTF-8 encoded JSON document.
     *
     * \sa QJsonDocument::toJson()
     */
    QByteArray toJson();

    /*!
     * \brief Loads data from a QJsonDocument into the Payment object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Payment object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void idChanged(const QString &id);
    void intentChanged(Intent intent);
    void payerChanged(Payer *payer);
    void transactionsChanged(const QList<Transaction*> &transactions);
    void stateChanged(State state);
    void experienceProfileIdChanged(const QString &experienceProfileId);
    void noteToPayerChanged(const QString &noteToPayer);
    void redirectUrlsChanged(RedirectUrls *redirectUrls);
    void failureReasonChanged(FailureReason failureReason);
    void createTimeChanged(const QDateTime &createTime);
    void updateTimeChanged(const QDateTime &updateTime);
    void linksChanged(const QList<Link*> &links);

protected:
    const QScopedPointer<PaymentPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Payment)
    Q_DECLARE_PRIVATE(Payment)

};

}
}
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::Payment::Intent)
Q_DECLARE_METATYPE(Geltan::PP::Payment::State)
Q_DECLARE_METATYPE(Geltan::PP::Payment::FailureReason)
#endif


#endif // PAYMENT_H
