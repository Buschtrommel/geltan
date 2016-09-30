/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * refund_p.h
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

#include "refund_p.h"
#include <Geltan/PP/Objects/paymentamount.h>
#include <Geltan/PP/Objects/link.h>
#include <Geltan/PP/ppenumsmap.h>
#include <QJsonDocument>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Refund::Refund(QObject *parent) :
    QObject(parent), d_ptr(new RefundPrivate)
{
}



Refund::Refund(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new RefundPrivate)
{
    loadFromJson(json);
}



Refund::Refund(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new RefundPrivate)
{
    loadFromJson(json);
}




Refund::~Refund()
{
}


QString Refund::id() const { Q_D(const Refund); return d->id; }

void Refund::setId(const QString &nId)
{
    Q_D(Refund); 
    if (nId != d->id) {
        d->id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << d->id;
#endif
        Q_EMIT idChanged(id());
    }
}




PaymentAmount *Refund::amount() const { Q_D(const Refund); return d->amount; }

void Refund::setAmount(PaymentAmount *nAmount)
{
    Q_D(Refund); 
    if (nAmount != d->amount) {
        d->amount = nAmount;
#ifdef QT_DEBUG
        qDebug() << "Changed amount to" << d->amount;
#endif
        Q_EMIT amountChanged(amount());
    }
}




PayPal::StateType Refund::state() const { Q_D(const Refund); return d->state; }

void Refund::setState(PayPal::StateType nState)
{
    Q_D(Refund); 
    if (nState != d->state) {
        d->state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << d->state;
#endif
        Q_EMIT stateChanged(state());
    }
}




QString Refund::reason() const { Q_D(const Refund); return d->reason; }

void Refund::setReason(const QString &nReason)
{
    Q_D(Refund); 
    if (nReason != d->reason) {
        d->reason = nReason;
#ifdef QT_DEBUG
        qDebug() << "Changed reason to" << d->reason;
#endif
        Q_EMIT reasonChanged(reason());
    }
}




QString Refund::saleId() const { Q_D(const Refund); return d->saleId; }

void Refund::setSaleId(const QString &nSaleId)
{
    Q_D(Refund); 
    if (nSaleId != d->saleId) {
        d->saleId = nSaleId;
#ifdef QT_DEBUG
        qDebug() << "Changed saleId to" << d->saleId;
#endif
        Q_EMIT saleIdChanged(saleId());
    }
}




QString Refund::captureId() const { Q_D(const Refund); return d->captureId; }

void Refund::setCaptureId(const QString &nCaptureId)
{
    Q_D(Refund); 
    if (nCaptureId != d->captureId) {
        d->captureId = nCaptureId;
#ifdef QT_DEBUG
        qDebug() << "Changed captureId to" << d->captureId;
#endif
        Q_EMIT captureIdChanged(captureId());
    }
}




QString Refund::parentPayment() const { Q_D(const Refund); return d->parentPayment; }

void Refund::setParentPayment(const QString &nParentPayment)
{
    Q_D(Refund); 
    if (nParentPayment != d->parentPayment) {
        d->parentPayment = nParentPayment;
#ifdef QT_DEBUG
        qDebug() << "Changed parentPayment to" << d->parentPayment;
#endif
        Q_EMIT parentPaymentChanged(parentPayment());
    }
}




QString Refund::description() const { Q_D(const Refund); return d->description; }

void Refund::setDescription(const QString &nDescription)
{
    Q_D(Refund); 
    if (nDescription != d->description) {
        d->description = nDescription;
#ifdef QT_DEBUG
        qDebug() << "Changed description to" << d->description;
#endif
        Q_EMIT descriptionChanged(description());
    }
}




QDateTime Refund::createTime() const { Q_D(const Refund); return d->createTime; }

void Refund::setCreateTime(const QDateTime &nCreateTime)
{
    Q_D(Refund); 
    if (nCreateTime != d->createTime) {
        d->createTime = nCreateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed createTime to" << d->createTime;
#endif
        Q_EMIT createTimeChanged(createTime());
    }
}




QDateTime Refund::updateTime() const { Q_D(const Refund); return d->updateTime; }

void Refund::setUpdateTime(const QDateTime &nUpdateTime)
{
    Q_D(Refund); 
    if (nUpdateTime != d->updateTime) {
        d->updateTime = nUpdateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed updateTime to" << d->updateTime;
#endif
        Q_EMIT updateTimeChanged(updateTime());
    }
}




PayPal::ReasonCode Refund::reasonCode() const { Q_D(const Refund); return d->reasonCode; }

void Refund::setReasonCode(PayPal::ReasonCode nReasonCode)
{
    Q_D(Refund); 
    if (nReasonCode != d->reasonCode) {
        d->reasonCode = nReasonCode;
#ifdef QT_DEBUG
        qDebug() << "Changed reasonCode to" << d->reasonCode;
#endif
        Q_EMIT reasonCodeChanged(reasonCode());
    }
}




QList<Link*> Refund::links() const { Q_D(const Refund); return d->links; }

void Refund::setLinks(const QList<Link*> &nLinks)
{
    Q_D(Refund); 
    if (nLinks != d->links) {
        d->links = nLinks;
#ifdef QT_DEBUG
        qDebug() << "Changed links to" << d->links;
#endif
        Q_EMIT linksChanged(links());
    }
}



QUrl Refund::getLinkURL(const QString &rel) const
{
    const Link *l = getLink(rel);
    if (l) {
        return l->href();
    } else {
        return QUrl();
    }
}



Link* Refund::getLink(const QString &rel) const
{
    Q_D(const Refund);

    if (d->links.isEmpty()) {
        return nullptr;
    }

    for (Link *l : d->links) {
        if (l->rel() == rel) {
            return l;
        }
    }

    return nullptr;
}



QVariantMap Refund::toVariant()
{
    Q_D(Refund);

    QVariantMap map;

    if (amount()) {
        d->addMapToVariantMap(&map, QStringLiteral("amount"), amount()->toVariant());
    }

    d->addStringToVariantMap(&map, QStringLiteral("reason"), reason());
    d->addStringToVariantMap(&map, QStringLiteral("description"), description());

    return map;
}



QJsonObject Refund::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}


void Refund::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void Refund::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Refund);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    setId(json.value(QStringLiteral("id")).toString());

    const QJsonObject ao = json.value(QStringLiteral("amount")).toObject();
    PaymentAmount *oldAo = amount();
    if (!ao.isEmpty()) {
        if (oldAo) {
            oldAo->loadFromJson(ao);
        } else {
            setAmount(new PaymentAmount(ao, this));
        }
    } else {
        setAmount(nullptr);
        delete oldAo;
    }


    setState(em->stateTypeTokenToEnum(json.value(QStringLiteral("state")).toString()));

    setReason(json.value(QStringLiteral("reason")).toString());

    setSaleId(json.value(QStringLiteral("sale_id")).toString());

    setCaptureId(json.value(QStringLiteral("capture_id")).toString());

    setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    setDescription(json.value(QStringLiteral("description")).toString());

    const QString ct = json.value(QStringLiteral("create_time")).toString();
    if (!ct.isEmpty()) {
        setCreateTime(QDateTime::fromString(ct, Qt::ISODate));
    } else {
        setCreateTime(QDateTime());
    }

    const QString ut = json.value(QStringLiteral("update_time")).toString();
    if (!ut.isEmpty()) {
        setUpdateTime(QDateTime::fromString(ut, Qt::ISODate));
    } else {
        setUpdateTime(QDateTime());
    }

    setReasonCode(em->reasonCodeTokenToEnum(json.value(QStringLiteral("reason_code")).toString()));

    const QJsonArray la = json.value(QStringLiteral("links")).toArray();
    d->clearLinks();
    Q_EMIT linksChanged(links());
    if (!la.isEmpty()) {
        QList<Link*> linksToAdd;
        QJsonArray::const_iterator i = la.constBegin();
        while (i != la.constEnd()) {
            linksToAdd.append(new Link(i->toObject()));
            ++i;
        }
        setLinks(linksToAdd);
    }
}
