/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/itemlist.cpp
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

#include "itemlist_p.h"
#include <Geltan/PP/Objects/item.h>
#include <Geltan/PP/Objects/shippingaddress.h>
#include <QJsonDocument>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


ItemList::ItemList(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new ItemListPrivate(this))
{
}



ItemList::ItemList(const QJsonDocument &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new ItemListPrivate(this))
{
    loadFromJson(json);
}


ItemList::ItemList(const QJsonObject &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new ItemListPrivate(this))
{
    loadFromJson(json);
}



ItemList::~ItemList()
{

}



QHash<int, QByteArray> ItemList::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(ItemRole, QByteArrayLiteral("item"));
    return roles;
}



int ItemList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const ItemList);
    return d->items.count();
}



QModelIndex ItemList::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}



QVariant ItemList::data(const QModelIndex &index, int role) const
{
    Q_D(const ItemList);

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (d->items.count() - 1)) {
        return QVariant();
    }

    if (role == ItemRole) {
        return QVariant::fromValue<Item*>(d->items.at(index.row()));
    } else {
        return QVariant();
    }
}



QList<Item*> ItemList::items() const { Q_D(const ItemList); return d->items; }

void ItemList::setItems(const QList<Item*> &nItems)
{
    Q_D(ItemList); 
    if (nItems != d->items) {
        d->items = nItems;
#ifdef QT_DEBUG
        qDebug() << "Changed items to" << d->items;
#endif
        Q_EMIT itemsChanged(items());
    }
}




ShippingAddress *ItemList::shippingAddress() const { Q_D(const ItemList); return d->shippingAddress; }

void ItemList::setShippingAddress(ShippingAddress *nShippingAddress)
{
    Q_D(ItemList); 
    if (nShippingAddress != d->shippingAddress) {
        d->shippingAddress = nShippingAddress;
#ifdef QT_DEBUG
        qDebug() << "Changed shippingAddress to" << d->shippingAddress;
#endif
        Q_EMIT shippingAddressChanged(shippingAddress());
    }
}




QString ItemList::shippingMethod() const { Q_D(const ItemList); return d->shippingMethod; }

void ItemList::setShippingMethod(const QString &nShippingMethod)
{
    Q_D(ItemList); 
    if (nShippingMethod != d->shippingMethod) {
        d->shippingMethod = nShippingMethod;
#ifdef QT_DEBUG
        qDebug() << "Changed shippingMethod to" << d->shippingMethod;
#endif
        Q_EMIT shippingMethodChanged(shippingMethod());
    }
}




QString ItemList::shippingPhoneNumber() const { Q_D(const ItemList); return d->shippingPhoneNumber; }

void ItemList::setShippingPhoneNumber(const QString &nShippingPhoneNumber)
{
    Q_D(ItemList); 
    if (nShippingPhoneNumber != d->shippingPhoneNumber) {
        d->shippingPhoneNumber = nShippingPhoneNumber;
#ifdef QT_DEBUG
        qDebug() << "Changed shippingPhoneNumber to" << d->shippingPhoneNumber;
#endif
        Q_EMIT shippingPhoneNumberChanged(shippingPhoneNumber());
    }
}




bool ItemList::addItem(Item *i)
{
    Q_D(ItemList);

    if (i) {

        if (i->thread() != this->thread()) {
            i->moveToThread(this->thread());
            if (i->thread() != this->thread()) {
                qCritical("Failed to move item to the model's thread");
                return false;
            }
        }

        i->setParent(this);

        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        d->items.append(i);

        endInsertRows();

        return true;

    } else {

        return false;

    }
}



Geltan::PP::Item *ItemList::addNewItem()
{
    Q_D(ItemList);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    Item *i = new Item(this);

    d->items.append(i);

    endInsertRows();

    return i;
}



void ItemList::removeItem(int idx)
{
    Q_D(ItemList);

    if (!d->items.isEmpty() && idx > -1 && idx < rowCount()) {

        beginRemoveRows(QModelIndex(), idx, idx);

        delete d->items.takeAt(idx);

        endRemoveRows();
    }
}


void ItemList::removeItem(Item *i)
{
    Q_D(const ItemList);

    if (i) {
        removeItem(d->items.indexOf(i));
    }
}




Item *ItemList::takeItem(int idx)
{
    Q_D(ItemList);

    if (!d->items.isEmpty() && idx > -1 && idx < rowCount()) {

        return d->items.takeAt(idx);

    } else {
        return nullptr;
    }
}



Item *ItemList::takeItem(Item *i)
{
    return takeItem(items().indexOf(i));
}



QVariantMap ItemList::toVariant()
{
    Q_D(ItemList);

    QVariantMap map;

    if (!items().isEmpty()) {
        QVariantList list;
        const auto its = items();
        for (Item *it : its) {
            list.append(it->toVariant());
        }
        d->addListToVariantMap(&map, QStringLiteral("items"), list);
    }

    if (shippingAddress()) {
        d->addMapToVariantMap(&map, QStringLiteral("shipping_address"), shippingAddress()->toVariant());
    }
    d->addStringToVariantMap(&map, QStringLiteral("shipping_method"), shippingMethod());
    d->addPhoneNumberToVariantMap(&map, QStringLiteral("shipping_phone_number"), shippingPhoneNumber());

    return map;
}



QJsonObject ItemList::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void ItemList::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void ItemList::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(ItemList);

    const QJsonArray is = json.value(QStringLiteral("items")).toArray();
    d->clear();
    if (!is.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, is.count() - 1);
        QJsonArray::const_iterator i = is.constBegin();
        while (i != is.constEnd()) {
            d->items.append(new Item(i->toObject(), this));
            ++i;
        }
        endInsertRows();
    }

    const QJsonObject sao = json.value(QStringLiteral("shipping_address")).toObject();
    ShippingAddress *oldSao = shippingAddress();
    if (!sao.isEmpty()) {
        if (oldSao) {
            oldSao->loadFromJson(sao);
        } else {
            setShippingAddress(new ShippingAddress(sao, this));
        }
    } else {
        setShippingAddress(nullptr);
        delete oldSao;
    }

    setShippingMethod(json.value(QStringLiteral("shipping_method")).toString());

    setShippingPhoneNumber(json.value(QStringLiteral("shipping_phone_number")).toString());
}
