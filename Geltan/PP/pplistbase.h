/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/pplistbase.h
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

#ifndef PPLISTBASE_H
#define PPLISTBASE_H

#include "ppbase.h"

namespace Geltan {
namespace PP {

class PPListBasePrivate;

class GELTANSHARED_EXPORT PPListBase : public PPBase
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs a new PPListBase object.
     */
    PPListBase(QObject *parent = nullptr);

protected:
    PPListBase(PPListBasePrivate &dd, QObject *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(PPListBase)
    Q_DISABLE_COPY(PPListBase)
};

}
}

#endif // PPLISTBASE_H
