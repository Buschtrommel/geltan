/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * item_p.h
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

#ifndef ITEM_P_H
#define ITEM_P_H

#include "item.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {


class ItemPrivate : public PPObjectsBasePrivate
{
public:
    ItemPrivate() :
        quantity(0),
        price(0.0),
        tax(0.0)
    {}

    ItemPrivate(ItemPrivate *other) {
        sku = other->sku;
        name = other->name;
        description = other->description;
        quantity = other->quantity;
        price = other->price;
        currency = other->currency;
        tax = other->tax;
        url = other->url;
    }

    ~ItemPrivate() {}

    QString sku;
    QString name;
    QString description;
    int quantity;
    float price;
    QString currency;
    float tax;
    QUrl url;
};

}
}

#endif // ITEM_P_H
