/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/geltan_global.h
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

#ifndef GELTAN_GLOBAL_H
#define GELTAN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GELTAN_LIBRARY)
#  define GELTANSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GELTANSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GELTAN_GLOBAL_H
