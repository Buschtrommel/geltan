/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * itemlist.h
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

#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {



class ItemListPrivate;
class ShippingAddress;
class Item;

/*!
 * \brief Provides a list of items together with some additional information.
 *
 * \ppPaymentsApi{item_list}
 *
 * \headerfile "" <Geltan/PP/Objects/itemlist.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT ItemList : public QAbstractListModel
{
    Q_OBJECT
    /*!
     * \brief Item details.
     *
     * Setting a new list of Item objects will reset the current model data and will delete all
     * Item objects currently available in the model.
     *
     * \ppApiName{items}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Item*></TD><TD>items() const</TD></TR><TR><TD>void</TD><TD>setItems(const QList<Item*> &nItems)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>itemsChanged(const QList<Item*> &items)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Item*> items READ items WRITE setItems NOTIFY itemsChanged)
    /*!
     * \brief Extended Address object used as shipping address in a payment.
     *
     * \ppApiName{shipping_address}
     *
     * \par Access functions:
     * <TABLE><TR><TD>ShippingAddress*</TD><TD>shippingAddress() const</TD></TR><TR><TD>void</TD><TD>setShippingAddress(ShippingAddress *nShippingAddress)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>shippingAddressChanged(ShippingAddress *shippingAddress)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::ShippingAddress *shippingAddress READ shippingAddress WRITE setShippingAddress NOTIFY shippingAddressChanged)
    /*!
     * \brief Shipping method used for this payment like USPSParcel etc.
     *
     * \ppApiName{shipping_method}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>shippingMethod() const</TD></TR><TR><TD>void</TD><TD>setShippingMethod(const QString &nShippingMethod)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>shippingMethodChanged(const QString &shippingMethod)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString shippingMethod READ shippingMethod WRITE setShippingMethod NOTIFY shippingMethodChanged)
    /*!
     * \brief Allows merchant's to share payer’s contact number with PayPal for the current payment.
     *
     * Final contact number of payer associated with the transaction might be same as shipping_phone_number 
     * ordifferent based on Payer’s action on PayPal. The phone number must be represented in its canonical
     * internationalformat, as defined by the E.164 numbering plan.
     *
     * \ppApiName{shipping_phone_number}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>shippingPhoneNumber() const</TD></TR><TR><TD>void</TD><TD>setShippingPhoneNumber(const QString &nShippingPhoneNumber)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>shippingPhoneNumberChanged(const QString &shippingPhoneNumber)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString shippingPhoneNumber READ shippingPhoneNumber WRITE setShippingPhoneNumber NOTIFY shippingPhoneNumberChanged)
public:
    /*!
     * \brief Constructs a new empty ItemList model object.
     */
    explicit ItemList(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new ItemList model object from JSON data.
     */
    ItemList(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new ItemList model object from JSON data.
     */
    ItemList(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the ItemList object.
     */
    ~ItemList();

    /*!
     * \brief The roles of this model.
     *
     * Use the enumeration name starting lowercase and withouth the "Role" suffix to
     * access the role from QML.
     */
    enum Roles {
        ItemRole = Qt::UserRole + 1     /**< Returns a pointer to the model item itself. */
    };

    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemMOdel.
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

    QList<Item*> items() const;
    ShippingAddress *shippingAddress() const;
    QString shippingMethod() const;
    QString shippingPhoneNumber() const;

    void setItems(const QList<Item*> &nItems);
    void setShippingAddress(ShippingAddress *nShippingAddress);
    void setShippingMethod(const QString &nShippingMethod);
    void setShippingPhoneNumber(const QString &nShippingPhoneNumber);

    /*!
     * \brief Adds a new Item to the model.
     *
     * If the Item to add is living in a different thread, it will be moved
     * to the model's thread. Also the model will be set as parent of the Item.
     *
     * Returns true if the item has been added to the model.
     */
    bool addItem(Item *i);

    /*!
     * \brief Creates a new empty Item and adds it to the model and returns a pointer to it.
     *
     * The ItemList object will be the parent of the newly created Item object.
     */
    Q_INVOKABLE Geltan::PP::Item *addNewItem();

    /*!
     * \brief Removes the Item at index position \a idx from the model.
     */
    Q_INVOKABLE void removeItem(int idx);

    /*!
     * \brief Removes the Item identified by its pointer from the model.
     * \overload
     */
    Q_INVOKABLE void removeItem(Item *i);

    /*!
     * \brief Removes the Item at index position \a idx from the model and returns a pointer to it.
     *
     * The Item will not be deleted, it's parent object will be set to \c nullptr. If the Item can not be
     * found, a \c nullptr will be returned.
     */
    Q_INVOKABLE Item *takeItem(int idx);

    /*!
     * \brief Removes the Item identified by the pointer from the model and returns the pointer to it.
     *
     * The Item will not be deleted, it's parent object will be set to \c nullptr. If the Item can not be
     * found, a \c nullptr will be returned.
     */
    Q_INVOKABLE Item *takeItem(Item *i);



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
     * \brief Loads data from a QJsonDocument into the ItemList object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the ItemList object.
     */
    void loadFromJson(const QJsonObject &json);

Q_SIGNALS:
    void itemsChanged(const QList<Item*> &items);
    void shippingAddressChanged(ShippingAddress *shippingAddress);
    void shippingMethodChanged(const QString &shippingMethod);
    void shippingPhoneNumberChanged(const QString &shippingPhoneNumber);

protected:
    const QScopedPointer<ItemListPrivate> d_ptr;

private:
    Q_DISABLE_COPY(ItemList)
    Q_DECLARE_PRIVATE(ItemList)
};

}
}


#endif // ITEMLIST_H
