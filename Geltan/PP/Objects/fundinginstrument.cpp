/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * payer.h
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

#include "fundinginstrument_p.h"
#include <Geltan/PP/Objects/creditcard.h>
#include <Geltan/PP/Objects/tokenizedcreditcard.h>
#include <Geltan/PP/Objects/billinginstrument.h>
#include <QJsonDocument>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


FundingInstrument::FundingInstrument(QObject *parent) :
    QObject(parent), d_ptr(new FundingInstrumentPrivate)
{
}



FundingInstrument::FundingInstrument(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new FundingInstrumentPrivate)
{
    loadFromJson(json);
}


FundingInstrument::FundingInstrument(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new FundingInstrumentPrivate)
{
    loadFromJson(json);
}



FundingInstrument::~FundingInstrument()
{
}



CreditCard *FundingInstrument::creditCard() const { Q_D(const FundingInstrument); return d->creditCard; }

void FundingInstrument::setCreditCard(CreditCard *nCreditCard)
{
    Q_D(FundingInstrument); 
    if (nCreditCard != d->creditCard) {
        d->creditCard = nCreditCard;
#ifdef QT_DEBUG
        qDebug() << "Changed creditCard to" << d->creditCard;
#endif
        Q_EMIT creditCardChanged(creditCard());
    }
}




TokenizedCreditCard *FundingInstrument::creditCardToken() const { Q_D(const FundingInstrument); return d->creditCardToken; }

void FundingInstrument::setCreditCardToken(TokenizedCreditCard *nCreditCardToken)
{
    Q_D(FundingInstrument); 
    if (nCreditCardToken != d->creditCardToken) {
        d->creditCardToken = nCreditCardToken;
#ifdef QT_DEBUG
        qDebug() << "Changed creditCardToken to" << d->creditCardToken;
#endif
        Q_EMIT creditCardTokenChanged(creditCardToken());
    }
}




BillingInstrument *FundingInstrument::billing() const { Q_D(const FundingInstrument); return d->billing; }

void FundingInstrument::setBilling(BillingInstrument *nBilling)
{
    Q_D(FundingInstrument); 
    if (nBilling != d->billing) {
        d->billing = nBilling;
#ifdef QT_DEBUG
        qDebug() << "Changed billing to" << d->billing;
#endif
        Q_EMIT billingChanged(billing());
    }
}




QVariantMap FundingInstrument::toVariant()
{
    Q_D(FundingInstrument);

    QVariantMap map;

    if (creditCard()) {
        d->addMapToVariantMap(&map, QStringLiteral("credit_card"), creditCard()->toVariant());
    }

    if (creditCardToken()) {
        d->addMapToVariantMap(&map, QStringLiteral("credit_card_token"), creditCardToken()->toVariant());
    }

    if (billing()) {
        d->addMapToVariantMap(&map, QStringLiteral("billing"), billing()->toVariant());
    }

    return map;
}


QJsonObject FundingInstrument::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}


void FundingInstrument::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void FundingInstrument::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }


    const QJsonObject cco = json.value(QStringLiteral("credit_card")).toObject();
    CreditCard *oldCreditCard = creditCard();
    if (!cco.isEmpty()) {
        if (oldCreditCard) {
            oldCreditCard->loadFromJson(cco);
        } else {
            setCreditCard(new CreditCard(cco, this));
        }
    } else {
        setCreditCard(nullptr);
        delete oldCreditCard;
    }


    const QJsonObject ccto = json.value(QStringLiteral("credit_card_token")).toObject();
    TokenizedCreditCard *oldCreditCardToken = creditCardToken();
    if (!ccto.isEmpty()) {
        if (oldCreditCardToken) {
            oldCreditCardToken->loadFromJson(ccto);
        } else {
            setCreditCardToken(new TokenizedCreditCard(ccto, this));
        }
    } else {
        setCreditCardToken(nullptr);
        delete oldCreditCardToken;
    }


    const QJsonObject bo = json.value(QStringLiteral("billing")).toObject();
    BillingInstrument *oldBilling = billing();
    if (!bo.isEmpty()) {
        if (oldBilling) {
            oldBilling->loadFromJson(bo);
        } else {
            setBilling(new BillingInstrument(bo, this));
        }
    } else {
        setBilling(nullptr);
        delete oldBilling;
    }
}
