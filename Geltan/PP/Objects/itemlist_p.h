/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * itemlist_p.h
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

#ifndef ITEMLIST_P_H
#define ITEMLIST_P_H

#include "itemlist.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class ItemListPrivate : public PPObjectsBasePrivate
{
public:
    ItemListPrivate(ItemList *parent) :
        q_ptr(parent),
        shippingAddress(nullptr)
    {}

    ~ItemListPrivate() {}

    void clear() {

        if (!items.isEmpty()) {

            Q_Q(ItemList);

            q->beginRemoveRows(QModelIndex(), 0, items.count() - 1);

            qDeleteAll(items);
            items.clear();

            q->endRemoveRows();
        }
    }

    ItemList * const q_ptr;
    Q_DECLARE_PUBLIC(ItemList)
    QList<Item*> items;
    ShippingAddress *shippingAddress;
    QString shippingMethod;
    QString shippingPhoneNumber;
};

}
}

#endif // ITEMLIST_P_H
