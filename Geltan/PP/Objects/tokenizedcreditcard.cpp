/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/tokenizedcreditcard.cpp
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

#include "tokenizedcreditcard_p.h"
#include <QJsonDocument>
#include <Geltan/PP/ppenumsmap.h>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


TokenizedCreditCard::TokenizedCreditCard(QObject *parent) :
    QObject(parent), d_ptr(new TokenizedCreditCardPrivate(this))
{
}


TokenizedCreditCard::TokenizedCreditCard(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new TokenizedCreditCardPrivate(this))
{
    loadFromJson(json);
}


TokenizedCreditCard::TokenizedCreditCard(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new TokenizedCreditCardPrivate(this))
{
    loadFromJson(json);
}


TokenizedCreditCard::~TokenizedCreditCard()
{

}


QString TokenizedCreditCard::creditCardId() const { Q_D(const TokenizedCreditCard); return d->creditCardId; }

void TokenizedCreditCard::setCreditCardId(const QString &nCreditCardId)
{
    Q_D(TokenizedCreditCard); 
    if (nCreditCardId != d->creditCardId) {
        d->creditCardId = nCreditCardId;
#ifdef QT_DEBUG
        qDebug() << "Changed creditCardId to" << d->creditCardId;
#endif
        Q_EMIT creditCardIdChanged(creditCardId());
    }
}




QString TokenizedCreditCard::payerId() const { Q_D(const TokenizedCreditCard); return d->payerId; }

void TokenizedCreditCard::setPayerId(const QString &nPayerId)
{
    Q_D(TokenizedCreditCard); 
    if (nPayerId != d->payerId) {
        d->payerId = nPayerId;
#ifdef QT_DEBUG
        qDebug() << "Changed payerId to" << d->payerId;
#endif
        Q_EMIT payerIdChanged(payerId());
    }
}




QString TokenizedCreditCard::last4() const { Q_D(const TokenizedCreditCard); return d->last4; }






PayPal::CreditCardType TokenizedCreditCard::type() const { Q_D(const TokenizedCreditCard); return d->type; }






quint8 TokenizedCreditCard::expireMonth() const { Q_D(const TokenizedCreditCard); return d->expireMonth; }






quint16 TokenizedCreditCard::expireYear() const { Q_D(const TokenizedCreditCard); return d->expireYear; }






QVariantMap TokenizedCreditCard::toVariant()
{
    Q_D(TokenizedCreditCard);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("credit_card_id"), creditCardId());
    d->addStringToVariantMap(&map, QStringLiteral("payer_id"), payerId());

    return map;
}



QJsonObject TokenizedCreditCard::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void TokenizedCreditCard::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void TokenizedCreditCard::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(TokenizedCreditCard);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    setCreditCardId(json.value(QStringLiteral("credit_card_id")).toString());

    setPayerId(json.value(QStringLiteral("payer_id")).toString());

    d->setLast4(json.value(QStringLiteral("last4")).toString());

    d->setType(em->creditCardTypeTokenToEnum(json.value(QStringLiteral("type")).toString()));

    d->setExpireMonth(json.value(QStringLiteral("expire_month")).toString().toUInt());

    d->setExpireYear(json.value(QStringLiteral("expire_year")).toString().toUInt());
}
