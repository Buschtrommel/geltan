/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/payer.cpp
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

#include "payer_p.h"
#include <Geltan/PP/Objects/payerinfo.h>
#include <Geltan/PP/Objects/fundinginstrument.h>
#include <Geltan/PP/ppenumsmap.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;

Payer::Payer(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new PayerPrivate(this))
{
}



Payer::Payer(const QJsonDocument &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new PayerPrivate(this))
{
    loadFromJson(json);
}


Payer::Payer(const QJsonObject &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new PayerPrivate(this))
{
    loadFromJson(json);
}



Payer::~Payer()
{

}




QHash<int, QByteArray> Payer::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    return roles;
}



int Payer::rowCount(const QModelIndex &parent) const
{
    Q_D(const Payer);
    Q_UNUSED(parent)
    return d->fundingInstruments.count();
}



QModelIndex Payer::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}




QVariant Payer::data(const QModelIndex &index, int role) const
{
    Q_D(const Payer);

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount() - 1)) {
        return QVariant();
    }

    if (role == Item) {
        return QVariant::fromValue<FundingInstrument*>(d->fundingInstruments.at(index.row()));
    } else {
        return QVariant();
    }
}





PayPal::PaymentMethod Payer::paymentMethod() const { Q_D(const Payer); return d->paymentMethod; }

void Payer::setPaymentMethod(PayPal::PaymentMethod nPaymentMethod)
{
    Q_D(Payer); 
    if (nPaymentMethod != d->paymentMethod) {
        d->paymentMethod = nPaymentMethod;
#ifdef QT_DEBUG
        qDebug() << "Changed paymentMethod to" << d->paymentMethod;
#endif
        Q_EMIT paymentMethodChanged(paymentMethod());
    }
}




Payer::Status Payer::status() const { Q_D(const Payer); return d->status; }

void Payer::setStatus(Payer::Status nStatus)
{
    Q_D(Payer); 
    if (nStatus != d->status) {
        d->status = nStatus;
#ifdef QT_DEBUG
        qDebug() << "Changed status to" << d->status;
#endif
        Q_EMIT statusChanged(status());
    }
}




QList<Geltan::PP::FundingInstrument *> Payer::fundingInstruments() const { Q_D(const Payer); return d->fundingInstruments; }

void Payer::setFundingInstruments(const QList<Geltan::PP::FundingInstrument *> &nFundingInstruments)
{
    Q_D(Payer);
    if (nFundingInstruments != d->fundingInstruments) {
        d->fundingInstruments = nFundingInstruments;
#ifdef QT_DEBUG
        qDebug() << "Changed fundingInstruments to" << d->fundingInstruments;
#endif
        Q_EMIT fundingInstrumentsChanged(fundingInstruments());
    }
}




Payer::FundingInstrumentType Payer::externalSelectedFundingInstrumentType() const { Q_D(const Payer); return d->externalSelectedFundingInstrumentType; }

void Payer::setExternalSelectedFundingInstrumentType(FundingInstrumentType nExternalSelectedFundingInstrumentType)
{
    Q_D(Payer);
    if (nExternalSelectedFundingInstrumentType != d->externalSelectedFundingInstrumentType) {
        d->externalSelectedFundingInstrumentType = nExternalSelectedFundingInstrumentType;
#ifdef QT_DEBUG
        qDebug() << "Changed externalSelectedFundingInstrumentType to" << d->externalSelectedFundingInstrumentType;
#endif
        Q_EMIT externalSelectedFundingInstrumentTypeChanged(externalSelectedFundingInstrumentType());
    }
}




PayerInfo *Payer::payerInfo() const { Q_D(const Payer); return d->payerInfo; }

void Payer::setPayerInfo(PayerInfo *nPayerInfo)
{
    Q_D(Payer);
    if (nPayerInfo != d->payerInfo) {
        d->payerInfo = nPayerInfo;
#ifdef QT_DEBUG
        qDebug() << "Changed payerInfo to" << d->payerInfo;
#endif
        Q_EMIT payerInfoChanged(payerInfo());
    }
}




bool Payer::addFundingInstrument(FundingInstrument *fi)
{
    if (fi) {
        if (fi->thread() != this->thread()) {
            fi->moveToThread(this->thread());
            if (fi->thread() != this->thread()) {
                qCritical("Failed to move funding instrument to the model's thread.");
                return false;
            }
        }

        fi->setParent(this);

        Q_D(Payer);

        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        d->fundingInstruments.append(fi);

        endInsertRows();

        Q_EMIT fundingInstrumentsChanged(fundingInstruments());

        return true;

    } else {
        return false;
    }
}



void Payer::addFundingInstruments(const QList<FundingInstrument *> &fis)
{
    if (fis.isEmpty()) {
        return;
    }

    Q_D(Payer);

    QList<FundingInstrument*> fisToAdd;

    for (FundingInstrument *fi : fis) {
        if (fi->thread() != this->thread()) {
            fi->moveToThread(this->thread());
            if (fi->thread() == this->thread()) {
                fi->setParent(this);
                fisToAdd.append(fi);
            } else {
                qWarning("Failed to move funding instrument to the model's thread.");
            }
        }
    }

    if (!fisToAdd.isEmpty()) {

        beginInsertRows(QModelIndex(), rowCount(), rowCount() + fisToAdd.size() - 1);

        d->fundingInstruments.append(fisToAdd);

        endInsertRows();

        Q_EMIT fundingInstrumentsChanged(fundingInstruments());
    }
}




QVariantMap Payer::toVariant()
{
    Q_D(Payer);

    QVariantMap map;

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    d->addStringToVariantMap(&map, QStringLiteral("payment_method"), em->paymentMethodEnumToToken(paymentMethod()));

    if (!fundingInstruments().isEmpty()) {
        QVariantList list;
        const auto fundingis = fundingInstruments();
        for (FundingInstrument *fi : fundingis) {
            list.append(fi->toVariant());
        }
        d->addListToVariantMap(&map, QStringLiteral("funding_instruments"), list);
    }

    QString fit; // funding instrument type

    switch(externalSelectedFundingInstrumentType()) {
    case Credit:
        fit = QStringLiteral("CREDIT");
        break;
    case PayUponInvoice:
        fit = QStringLiteral("PAY_UPON_INVOICE");
        break;
    default:
        break;
    }

    d->addStringToVariantMap(&map, QStringLiteral("external_selected_funding_instrument_type"), fit);

    if (payerInfo()) {
        d->addMapToVariantMap(&map, QStringLiteral("payer_info"), payerInfo()->toVariant());
    }

    return map;
}


QJsonObject Payer::toJsonObject()
{
    return QJsonObject::fromVariantMap(this->toVariant());
}



void Payer::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void Payer::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(Payer);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    setPaymentMethod(em->paymentMethodTokenToEnum(json.value(QStringLiteral("payment_method")).toString()));

    const QString sStatus = json.value(QStringLiteral("status")).toString();
    if (sStatus == QLatin1String("VERIFIED")) {
        setStatus(Verified);
    } else if (sStatus == QLatin1String("UNVERIFIED")) {
        setStatus(Unverified);
    } else {
        setStatus(NoStatus);
    }

    const QJsonArray fis = json.value(QStringLiteral("funding_instruments")).toArray();
    d->clearFundingInstruments();
    if (!fis.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, fis.count() - 1);
        QJsonArray::const_iterator i = fis.constBegin();
        while (i != fis.constEnd()) {
            d->fundingInstruments.append(new FundingInstrument(i->toObject(), this));
            ++i;
        }
        endInsertRows();
    }

    const QString sExtFis = json.value(QStringLiteral("external_selected_funding_instrument_type")).toString();
    if (sExtFis == QLatin1String("CREDIT")) {
        setExternalSelectedFundingInstrumentType(Credit);
    } else if (sExtFis == QLatin1String("PAY_UPON_INVOICE")) {
        setExternalSelectedFundingInstrumentType(PayUponInvoice);
    } else {
        setExternalSelectedFundingInstrumentType(NoFundingInstrumentType);
    }

    const QJsonObject pio = json.value(QStringLiteral("payer_info")).toObject();
    PayerInfo *oldPio = payerInfo();
    if (!pio.isEmpty()) {
        if (oldPio) {
            oldPio->loadFromJson(pio);
        } else {
            setPayerInfo(new PayerInfo(pio, this));
        }
    } else {
        setPayerInfo(nullptr);
        delete oldPio;
    }
}
