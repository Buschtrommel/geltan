/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/ppobjectsbase_p.h
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

#ifndef PPOBJECTSBASE_P_H
#define PPOBJECTSBASE_P_H

#include <QString>
#include <QVariantMap>
#include <QVariantList>
#include <QRegularExpression>

namespace Geltan {
namespace PP {

class PPObjectsBasePrivate
{
public:
    PPObjectsBasePrivate() {}

    ~PPObjectsBasePrivate() {}


    QString checkString(const QString &s, int maxLength = 0) {
        if (maxLength > 0 && s.size() > maxLength) {
            QString _s = s;
            _s.truncate(maxLength);
            return _s;
        } else {
            return s;
        }
    }

    void addStringToVariantMap(QVariantMap *map, const QString &key, const QString &value, int maxLength = 0) {
        if (!map || key.isEmpty() || value.isEmpty()) {
            return;
        }

        map->insert(key, checkString(value, maxLength));
    }

    void addFloatToVariantMap(QVariantMap *map, const QString &key, float value, int maxLength = 10, int maxDecPlaces = 2) {
        if (!map || key.isEmpty() || value == 0.0f) {
            return;
        }

        if (maxDecPlaces > -1) {
            QString n = QString::number(value, 'f', maxDecPlaces);
            if (n.size() <= maxLength) {
                map->insert(key, n.toDouble());
            }
        } else {
            map->insert(key, value);
        }
    }

    void addDoubleToVariantMap(QVariantMap *map, const QString &key, double value, int maxLength = 10, int maxDecPlaces = 2) {
        if (!map || key.isEmpty()) {
            return;
        }

        if (maxDecPlaces > -1) {
            QString n = QString::number(value, 'f', maxDecPlaces);
            if (n.size() <= maxLength) {
                map->insert(key, n.toDouble());
            }
        } else {
            map->insert(key, value);
        }
    }

    void addIntToVariantMap(QVariantMap *map, const QString &key, int value, int omitValue = 0)
    {
        if (!map || key.isEmpty() || value == omitValue) {
            return;
        }

        map->insert(key, value);
    }

    void addMapToVariantMap(QVariantMap *map, const QString &key, const QVariantMap &vMap) {
        if (!map || key.isEmpty() || vMap.isEmpty()) {
            return;
        }

        map->insert(key, vMap);
    }


    void addListToVariantMap(QVariantMap *map, const QString &key, const QVariantList &list) {
        if (!map || key.isEmpty() || list.isEmpty()) {
            return;
        }

        map->insert(key, list);
    }


    void addPhoneNumberToVariantMap(QVariantMap *map, const QString &key, const QString &number) {
        if (!map || key.isEmpty() || number.isEmpty()) {
            return;
        }

        QString n = number.simplified();
        n.remove(QRegularExpression(QStringLiteral("[^0-9+\\s]")));

        map->insert(key, n);

    }


};

}
}

#endif // PPOBJECTSBASE_P_H
