/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * address.h
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

#include "payment_p.h"
#include <Geltan/PP/Objects/payer.h>
#include <Geltan/PP/Objects/transaction.h>
#include <Geltan/PP/Objects/redirecturls.h>
#include <Geltan/PP/Objects/link.h>
#include <Geltan/PP/Objects/paymentamount.h>
#include <QJsonArray>

#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Payment::Payment(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new PaymentPrivate(this))
{
}



Payment::Payment(const QJsonDocument &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new PaymentPrivate(this))
{
    loadFromJson(json);
}



Payment::Payment(const QJsonObject &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new PaymentPrivate(this))
{
    loadFromJson(json);
}



Payment::~Payment()
{
}




QHash<int, QByteArray> Payment::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    roles.insert(Amount, QByteArrayLiteral("amount"));
    roles.insert(Description, QByteArrayLiteral("description"));
    return roles;
}



int Payment::rowCount(const QModelIndex &parent) const
{
    Q_D(const Payment);
    Q_UNUSED(parent)
    return d->transactions.count();
}



QModelIndex Payment::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}




QVariant Payment::data(const QModelIndex &index, int role) const
{
    Q_D(const Payment);

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount() - 1)) {
        return QVariant();
    }

    Transaction *t = d->transactions.at(index.row());

    switch (role) {
    case Item:
        return QVariant::fromValue<Transaction*>(t);
    case Amount:
        return QVariant::fromValue<PaymentAmount*>(t->amount());
    case Description:
        return QVariant::fromValue(t->description());
    default:
        return QVariant();
    }
}



QString Payment::id() const { Q_D(const Payment); return d->id; }

void Payment::setId(const QString &nId)
{
    Q_D(Payment); 
    if (nId != d->id) {
        d->id = nId;
#ifdef QT_DEBUG
        qDebug() << "Changed id to" << d->id;
#endif
        Q_EMIT idChanged(id());
    }
}




Payment::Intent Payment::intent() const { Q_D(const Payment); return d->intent; }

void Payment::setIntent(Intent nIntent)
{
    Q_D(Payment); 
    if (nIntent != d->intent) {
        d->intent = nIntent;
#ifdef QT_DEBUG
        qDebug() << "Changed intent to" << d->intent;
#endif
        Q_EMIT intentChanged(intent());
    }
}




Payer *Payment::payer() const { Q_D(const Payment); return d->payer; }

void Payment::setPayer(Payer *nPayer)
{
    Q_D(Payment); 
    if (nPayer != d->payer) {
        d->payer = nPayer;
#ifdef QT_DEBUG
        qDebug() << "Changed payer to" << d->payer;
#endif
        Q_EMIT payerChanged(payer());
    }
}




QList<Transaction*> Payment::transactions() const { Q_D(const Payment); return d->transactions; }

void Payment::setTransactions(const QList<Transaction*> &nTransactions)
{
    Q_D(Payment); 
    if (nTransactions != d->transactions) {
        d->transactions = nTransactions;
#ifdef QT_DEBUG
        qDebug() << "Changed transactions to" << d->transactions;
#endif
        Q_EMIT transactionsChanged(transactions());
    }
}




Payment::State Payment::state() const { Q_D(const Payment); return d->state; }

void Payment::setState(State nState)
{
    Q_D(Payment); 
    if (nState != d->state) {
        d->state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << d->state;
#endif
        Q_EMIT stateChanged(state());
    }
}




QString Payment::experienceProfileId() const { Q_D(const Payment); return d->experienceProfileId; }

void Payment::setExperienceProfileId(const QString &nExperienceProfileId)
{
    Q_D(Payment); 
    if (nExperienceProfileId != d->experienceProfileId) {
        d->experienceProfileId = nExperienceProfileId;
#ifdef QT_DEBUG
        qDebug() << "Changed experienceProfileId to" << d->experienceProfileId;
#endif
        Q_EMIT experienceProfileIdChanged(experienceProfileId());
    }
}




QString Payment::noteToPayer() const { Q_D(const Payment); return d->noteToPayer; }

void Payment::setNoteToPayer(const QString &nNoteToPayer)
{
    Q_D(Payment); 
    if (nNoteToPayer != d->noteToPayer) {
        d->noteToPayer = nNoteToPayer;
#ifdef QT_DEBUG
        qDebug() << "Changed noteToPayer to" << d->noteToPayer;
#endif
        Q_EMIT noteToPayerChanged(noteToPayer());
    }
}




RedirectUrls *Payment::redirectUrls() const { Q_D(const Payment); return d->redirectUrls; }

void Payment::setRedirectUrls(RedirectUrls *nRedirectUrls)
{
    Q_D(Payment); 
    if (nRedirectUrls != d->redirectUrls) {
        d->redirectUrls = nRedirectUrls;
#ifdef QT_DEBUG
        qDebug() << "Changed redirectUrls to" << d->redirectUrls;
#endif
        Q_EMIT redirectUrlsChanged(redirectUrls());
    }
}




Payment::FailureReason Payment::failureReason() const { Q_D(const Payment); return d->failureReason; }

void Payment::setFailureReason(FailureReason nFailureReason)
{
    Q_D(Payment); 
    if (nFailureReason != d->failureReason) {
        d->failureReason = nFailureReason;
#ifdef QT_DEBUG
        qDebug() << "Changed failureReason to" << d->failureReason;
#endif
        Q_EMIT failureReasonChanged(failureReason());
    }
}




QDateTime Payment::createTime() const { Q_D(const Payment); return d->createTime; }

void Payment::setCreateTime(const QDateTime &nCreateTime)
{
    Q_D(Payment); 
    if (nCreateTime != d->createTime) {
        d->createTime = nCreateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed createTime to" << d->createTime;
#endif
        Q_EMIT createTimeChanged(createTime());
    }
}




QDateTime Payment::updateTime() const { Q_D(const Payment); return d->updateTime; }

void Payment::setUpdateTime(const QDateTime &nUpdateTime)
{
    Q_D(Payment); 
    if (nUpdateTime != d->updateTime) {
        d->updateTime = nUpdateTime;
#ifdef QT_DEBUG
        qDebug() << "Changed updateTime to" << d->updateTime;
#endif
        Q_EMIT updateTimeChanged(updateTime());
    }
}




QList<Link*> Payment::links() const { Q_D(const Payment); return d->links; }

void Payment::setLinks(const QList<Link*> &nLinks)
{
    Q_D(Payment); 
    if (nLinks != d->links) {
        d->links = nLinks;
#ifdef QT_DEBUG
        qDebug() << "Changed links to" << d->links;
#endif
        Q_EMIT linksChanged(links());
    }
}



QVariantMap Payment::toVariant()
{
    Q_D(Payment);

    QVariantMap map;

    QString it; // intent
    switch(intent()) {
    case Sale:
        it = QStringLiteral("sale");
        break;
    case Authorize:
        it = QStringLiteral("authorize");
        break;
    case Order:
        it = QStringLiteral("order");
        break;
    default:
        break;
    }

    d->addStringToVariantMap(&map, QStringLiteral("intent"), it);

    if (payer()) {
        d->addMapToVariantMap(&map, QStringLiteral("payer"), payer()->toVariant());
    }

    if (!transactions().isEmpty()) {
        QVariantList trans;
        const auto trs = transactions();
        for (Transaction *t : trs) {
            trans.append(t->toVariant());
        }
        d->addListToVariantMap(&map, QStringLiteral("transactions"), trans);
    }

    d->addStringToVariantMap(&map, QStringLiteral("experience_profile_id"), experienceProfileId());
    d->addStringToVariantMap(&map, QStringLiteral("note_to_payer"), noteToPayer(), 165);

    if (redirectUrls()) {
        d->addMapToVariantMap(&map, QStringLiteral("redirect_urls"), redirectUrls()->toVariant());
    }

    return map;
}



QJsonObject Payment::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}


QJsonDocument Payment::toJsonDocument()
{
    return QJsonDocument(toJsonObject());
}



QByteArray Payment::toBinaryData()
{
    return toJsonDocument().toBinaryData();
}



QByteArray Payment::toJson()
{
    return toJsonDocument().toJson();
}



bool Payment::addTransaction(Transaction *nTransaction)
{
    if (nTransaction) {

        if (nTransaction->thread() != this->thread()) {
            nTransaction->moveToThread(this->thread());
            if (nTransaction->thread() != this->thread()) {
                qCritical("Failed to move transaction to the model's thread");
                return false;
            }
        }

        nTransaction->setParent(this);

        Q_D(Payment);

        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        d->transactions.append(nTransaction);

        endInsertRows();

        return true;

    } else {
        return false;
    }
}




void Payment::addTransactions(const QList<Transaction *> &nTransactions)
{
    if (!nTransactions.isEmpty()) {

        Q_D(Payment);

        QList<Transaction*> trsToAdd;

        for (Transaction *t : nTransactions) {
            if (t->thread() != this->thread()) {
                t->moveToThread(this->thread());
                if (t->thread() == this->thread()) {
                    t->setParent(this);
                    trsToAdd.append(t);
                } else {
                    qWarning("Failed to move transaction to model's thread.");
                }
            }
        }

        if (!trsToAdd.isEmpty()) {

            beginInsertRows(QModelIndex(), rowCount(), rowCount() + trsToAdd.size() - 1);

            d->transactions.append(nTransactions);

            endInsertRows();

        }
    }
}



Transaction *Payment::addNewTransaction()
{
    Transaction *t = new Transaction(this);
    PaymentAmount *pa = new PaymentAmount(t);
    t->setAmount(pa);
    if (addTransaction(t)) {
        return t;
    } else {
        qWarning("Failed to add new transaction.");
        delete t;
        return nullptr;
    }
}


Transaction *Payment::addNewTransaction(float total, const QString &currency, const QString &description)
{
    Transaction *t = new Transaction(this);
    PaymentAmount *pa = new PaymentAmount(total, currency, t);
    t->setAmount(pa);
    t->setDescription(description);
    if (addTransaction(t)) {
        return t;
    } else {
        qWarning("Failed to add new transaction.");
        delete t;
        return nullptr;
    }
}



void Payment::removeTransaction(int idx)
{
    if (idx < 0 || idx >= rowCount()) {
        return;
    }

    Q_D(Payment);

    beginRemoveRows(QModelIndex(), idx, idx);

    delete d->transactions.takeAt(idx);

    endRemoveRows();
}



void Payment::removeTransaction(Transaction *transaction)
{
    Q_D(const Payment);

    const int idx = d->transactions.indexOf(transaction);

    removeTransaction(idx);
}



Transaction* Payment::takeTransaction(int idx)
{
    if (idx < 0 || idx >= rowCount()) {
        return nullptr;
    }

    Q_D(Payment);

    beginRemoveRows(QModelIndex(), idx, idx);

    Transaction *t = d->transactions.takeAt(idx);
    t->setParent(nullptr);

    endRemoveRows();

    return t;
}




Transaction* Payment::takeTransaction(Transaction *transaction)
{
    Q_D(const Payment);

    const int idx = d->transactions.indexOf(transaction);

    return takeTransaction(idx);
}



QUrl Payment::getLinkURL(const QString &rel) const
{
    const Link *l = getLink(rel);
    if (l) {
        return l->href();
    } else {
        return QUrl();
    }
}



Link* Payment::getLink(const QString &rel) const
{
    Q_D(const Payment);

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



void Payment::addRedirectUrls(const QUrl &returnUrl, const QUrl &cancelUrl)
{
    Q_D(Payment);

    if (!d->redirectUrls) {
        d->redirectUrls = new RedirectUrls(returnUrl, cancelUrl, this);
    } else {
        d->redirectUrls->setReturnUrl(returnUrl);
        d->redirectUrls->setCancelUrl(cancelUrl);
    }
}




void Payment::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void Payment::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Payment);

    setId(json.value(QStringLiteral("id")).toString(id()));

    const QString sIntent = json.value(QStringLiteral("intent")).toString();
    if (QString::compare(sIntent, QStringLiteral("sale"), Qt::CaseInsensitive)) {
        setIntent(Sale);
    } else if (QString::compare(sIntent, QStringLiteral("authorize"), Qt::CaseInsensitive)) {
        setIntent(Authorize);
    } else if (QString::compare(sIntent, QStringLiteral("order"), Qt::CaseInsensitive)) {
        setIntent(Order);
    } else {
        setIntent(NoIntent);
    }

    const QJsonObject po = json.value(QStringLiteral("payer")).toObject();
    Payer *oldPo = payer();
    if (!po.isEmpty()) {
        if (oldPo) {
            oldPo->loadFromJson(po);
        } else {
            setPayer(new Payer(po, this));
        }
    } else {
        setPayer(nullptr);
        delete oldPo;
    }

    const QJsonArray ts = json.value(QStringLiteral("transactions")).toArray();
    d->clearTransactions();
    if (!ts.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, ts.count() - 1);
        QJsonArray::const_iterator i = ts.constBegin();
        while (i != ts.constEnd()) {
            d->transactions.append(new Transaction(i->toObject(), this));
            ++i;
        }
        endInsertRows();
    }

    const QString sState = json.value(QStringLiteral("state")).toString();
    if (QString::compare(sState, QStringLiteral("created"), Qt::CaseInsensitive)) {
        setState(Created);
    } else if (QString::compare(sState, QStringLiteral("approved"), Qt::CaseInsensitive)) {
        setState(Approved);
    } else if (QString::compare(sState, QStringLiteral("failed"), Qt::CaseInsensitive)) {
        setState(Failed);
    } else{
        setState(NoState);
    }

    setExperienceProfileId(json.value(QStringLiteral("experience_profile_id")).toString(experienceProfileId()));

    setNoteToPayer(json.value(QStringLiteral("note_to_payer")).toString(noteToPayer()));

    const QJsonObject rus = json.value(QStringLiteral("redirect_urls")).toObject();
    RedirectUrls *oldRus = redirectUrls();
    if (!rus.isEmpty()) {
        if (oldRus) {
            oldRus->loadFromJson(rus);
        } else {
            setRedirectUrls(new RedirectUrls(rus, this));
        }
    } else {
        setRedirectUrls(nullptr);
        delete oldRus;
    }

    const QString sfr = json.value(QStringLiteral("failure_reason")).toString();
    if (QString::compare(sfr, QStringLiteral("UNABLE_TO_COMPLETE_TRANSACTION"), Qt::CaseInsensitive)) {
        setFailureReason(UnableToCompleteTransaction);
    } else if (QString::compare(sfr, QStringLiteral("INVALID_PAYMENT_METHOD"), Qt::CaseInsensitive)) {
        setFailureReason(InvalidPaymentMethod);
    } else if (QString::compare(sfr, QStringLiteral("PAYER_CANNOT_PAY"), Qt::CaseInsensitive)) {
        setFailureReason(PayerCannotPay);
    } else if (QString::compare(sfr, QStringLiteral("CANNOT_PAY_THIS_PAYEE"), Qt::CaseInsensitive)) {
        setFailureReason(CannotPayThisPayee);
    } else if (QString::compare(sfr, QStringLiteral("REDIRECT_REQUIRED"), Qt::CaseInsensitive)) {
        setFailureReason(RedirectRequired);
    } else if (QString::compare(sfr, QStringLiteral("PAYEE_FILTER_RESTRICTIONS"), Qt::CaseInsensitive)) {
        setFailureReason(PayeeFilterRestrictions);
    } else {
        setFailureReason(NoFailureReason);
    }

    const QString sCreateTime = json.value(QStringLiteral("create_time")).toString();
    if (!sCreateTime.isEmpty()) {
        setCreateTime(QDateTime::fromString(sCreateTime, Qt::ISODate));
    } else {
        setCreateTime(QDateTime());
    }

    const QString sUpdateTime = json.value(QStringLiteral("update_time")).toString();
    if (!sUpdateTime.isEmpty()) {
        setUpdateTime(QDateTime::fromString(sUpdateTime, Qt::ISODate));
    } else {
        setUpdateTime(QDateTime());
    }

    const QJsonArray la = json.value(QStringLiteral("links")).toArray();
    d->clearLinks();
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
