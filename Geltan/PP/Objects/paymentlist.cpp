/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/paymentlist.cpp
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

#include "paymentlist_p.h"
#include "payer.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;

PaymentList::PaymentList(QObject *parent) : QAbstractListModel(parent), d_ptr(new PaymentListPrivate(this))
{

}


PaymentList::PaymentList(const QJsonDocument &json, QObject *parent) : QAbstractListModel(parent), d_ptr(new PaymentListPrivate(this))
{
    loadFromJson(json);
}



PaymentList::PaymentList(const QJsonObject &json, QObject *parent) : QAbstractListModel(parent), d_ptr(new PaymentListPrivate(this))
{
    loadFromJson(json);
}



PaymentList::~PaymentList()
{

}




QHash<int, QByteArray> PaymentList::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    roles.insert(Id, QByteArrayLiteral("id"));
    roles.insert(CreateTime, QByteArrayLiteral("createTime"));
    roles.insert(UpdateTime, QByteArrayLiteral("updateTime"));
    roles.insert(State, QByteArrayLiteral("state"));
    roles.insert(Intent, QByteArrayLiteral("intent"));
    roles.insert(Payer, QByteArrayLiteral("payer"));
    return roles;
}


int PaymentList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const PaymentList);
    return d->payments.count();
}


QModelIndex PaymentList::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}


QVariant PaymentList::data(const QModelIndex &index, int role) const
{
    Q_D(const PaymentList);

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount() - 1)) {
        return QVariant();
    }

    Payment *p = d->payments.at(index.row());

    switch (role) {
    case Item:
        return QVariant::fromValue<Payment*>(p);
    case Id:
        return QVariant::fromValue<QString>(p->id());
    case CreateTime:
        return QVariant::fromValue<QDateTime>(p->createTime());
    case UpdateTime:
        return QVariant::fromValue<QDateTime>(p->updateTime());
    case State:
        return QVariant::fromValue<Geltan::PP::Payment::State>(p->state());
    case Intent:
        return QVariant::fromValue<Geltan::PP::Payment::Intent>(p->intent());
    case Payer:
        return QVariant::fromValue(p->payer());
    default:
        return QVariant();
    }
}





QList<Payment*> PaymentList::payments() const { Q_D(const PaymentList); return d->payments; }

void PaymentList::setPayments(const QList<Payment*> &nPayments)
{
    Q_D(PaymentList);
    if (nPayments != d->payments) {
        d->payments = nPayments;
#ifdef QT_DEBUG
        qDebug() << "Changed payments to" << d->payments;
#endif
        Q_EMIT paymentsChanged(payments());
    }
}




int PaymentList::count() const { Q_D(const PaymentList); return d->count; }

void PaymentList::setCount(int nCount)
{
    Q_D(PaymentList);
    if (nCount != d->count) {
        d->count = nCount;
#ifdef QT_DEBUG
        qDebug() << "Changed count to" << d->count;
#endif
        Q_EMIT countChanged(count());
    }
}




QString PaymentList::nextId() const { Q_D(const PaymentList); return d->nextId; }

void PaymentList::setNextId(const QString &nNextId)
{
    Q_D(PaymentList);
    if (nNextId != d->nextId) {
        d->nextId = nNextId;
#ifdef QT_DEBUG
        qDebug() << "Changed nextId to" << d->nextId;
#endif
        Q_EMIT nextIdChanged(nextId());
    }
}







void PaymentList::loadFromJson(const QJsonDocument &json, bool append)
{
    loadFromJson(json.object(), append);
}



void PaymentList::loadFromJson(const QJsonObject &json, bool append)
{
    Q_D(PaymentList);

    if (!append) {
        d->clear();
    }

    if (json.isEmpty()) {
        setCount(0);
        setNextId(QString());
        return;
    }

    const QJsonArray ps = json.value(QStringLiteral("payments")).toArray();

    if (!ps.isEmpty()) {

        beginInsertRows(QModelIndex(), rowCount(), ps.count() - 1);

        for (const QJsonValue &p : ps) {
            d->payments.append(new Payment(p.toObject(), this));
        }

        endInsertRows();
    }

    Q_EMIT paymentsChanged(payments());

    setCount(json.value(QStringLiteral("count")).toInt());

    setNextId(json.value(QStringLiteral("next_id")).toString());
}
