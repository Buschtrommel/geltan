/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/list.h
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

#include "list_p.h"
#include <QUrlQuery>

using namespace Geltan;
using namespace PP;
using namespace Payments;

List::List(QObject *parent) : PPBase(*new ListPrivate, parent)
{
    Q_D(List);
    d->count = 0;
    d->startIndex = 0;
    d->sortBy = QStringLiteral("update_time");
    d->sortOrder = Qt::AscendingOrder;
    d->paymentList = nullptr;
    setApiPath(QStringLiteral("/v1/payments/payment"));
    setNetworkOperation(QNetworkAccessManager::GetOperation);
    setExpectedType(PPBase::Object);
    addRequestHeader(QByteArrayLiteral("Content-Type"), QByteArrayLiteral("application/json"));
}



List::List(ListPrivate &dd, QObject *parent) : PPBase(dd, parent)
{

}




void List::call()
{
    setError(nullptr);
    setInOperation(true);
    setAuthentication();

    QUrlQuery uq;

    if (count() > 0) {
        uq.addQueryItem(QStringLiteral("count"), QString::number(count()));
    }

    if (!startId().isEmpty()) {
        uq.addQueryItem(QStringLiteral("start_id"), startId());
    }

    if (startIndex() > -1) {
        uq.addQueryItem(QStringLiteral("start_index"), QString::number(startIndex()));
    }

    if (startTime().isValid()) {
        uq.addQueryItem(QStringLiteral("start_time"), startTime().toUTC().toString(Qt::ISODate));
    }

    if (endTime().isValid()) {
        uq.addQueryItem(QStringLiteral("end_time"), endTime().toUTC().toString(Qt::ISODate));
    }

    if (!sortBy().isEmpty()) {
        uq.addQueryItem(QStringLiteral("sort_by"), sortBy());

        if (sortOrder() == Qt::AscendingOrder) {
            uq.addQueryItem(QStringLiteral("sort_order"), QStringLiteral("asc"));
        } else {
            uq.addQueryItem(QStringLiteral("sort_order"), QStringLiteral("desc"));
        }
    }

    setUrlQuery(uq);

    sendRequest();
}




void List::call(int count, const QString &startId, int startIndex, const QDateTime &startTime, const QDateTime &endTime, const QString &sortBy, Qt::SortOrder sortOrder)
{
    setCount(count);
    setStartId(startId);
    setStartIndex(startIndex);
    setStartTime(startTime);
    setEndTime(endTime);
    setSortBy(sortBy);
    setSortOrder(sortOrder);

    call();
}




void List::successCallBack()
{
    Q_D(List);

    if (d->paymentList) {
        d->paymentList->loadFromJson(jsonResult());
    } else {
        d->paymentList = new PaymentList(jsonResult(), this);
        Q_EMIT paymentListChanged(d->paymentList);
    }

    setInOperation(false);
    Q_EMIT succeeded();
}



void List::errorCallBack()
{
    setInOperation(false);
    Q_EMIT failed();
}



bool List::checkInput()
{
    if (startTime().isValid() && endTime().isValid()) {
        if (startTime() > endTime()) {
            setError(new Error(Error::InputError, tr("The end time has to be later than the start time."), Error::Critical, QString(), this));
            return false;
        }
    }
    return true;
}



bool List::checkOutput()
{
    if (PPBase::checkOutput()) {
        return true;
    } else {
        return false;
    }
}




int List::count() const { Q_D(const List); return d->count; }

void List::setCount(int nCount)
{
    Q_D(List);
    if (nCount != d->count) {
        d->count = nCount;
#ifdef QT_DEBUG
        qDebug() << "Changed count to" << d->count;
#endif
        Q_EMIT countChanged(count());
    }
}




QString List::startId() const { Q_D(const List); return d->startId; }

void List::setStartId(const QString &nStartId)
{
    Q_D(List);
    if (nStartId != d->startId) {
        d->startId = nStartId;
#ifdef QT_DEBUG
        qDebug() << "Changed startId to" << d->startId;
#endif
        Q_EMIT startIdChanged(startId());
    }
}




int List::startIndex() const { Q_D(const List); return d->startIndex; }

void List::setStartIndex(int nStartIndex)
{
    Q_D(List);
    if (nStartIndex != d->startIndex) {
        d->startIndex = nStartIndex;
#ifdef QT_DEBUG
        qDebug() << "Changed startIndex to" << d->startIndex;
#endif
        Q_EMIT startIndexChanged(startIndex());
    }
}




QDateTime List::startTime() const { Q_D(const List); return d->startTime; }

void List::setStartTime(const QDateTime &nStartTime)
{
    Q_D(List);
    if (nStartTime != d->startTime) {
        d->startTime = nStartTime;
#ifdef QT_DEBUG
        qDebug() << "Changed startTime to" << d->startTime;
#endif
        Q_EMIT startTimeChanged(startTime());
    }
}




QDateTime List::endTime() const { Q_D(const List); return d->endTime; }

void List::setEndTime(const QDateTime &nEndTime)
{
    Q_D(List);
    if (nEndTime != d->endTime) {
        d->endTime = nEndTime;
#ifdef QT_DEBUG
        qDebug() << "Changed endTime to" << d->endTime;
#endif
        Q_EMIT endTimeChanged(endTime());
    }
}




QString List::sortBy() const { Q_D(const List); return d->sortBy; }

void List::setSortBy(const QString &nSortBy)
{
    Q_D(List);
    if (nSortBy != d->sortBy) {
        d->sortBy = nSortBy;
#ifdef QT_DEBUG
        qDebug() << "Changed sortBy to" << d->sortBy;
#endif
        Q_EMIT sortByChanged(sortBy());
    }
}




Qt::SortOrder List::sortOrder() const { Q_D(const List); return d->sortOrder; }

void List::setSortOrder(const Qt::SortOrder &nSortOrder)
{
    Q_D(List);
    if (nSortOrder != d->sortOrder) {
        d->sortOrder = nSortOrder;
#ifdef QT_DEBUG
        qDebug() << "Changed sortOrder to" << d->sortOrder;
#endif
        Q_EMIT sortOrderChanged(sortOrder());
    }
}



PaymentList *List::paymentList() const { Q_D(const List); return d->paymentList; }
