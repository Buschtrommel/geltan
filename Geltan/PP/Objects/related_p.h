/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * related_p.h
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

#ifndef RELATED_P_H
#define RELATED_P_H

#include "related.h"
#include "ppobjectsbase_p.h"

namespace Geltan {
namespace PP {

class RelatedPrivate : public PPObjectsBasePrivate
{
public:
    RelatedPrivate() :
        sale(nullptr),
        authorization(nullptr),
        order(nullptr),
        capture(nullptr),
        refund(nullptr)
    {}

    ~RelatedPrivate() {}

    Sale *sale;
    Authorization *authorization;
    Order *order;
    Capture *capture;
    Refund *refund;
};

}
}

#endif // RELATED_P_H
