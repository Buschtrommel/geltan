/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * error_p.h
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

#ifndef ERROR_P_H
#define ERROR_P_H

#include "error.h"

namespace Geltan {

class ErrorPrivate
{
public:
    QString text = QString();
    Error::ErrorType type = Error::NoError;
    QString data = QString();
    Error::ErrorSeverity severity = Error::Nothing;

    void printOut()
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)

        switch(severity) {
        case Error::Warning:
            qWarning("%s", qUtf8Printable(text));
            break;
        case Error::Critical:
            qCritical("%s", qUtf8Printable(text));
            break;
        case Error::Fatal:
            qFatal("%s", qUtf8Printable(text));
            break;
        case Error::Nothing:
        default:
            break;
        }

        if (!data.isEmpty()) {
            qDebug("%s", qUtf8Printable(data));
        }

#else

        switch(severity) {
        case Error::Warning:
            qWarning("%s", qPrintable(text));
            break;
        case Error::Critical:
            qCritical("%s", qPrintable(text));
            break;
        case Error::Fatal:
            qFatal("%s", qPrintable(text));
            break;
        case Error::Nothing:
        default:
            break;
        }

        if (!data.isEmpty()) {
            qDebug(qPrintable(data));
        }

#endif
    }

};

}


#endif // ERROR_P_H
