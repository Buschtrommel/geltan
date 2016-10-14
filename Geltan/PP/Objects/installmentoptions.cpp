/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/installmentoptions.cpp
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

#include "installmentoptions_p.h"
#include <Geltan/PP/Objects/installmentdescription.h>
#include <Geltan/PP/ppenumsmap.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


InstallmentOptions::InstallmentOptions(QObject *parent) :
    QAbstractListModel(parent), d_ptr(new InstallmentOptionsPrivate(this))
{
}


InstallmentOptions::InstallmentOptions(const QJsonDocument &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new InstallmentOptionsPrivate(this))
{
    loadFromJson(json);
}


InstallmentOptions::InstallmentOptions(const QJsonObject &json, QObject *parent) :
    QAbstractListModel(parent), d_ptr(new InstallmentOptionsPrivate(this))
{
    loadFromJson(json);
}


InstallmentOptions::~InstallmentOptions()
{

}




QHash<int, QByteArray> InstallmentOptions::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    return roles;
}



int InstallmentOptions::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const InstallmentOptions);
    return d->installmentOptions.count();
}



QModelIndex InstallmentOptions::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}



QVariant InstallmentOptions::data(const QModelIndex &index, int role) const
{
    Q_D(const InstallmentOptions);

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (rowCount()-1)) {
        return QVariant();
    }

    if (role == Item) {
        return QVariant::fromValue<InstallmentDescription*>(d->installmentOptions.at(index.row()));
    } else {
        return QVariant();
    }
}




QString InstallmentOptions::installmentId() const { Q_D(const InstallmentOptions); return d->installmentId; }

void InstallmentOptions::setInstallmentId(const QString &nInstallmentId)
{
    Q_D(InstallmentOptions);
    if (nInstallmentId != d->installmentId) {
        d->installmentId = nInstallmentId;
#ifdef QT_DEBUG
        qDebug() << "Changed installmentId to" << d->installmentId;
#endif
        Q_EMIT installmentIdChanged(installmentId());
    }
}




PayPal::CreditCardType InstallmentOptions::network() const { Q_D(const InstallmentOptions); return d->network; }

void InstallmentOptions::setNetwork(PayPal::CreditCardType nNetwork)
{
    Q_D(InstallmentOptions);
    if (nNetwork != d->network) {
        d->network = nNetwork;
#ifdef QT_DEBUG
        qDebug() << "Changed network to" << d->network;
#endif
        Q_EMIT networkChanged(network());
    }
}




QString InstallmentOptions::issuer() const { Q_D(const InstallmentOptions); return d->issuer; }

void InstallmentOptions::setIssuer(const QString &nIssuer)
{
    Q_D(InstallmentOptions);
    if (nIssuer != d->issuer) {
        d->issuer = nIssuer;
#ifdef QT_DEBUG
        qDebug() << "Changed issuer to" << d->issuer;
#endif
        Q_EMIT issuerChanged(issuer());
    }
}




QList<InstallmentDescription*> InstallmentOptions::installmentOptions() const { Q_D(const InstallmentOptions); return d->installmentOptions; }

void InstallmentOptions::setInstallmentOptions(const QList<InstallmentDescription*> &nInstallmentOptions)
{
    Q_D(InstallmentOptions);
    if (nInstallmentOptions != d->installmentOptions) {
        d->installmentOptions = nInstallmentOptions;
#ifdef QT_DEBUG
        qDebug() << "Changed installmentOptions to" << d->installmentOptions;
#endif
        Q_EMIT installmentOptionsChanged(installmentOptions());
    }
}




void InstallmentOptions::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}



void InstallmentOptions::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(InstallmentOptions);

    QScopedPointer<const PPEnumsMap> em(new PPEnumsMap);

    setInstallmentId(json.value(QStringLiteral("installment_id")).toString());

    setNetwork(em->creditCardTypeTokenToEnum(json.value(QStringLiteral("network")).toString()));

    setIssuer(json.value(QStringLiteral("issuer")).toString());

    const QJsonArray ios = json.value(QStringLiteral("installment_options")).toArray();
    d->clear();
    if (!ios.isEmpty()) {
        beginInsertRows(QModelIndex(), 0, ios.count() - 1);

        QJsonArray::const_iterator i = ios.constBegin();
        while (i != ios.constEnd()) {
            d->installmentOptions.append(new InstallmentDescription(i->toObject(), this));
            ++i;
        }

        endInsertRows();
    }
}
