/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * transaction.cpp
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

#include "transaction_p.h"
#include <Geltan/PP/Objects/related.h>
#include <Geltan/PP/Objects/sale.h>
#include <Geltan/PP/Objects/authorization.h>
#include <Geltan/PP/Objects/order.h>
#include <Geltan/PP/Objects/capture.h>
#include <Geltan/PP/Objects/refund.h>
#include <Geltan/PP/Objects/paymentamount.h>
#include <Geltan/PP/Objects/paymentoptions.h>
#include <Geltan/PP/Objects/itemlist.h>
#include <Geltan/PP/Objects/item.h>
#include <Geltan/PP/Objects/details.h>
#include <Geltan/PP/Objects/payee.h>
#include <QJsonDocument>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


Transaction::Transaction(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new TransactionPrivate(this))
{
}


Transaction::Transaction(const QJsonDocument &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new TransactionPrivate(this))
{
    loadFromJson(json);
}


Transaction::Transaction(const QJsonObject &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new TransactionPrivate(this))
{
    loadFromJson(json);
}


Transaction::~Transaction()
{
}



QHash<int, QByteArray> Transaction::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(RelItem, QByteArrayLiteral("relitem"));
    roles.insert(Sale, QByteArrayLiteral("sale"));
    roles.insert(Authorization, QByteArrayLiteral("authorization"));
    roles.insert(Order, QByteArrayLiteral("order"));
    roles.insert(Capture, QByteArrayLiteral("capture"));
    roles.insert(Refund, QByteArrayLiteral("refund"));
    return roles;
}



int Transaction::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const Transaction);
    return d->relatedResources.count();
}


QModelIndex Transaction::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}


QVariant Transaction::data(const QModelIndex &index, int role) const
{
    Q_D(const Transaction);

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount()-1)) {
        return QVariant();
    }

    Related *r = d->relatedResources.at(index.row());

    switch (role) {
    case RelItem:
        return QVariant::fromValue<Related*>(r);
    case Sale:
        return QVariant::fromValue(r->sale());
    case Authorization:
        return QVariant::fromValue(r->authorization());
    case Order:
        return QVariant::fromValue(r->order());
    case Capture:
        return QVariant::fromValue(r->capture());
    case Refund:
        return QVariant::fromValue(r->refund());
    default:
        return QVariant();
    }
}



QString Transaction::referenceId() const { Q_D(const Transaction); return d->referenceId; }

void Transaction::setReferenceId(const QString &nReferenceId)
{
    Q_D(Transaction); 
    if (nReferenceId != d->referenceId) {
        d->referenceId = nReferenceId;
#ifdef QT_DEBUG
        qDebug() << "Changed referenceId to" << d->referenceId;
#endif
        Q_EMIT referenceIdChanged(referenceId());
    }
}




PaymentAmount *Transaction::amount() const { Q_D(const Transaction); return d->amount; }

void Transaction::setAmount(PaymentAmount *nAmount)
{
    Q_D(Transaction); 
    if (nAmount != d->amount) {
        d->amount = nAmount;
#ifdef QT_DEBUG
        qDebug() << "Changed amount to" << d->amount;
#endif
        Q_EMIT amountChanged(amount());
    }
}




QString Transaction::description() const { Q_D(const Transaction); return d->description; }

void Transaction::setDescription(const QString &nDescription)
{
    Q_D(Transaction); 
    if (nDescription != d->description) {
        d->description = nDescription;
#ifdef QT_DEBUG
        qDebug() << "Changed description to" << d->description;
#endif
        Q_EMIT descriptionChanged(description());
    }
}




QString Transaction::noteToPayee() const { Q_D(const Transaction); return d->noteToPayee; }

void Transaction::setNoteToPayee(const QString &nNoteToPayee)
{
    Q_D(Transaction); 
    if (nNoteToPayee != d->noteToPayee) {
        d->noteToPayee = nNoteToPayee;
#ifdef QT_DEBUG
        qDebug() << "Changed noteToPayee to" << d->noteToPayee;
#endif
        Q_EMIT noteToPayeeChanged(noteToPayee());
    }
}




QString Transaction::custom() const { Q_D(const Transaction); return d->custom; }

void Transaction::setCustom(const QString &nCustom)
{
    Q_D(Transaction); 
    if (nCustom != d->custom) {
        d->custom = nCustom;
#ifdef QT_DEBUG
        qDebug() << "Changed custom to" << d->custom;
#endif
        Q_EMIT customChanged(custom());
    }
}




QString Transaction::invoiceNumber() const { Q_D(const Transaction); return d->invoiceNumber; }

void Transaction::setInvoiceNumber(const QString &nInvoiceNumber)
{
    Q_D(Transaction); 
    if (nInvoiceNumber != d->invoiceNumber) {
        d->invoiceNumber = nInvoiceNumber;
#ifdef QT_DEBUG
        qDebug() << "Changed invoiceNumber to" << d->invoiceNumber;
#endif
        Q_EMIT invoiceNumberChanged(invoiceNumber());
    }
}




QString Transaction::softDescriptor() const { Q_D(const Transaction); return d->softDescriptor; }

void Transaction::setSoftDescriptor(const QString &nSoftDescriptor)
{
    Q_D(Transaction); 
    if (nSoftDescriptor != d->softDescriptor) {
        d->softDescriptor = nSoftDescriptor;
#ifdef QT_DEBUG
        qDebug() << "Changed softDescriptor to" << d->softDescriptor;
#endif
        Q_EMIT softDescriptorChanged(softDescriptor());
    }
}




PaymentOptions *Transaction::paymentOptions() const { Q_D(const Transaction); return d->paymentOptions; }

void Transaction::setPaymentOptions(PaymentOptions *nPaymentOptions)
{
    Q_D(Transaction); 
    if (nPaymentOptions != d->paymentOptions) {
        d->paymentOptions = nPaymentOptions;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentOptions to" << d->paymentOptions;
#endif
        Q_EMIT paymentOptionsChanged(paymentOptions());
    }
}




ItemList *Transaction::itemList() const { Q_D(const Transaction); return d->itemList; }

void Transaction::setItemList(ItemList *nItemList)
{
    Q_D(Transaction); 
    if (nItemList != d->itemList) {
        d->itemList = nItemList;
#ifdef QT_DEBUG
        qDebug() << "Changed itemList to" << d->itemList;
#endif
        Q_EMIT itemListChanged(itemList());
    }
}




QUrl Transaction::notifyUrl() const { Q_D(const Transaction); return d->notifyUrl; }

void Transaction::setNotifyUrl(const QUrl &nNotifyUrl)
{
    Q_D(Transaction); 
    if (nNotifyUrl != d->notifyUrl) {
        d->notifyUrl = nNotifyUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed notifyUrl to" << d->notifyUrl;
#endif
        Q_EMIT notifyUrlChanged(notifyUrl());
    }
}




QUrl Transaction::orderUrl() const { Q_D(const Transaction); return d->orderUrl; }

void Transaction::setOrderUrl(const QUrl &nOrderUrl)
{
    Q_D(Transaction); 
    if (nOrderUrl != d->orderUrl) {
        d->orderUrl = nOrderUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed orderUrl to" << d->orderUrl;
#endif
        Q_EMIT orderUrlChanged(orderUrl());
    }
}




QList<Related*> Transaction::relatedResources() const { Q_D(const Transaction); return d->relatedResources; }

void Transaction::setRelatedResources(const QList<Related*> &nRelatedResources)
{
    Q_D(Transaction); 
    if (nRelatedResources != d->relatedResources) {

        d->clear();
        d->relatedResources = nRelatedResources;

#ifdef QT_DEBUG
        qDebug() << "Changed relatedResources to" << d->relatedResources;
#endif

        Q_EMIT relatedResourcesChanged(relatedResources());
    }
}


Payee *Transaction::payee() const { Q_D(const Transaction); return d->payee; }

void Transaction::setPayee(Payee *nPayee)
{
    Q_D(Transaction);
    if (nPayee != d->payee) {
        d->payee = nPayee;
#ifdef QT_DEBUG
        qDebug() << "Changed payee to" << d->payee;
#endif
        Q_EMIT payeeChanged(payee());
    }
}



bool Transaction::addItem(Item *i)
{
    if (!itemList()) {
        setItemList(new ItemList(this));
    }

    return itemList()->addItem(i);
}



Geltan::PP::Item *Transaction::addNewItem()
{
    if (!itemList()) {
        setItemList(new ItemList(this));
    }

    Item *i = new Item(itemList());
    i->setQuantity(1);

    if (itemList()->addItem(i)) {
        return i;
    } else {
        delete i;
        return nullptr;
    }
}




bool Transaction::addRelatedResource(Related *resource)
{
    Q_D(Transaction);

    if (resource) {

        if (resource->thread() != this->thread()) {
            resource->moveToThread(this->thread());
            if (resource->thread() != this->thread()) {
                qCritical("Failed to move resource to the model's thread.");
                return false;
            }
        }

        resource->setParent(this);

        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        d->relatedResources.append(resource);

        endInsertRows();

        return true;

    } else {
        return false;
    }
}


void Transaction::removeRelatedResource(int idx)
{
    Q_D(Transaction);

    if (!d->relatedResources.isEmpty() && idx > -1 && idx < rowCount()) {

        delete d->relatedResources.takeAt(idx);

    }
}



void Transaction::removeRelatedResource(Related *resource)
{
    Q_D(const Transaction);

    removeRelatedResource(d->relatedResources.indexOf(resource));
}



Related *Transaction::takeRelatedResource(int idx)
{
    Q_D(Transaction);

    if (d->relatedResources.isEmpty() || idx < 0 || idx >= rowCount()) {
        return nullptr;
    }

    Related *r = d->relatedResources.takeAt(idx);
    r->setParent(nullptr);

    return r;
}


Related *Transaction::takeRelatedResource(Related *resource)
{
    Q_D(const Transaction);

    return takeRelatedResource(d->relatedResources.indexOf(resource));
}



void Transaction::setPaymentAmount(const QString &currency, float total, float subtotal, float shipping, float tax, float handlingFee, float shippingDiscount, float insurance, float giftWrap)
{
    if (!amount()) {
        setAmount(new PaymentAmount(total, currency, this));
    } else {
        amount()->setTotal(total);
        amount()->setCurrency(currency);
    }

    if (subtotal || shipping || tax || handlingFee || shippingDiscount || insurance || giftWrap) {
        if (!amount()->details()) {
            amount()->setDetails(new Details(subtotal, shipping, tax, handlingFee, shippingDiscount, insurance, giftWrap, amount()));
        } else {
            Details *det = amount()->details();
            det->setSubtotal(subtotal);
            det->setShipping(shipping);
            det->setTax(tax);
            det->setHandlingFee(handlingFee);
            det->setShippingDiscount(shippingDiscount);
            det->setInsurance(insurance);
            det->setGiftWrap(giftWrap);
        }
    }
}





QVariantMap Transaction::toVariant()
{
    Q_D(Transaction);

    QVariantMap map;

    d->addStringToVariantMap(&map, QStringLiteral("reference_id"), referenceId(), 256);
    if (amount()) {
        d->addMapToVariantMap(&map, QStringLiteral("amount"), amount()->toVariant());
    }
    d->addStringToVariantMap(&map, QStringLiteral("description"), description(), 127);
    d->addStringToVariantMap(&map, QStringLiteral("note_to_payee"), noteToPayee(), 255);
    d->addStringToVariantMap(&map, QStringLiteral("custom"), custom(), 127);
    d->addStringToVariantMap(&map, QStringLiteral("invoice_number"), invoiceNumber(), 127);
    d->addStringToVariantMap(&map, QStringLiteral("soft_descriptor"), softDescriptor(), 22);
    if (paymentOptions()) {
        d->addMapToVariantMap(&map, QStringLiteral("payment_options"), paymentOptions()->toVariant());
    }
    if (itemList()) {
        d->addMapToVariantMap(&map, QStringLiteral("item_list"), itemList()->toVariant());
    }
    d->addStringToVariantMap(&map, QStringLiteral("notify_url"), notifyUrl().toString(), 2048);
    d->addStringToVariantMap(&map, QStringLiteral("order_url"), orderUrl().toString(), 2048);


    return map;
}




QJsonObject Transaction::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void Transaction::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void Transaction::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Transaction);

    setReferenceId(json.value(QStringLiteral("reference_id")).toString());

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

    setDescription(json.value(QStringLiteral("description")).toString());

    setNoteToPayee(json.value(QStringLiteral("note_to_payee")).toString());

    setCustom(json.value(QStringLiteral("custom")).toString());

    setInvoiceNumber(json.value(QStringLiteral("invoice_number")).toString());

    setSoftDescriptor(json.value(QStringLiteral("soft_descriptor")).toString());

    const QJsonObject poo = json.value(QStringLiteral("payment_options")).toObject();
    PaymentOptions *oldPoo = paymentOptions();
    if (!poo.isEmpty()) {
        if (oldPoo) {
            oldPoo->loadFromJson(poo);
        } else {
            setPaymentOptions(new PaymentOptions(poo, this));
        }
    } else {
        setPaymentOptions(nullptr);
        delete oldPoo;
    }

    const QJsonObject ilo = json.value(QStringLiteral("item_list")).toObject();
    ItemList *oldIlo = itemList();
    if (!ilo.isEmpty()) {
        if (oldIlo) {
            oldIlo->loadFromJson(ilo);
        } else {
            setItemList(new ItemList(ilo, this));
        }
    } else {
        setItemList(nullptr);
        delete oldIlo;
    }

    setNotifyUrl(QUrl(json.value(QStringLiteral("notify_url")).toString()));

    setOrderUrl(QUrl(json.value(QStringLiteral("order_url")).toString()));

    const QJsonArray rs = json.value(QStringLiteral("related_resources")).toArray();
    d->clear();
    if (!rs.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, rs.count() - 1);
        QJsonArray::const_iterator i = rs.constBegin();
        while (i != rs.constEnd()) {
            d->relatedResources.append(new Related(i->toObject(), this));
            ++i;
        }
        endInsertRows();
    }

    const QJsonObject pyo = json.value(QStringLiteral("payee")).toObject();
    Payee *oldPyo = payee();
    if (!pyo.isEmpty()) {
        if (oldPyo) {
            oldPyo->loadFromJson(pyo);
        } else {
            setPayee(new Payee(pyo, this));
        }
    } else {
        setPayee(nullptr);
        delete oldPyo;
    }
}
