/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * transaction.h
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

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <QUrl>
#include <QAbstractListModel>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class TransactionPrivate;
class Item;
class PaymentAmount;
class PaymentOptions;
class Related;
class ItemList;
class Payee;

/*!
 * \brief A transaction defines the contract of a payment - what is the payment for and who is fulfilling it.
 *
 * The model provides access to the Related resources objects connected with this Transaction. The Related objects
 * are stored as pointers as well as the members of the Related obejct are stored as pointers. If a specific member
 * of a Related object is not set, a nullptr will be returned. So you should check for a nullptr before you use the
 * members.
 *
 * \ppPaymentsApi{transaction}
 *
 * \headerfile "" <Geltan/PP/Objects/transaction.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Transaction : public QAbstractListModel
{
    Q_OBJECT
    /*!
     * \brief Merchant identifier to purchase unit.
     *
     * \ppApiName{reference_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>referenceId() const</TD></TR><TR><TD>void</TD><TD>setReferenceId(const QString &nReferenceId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>referenceIdChanged(const QString &referenceId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString referenceId READ referenceId WRITE setReferenceId NOTIFY referenceIdChanged)
    /*!
     * \brief Payment amount with break-ups.
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
     * \brief Description of what is being paid for.
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
     * \brief Note to the recipient of the funds in this transaction.
     *
     * \ppApiName{note_to_payee}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>noteToPayee() const</TD></TR><TR><TD>void</TD><TD>setNoteToPayee(const QString &nNoteToPayee)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>noteToPayeeChanged(const QString &noteToPayee)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString noteToPayee READ noteToPayee WRITE setNoteToPayee NOTIFY noteToPayeeChanged)
    /*!
     * \brief Free-form field for the use of clients.
     *
     * \ppApiName{custom}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>custom() const</TD></TR><TR><TD>void</TD><TD>setCustom(const QString &nCustom)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>customChanged(const QString &custom)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString custom READ custom WRITE setCustom NOTIFY customChanged)
    /*!
     * \brief Invoice number to track this payment.
     *
     * \ppApiName{invoice_number}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>invoiceNumber() const</TD></TR><TR><TD>void</TD><TD>setInvoiceNumber(const QString &nInvoiceNumber)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>invoiceNumberChanged(const QString &invoiceNumber)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString invoiceNumber READ invoiceNumber WRITE setInvoiceNumber NOTIFY invoiceNumberChanged)
    /*!
     * \brief Soft PaymentOptionsdescriptor used when charging this funding source.
     *
     * \ppApiName{soft_descriptor}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>softDescriptor() const</TD></TR><TR><TD>void</TD><TD>setSoftDescriptor(const QString &nSoftDescriptor)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>softDescriptorChanged(const QString &softDescriptor)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString softDescriptor READ softDescriptor WRITE setSoftDescriptor NOTIFY softDescriptorChanged)
    /*!
     * \brief Payment options requested for this purchase unit.
     *
     * \ppApiName{payment_options}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PaymentOptions*</TD><TD>paymentOptions() const</TD></TR><TR><TD>void</TD><TD>setPaymentOptions(PaymentOptions *nPaymentOptions)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentOptionsChanged(PaymentOptions *paymentOptions)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PaymentOptions *paymentOptions READ paymentOptions WRITE setPaymentOptions NOTIFY paymentOptionsChanged)
    /*!
     * \brief List of items being paid for.
     *
     * \ppApiName{item_list}
     *
     * \par Access functions:
     * <TABLE><TR><TD>ItemList*</TD><TD>itemList() const</TD></TR><TR><TD>void</TD><TD>setItemList(ItemList *nItemList)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>itemListChanged(ItemList *itemList)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::ItemList *itemList READ itemList WRITE setItemList NOTIFY itemListChanged)
    /*!
     * \brief URL to send payment notifications.
     *
     * \ppApiName{notify_url}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QUrl</TD><TD>notifyUrl() const</TD></TR><TR><TD>void</TD><TD>setNotifyUrl(const QUrl &nNotifyUrl)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>notifyUrlChanged(const QUrl &notifyUrl)</TD></TR></TABLE>
     */
    Q_PROPERTY(QUrl notifyUrl READ notifyUrl WRITE setNotifyUrl NOTIFY notifyUrlChanged)
    /*!
     * \brief URL on merchant site pertaining to this payment.
     *
     * \ppApiName{order_url}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QUrl</TD><TD>orderUrl() const</TD></TR><TR><TD>void</TD><TD>setOrderUrl(const QUrl &nOrderUrl)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>orderUrlChanged(const QUrl &orderUrl)</TD></TR></TABLE>
     */
    Q_PROPERTY(QUrl orderUrl READ orderUrl WRITE setOrderUrl NOTIFY orderUrlChanged)
    /*!
     * \brief List of financial transaction (Sale, Authorization, Capture, Refund) related to the payment.
     *
     * Setting a new list of Related resources will reset the current model data and will delete all
     * Related objects currently available in the model.
     *
     * \ppApiName{related_resources}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Related*></TD><TD>relatedResources() const</TD></TR><TR><TD>void</TD><TD>setRelatedResources(const QList<Related*> &nRelatedResources)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>relatedResourcesChanged(const QList<Related*> &relatedResources)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::Related*> relatedResources READ relatedResources WRITE setRelatedResources NOTIFY relatedResourcesChanged)
    /*!
     * \brief Information about the payee.
     *
     * \par Access functions:
     * <TABLE><TR><TD>Payee*</TD><TD>payee() const</TD></TR><TR><TD>void</TD><TD>setPayee(Payee *nPayee)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payeeChanged(Payee *payee)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Payee *payee READ payee WRITE setPayee NOTIFY payeeChanged)
public:
    /*!
     * \brief Constructs a new empty Transaction object.
     */
    explicit Transaction(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Transaction object from JSON data.
     */
    Transaction(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Transaction object from JSON data.
     */
    Transaction(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Transaction object.
     */
    ~Transaction();

    /*!
     * \brief The roles of this model.
     *
     * To access them from QML, use the enumeration name starting lowercase.
     */
    enum Roles {
        RelItem = Qt::UserRole + 1, /**< Pointer to the Related object itself. */
        Sale,                       /**< Pointer to the Sale object inside the Related object. */
        Authorization,              /**< Pointer to the Authorization object inside the Related object. */
        Order,                      /**< Pointer to the Order object inside the Related object. */
        Capture,                    /**< Pointer to the Capture object inside the Related object. */
        Refund                      /**< Pointer to the Refund object inside the Related object. */
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

    QString referenceId() const;
    PaymentAmount *amount() const;
    QString description() const;
    QString noteToPayee() const;
    QString custom() const;
    QString invoiceNumber() const;
    QString softDescriptor() const;
    PaymentOptions *paymentOptions() const;
    ItemList *itemList() const;
    QUrl notifyUrl() const;
    QUrl orderUrl() const;
    QList<Related*> relatedResources() const;
    Payee *payee() const;

    void setReferenceId(const QString &nReferenceId);
    void setAmount(PaymentAmount *nAmount);
    void setDescription(const QString &nDescription);
    void setNoteToPayee(const QString &nNoteToPayee);
    void setCustom(const QString &nCustom);
    void setInvoiceNumber(const QString &nInvoiceNumber);
    void setSoftDescriptor(const QString &nSoftDescriptor);
    void setPaymentOptions(PaymentOptions *nPaymentOptions);
    void setItemList(ItemList *nItemList);
    void setNotifyUrl(const QUrl &nNotifyUrl);
    void setOrderUrl(const QUrl &nOrderUrl);
    void setRelatedResources(const QList<Related*> &nRelatedResources);
    void setPayee(Payee *nPayee);

    /*!
     * \brief Adds a new Item to the Transaction ItemList object.
     *
     * If the Item to add is living in a different thread, it will be moved
     * to the ItemLists's thread. Also the ItemList will be set as parent of the Item.
     *
     * If no ItemList object is present, a new ItemList object will be created as child
     * of the Transaction object.
     *
     * Returns true if the Item has been added to the model.
     */
    bool addItem(Item *i);

    /*!
     * \brief Creates a new empty Item and adds it to the Transaction ItemList object and returns a pointer to it.
     *
     * The ItemList object will be the parent of the newly created Item object.
     *
     * If no ItemList object is present, a new ItemList object will be created as child
     * of the Transaction object.
     */
    Q_INVOKABLE Geltan::PP::Item *addNewItem();

    /*!
     * \brief Adds a new Related resource to the model.
     *
     * If the resource to add is living in a different thread it will be moved
     * to the model's thread. Also the model will be set as parent of the Related resource.
     *
     * Returns true if the Related resource has been added to the model.
     */
    bool addRelatedResource(Related *resource);

    /*!
     * \brief Removes the Related resource at index position \a idx from the model and destroys it.
     */
    void removeRelatedResource(int idx);

    /*!
     * \brief Removes the Related resource identified by the pointer from the model and destroys it.
     * \overload
     */
    void removeRelatedResource(Related *resource);

    /*!
     * \brief Removes the Related resource at index position \a idx from the model and returns a pointer to it.
     *
     * The resource will not be deleted, it's parent object will be set to \c nullptr. If the resource can not be
     * found, a \c nullptr will be returned.
     */
    Related *takeRelatedResource(int idx);

    /*!
     * \brief Removes the Related resource at identified by the pointer from the model and returns the pointer to it.
     *
     * The resource will not be delete, it's parent object will be set to \c nullptr. If the resource can not be
     * found, a \c nullptr will be returned.
     */
    Related *takeRelatedResource(Related *resource);


    /*!
     * \brief Sets the amount of the transaction, with optional details.
     *
     * This will create a new PaymentAmount object as child of the Transaction object
     * if no such object is already available. If details (suche as subtotal etc.) are used,
     * a Details object will be created as child of the PaymentAmount object, if not already present.
     */
    void setPaymentAmount(const QString &currency, float total, float subtotal = 0.0, float shipping = 0.0, float tax = 0.0, float handlingFee = 0.0, float shippingDiscount = 0.0, float insurance = 0.0, float giftWrap = 0.0);



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
     * \brief Loads data from a QJsonDocument into the Transaction object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Transaction object.
     */
    void loadFromJson(const QJsonObject &json);



Q_SIGNALS:
    void referenceIdChanged(const QString &referenceId);
    void amountChanged(PaymentAmount *amount);
    void descriptionChanged(const QString &description);
    void noteToPayeeChanged(const QString &noteToPayee);
    void customChanged(const QString &custom);
    void invoiceNumberChanged(const QString &invoiceNumber);
    void softDescriptorChanged(const QString &softDescriptor);
    void paymentOptionsChanged(PaymentOptions *paymentOptions);
    void itemListChanged(ItemList *itemList);
    void notifyUrlChanged(const QUrl &notifyUrl);
    void orderUrlChanged(const QUrl &orderUrl);
    void relatedResourcesChanged(const QList<Related*> &relatedResources);
    void payeeChanged(Payee *payee);

protected:
    const QScopedPointer<TransactionPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Transaction)
    Q_DECLARE_PRIVATE(Transaction)

};

}
}


#endif // TRANSACTION_H
