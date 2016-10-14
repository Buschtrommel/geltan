/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/tokenizedcreditcard_p.h
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

#ifndef TOKENIZEDCREDITCARD_P_H
#define TOKENIZEDCREDITCARD_P_H

#include "tokenizedcreditcard.h"
#include "ppobjectsbase_p.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {

class TokenizedCreditCardPrivate : public PPObjectsBasePrivate
{
public:
    TokenizedCreditCardPrivate(TokenizedCreditCard *parent) :
        q_ptr(parent),
        type(PayPal::NoCreditCardType),
        expireMonth(0),
        expireYear(0)
    {}

    ~TokenizedCreditCardPrivate() {}


    void setLast4(const QString &nLast4)
    {
        if (nLast4 != last4) {
            Q_Q(TokenizedCreditCard);
            last4 = nLast4;
    #ifdef QT_DEBUG
            qDebug() << "Changed last4 to" << last4;
    #endif
            Q_EMIT q->last4Changed(last4);
        }
    }


    void setType(PayPal::CreditCardType nType)
    {
        if (nType != type) {
            Q_Q(TokenizedCreditCard);
            type = nType;
    #ifdef QT_DEBUG
            qDebug() << "Changed type to" << type;
    #endif
            Q_EMIT q->typeChanged(type);
        }
    }


    void setExpireMonth(quint8 nExpireMonth)
    {
        if (nExpireMonth != expireMonth) {
            Q_Q(TokenizedCreditCard);
            expireMonth = nExpireMonth;
    #ifdef QT_DEBUG
            qDebug() << "Changed expireMonth to" << expireMonth;
    #endif
            Q_EMIT q->expireMonthChanged(expireMonth);
        }
    }


    void setExpireYear(quint16 nExpireYear)
    {
        if (nExpireYear != expireYear) {
            Q_Q(TokenizedCreditCard);
            expireYear = nExpireYear;
    #ifdef QT_DEBUG
            qDebug() << "Changed expireYear to" << expireYear;
    #endif
            Q_EMIT q->expireYearChanged(expireYear);
        }
    }


    TokenizedCreditCard * const q_ptr;
    Q_DECLARE_PUBLIC(TokenizedCreditCard)
    QString creditCardId;
    QString payerId;
    QString last4;
    PayPal::CreditCardType type;
    quint8 expireMonth;
    quint16 expireYear;
};

}
}

#endif // TOKENIZEDCREDITCARD_P_H
