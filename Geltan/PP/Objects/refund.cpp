/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/refund_p.h
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
    QObject(parent), d_ptr(new RefundPrivate(this))
{
}



Refund::Refund(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new RefundPrivate(this))
{
    loadFromJson(json);
}



Refund::Refund(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new RefundPrivate(this))
{
    loadFromJson(json);
}




Refund::~Refund()
{
}


QString Refund::id() const { Q_D(const Refund); return d->id; }






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



QString Refund::invoiceNumber() const { Q_D(const Refund); return d->invoiceNumber; }

void Refund::setInvoiceNumber(const QString &nInvoiceNumber)
{
    Q_D(Refund);
    if (nInvoiceNumber != d->invoiceNumber) {
        d->invoiceNumber = nInvoiceNumber;
#ifdef QT_DEBUG
        qDebug() << "Changed invoiceNumber to" << d->invoiceNumber;
#endif
        Q_EMIT invoiceNumberChanged(invoiceNumber());
    }
}




QString Refund::saleId() const { Q_D(const Refund); return d->saleId; }






QString Refund::captureId() const { Q_D(const Refund); return d->captureId; }






QString Refund::parentPayment() const { Q_D(const Refund); return d->parentPayment; }






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






QDateTime Refund::updateTime() const { Q_D(const Refund); return d->updateTime; }






PayPal::ReasonCode Refund::reasonCode() const { Q_D(const Refund); return d->reasonCode; }






QList<Link*> Refund::links() const { Q_D(const Refund); return d->links; }





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
    d->addStringToVariantMap(&map, QStringLiteral("invoice_number"), invoiceNumber(), 127);
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

    d->setId(json.value(QStringLiteral("id")).toString());

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


    d->setState(em->stateTypeTokenToEnum(json.value(QStringLiteral("state")).toString()));

    setReason(json.value(QStringLiteral("reason")).toString());

    d->setSaleId(json.value(QStringLiteral("sale_id")).toString());

    d->setCaptureId(json.value(QStringLiteral("capture_id")).toString());

    d->setParentPayment(json.value(QStringLiteral("parent_payment")).toString());

    setDescription(json.value(QStringLiteral("description")).toString());

    const QString ct = json.value(QStringLiteral("create_time")).toString();
    if (!ct.isEmpty()) {
        d->setCreateTime(QDateTime::fromString(ct, Qt::ISODate));
    } else {
        d->setCreateTime(QDateTime());
    }

    const QString ut = json.value(QStringLiteral("update_time")).toString();
    if (!ut.isEmpty()) {
        d->setUpdateTime(QDateTime::fromString(ut, Qt::ISODate));
    } else {
        d->setUpdateTime(QDateTime());
    }

    d->setReasonCode(em->reasonCodeTokenToEnum(json.value(QStringLiteral("reason_code")).toString()));

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
        d->setLinks(linksToAdd);
    }
}
