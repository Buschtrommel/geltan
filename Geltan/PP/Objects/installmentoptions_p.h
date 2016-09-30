/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * installmentoptions_p.h
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

#ifndef INSTALLMENTOPTIONS_P_H
#define INSTALLMENTOPTIONS_P_H

#include "installmentoptions.h"

namespace Geltan {
namespace PP {

class InstallmentOptionsPrivate
{
public:
    InstallmentOptionsPrivate(InstallmentOptions *parent) :
        q_ptr(parent),
        network(PayPal::NoCreditCardType)
    {}

    ~InstallmentOptionsPrivate() {}

    void clear()
    {
        if (!installmentOptions.isEmpty()) {
            Q_Q(InstallmentOptions);

            q->beginRemoveRows(QModelIndex(), 0, installmentOptions.count() - 1);

            qDeleteAll(installmentOptions);
            installmentOptions.clear();

            q->endRemoveRows();
        }
    }

    InstallmentOptions * const q_ptr;
    Q_DECLARE_PUBLIC(InstallmentOptions)
    QString installmentId;
    PayPal::CreditCardType network;
    QString issuer;
    QList<InstallmentDescription*> installmentOptions;
};

}
}

#endif // INSTALLMENTOPTIONS_P_H
