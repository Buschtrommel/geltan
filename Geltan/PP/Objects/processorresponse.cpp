/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/processorresponse.cpp
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

#include "processorresponse_p.h"
#include <QJsonDocument>
#include <QJsonObject>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Geltan;
using namespace PP;


ProcessorResponse::ProcessorResponse(QObject *parent) :
    QObject(parent), d_ptr(new ProcessorResponsePrivate(this))
{
}



ProcessorResponse::ProcessorResponse(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new ProcessorResponsePrivate(this))
{
    loadFromJson(json);
}


ProcessorResponse::ProcessorResponse(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new ProcessorResponsePrivate(this))
{
    loadFromJson(json);
}


ProcessorResponse::~ProcessorResponse()
{
}


QString ProcessorResponse::responseCode() const { Q_D(const ProcessorResponse); return d->responseCode; }


QString ProcessorResponse::avsCode() const { Q_D(const ProcessorResponse); return d->avsCode; }


QString ProcessorResponse::cvvCode() const { Q_D(const ProcessorResponse); return d->cvvCode; }


ProcessorResponse::AdviceCode ProcessorResponse::adviceCode() const { Q_D(const ProcessorResponse); return d->adviceCode; }


QString ProcessorResponse::eciSubmitted() const { Q_D(const ProcessorResponse); return d->eciSubmitted; }


QString ProcessorResponse::vpas() const { Q_D(const ProcessorResponse); return d->vpas; }


void ProcessorResponse::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void ProcessorResponse::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    Q_D(ProcessorResponse);

    d->setResponseCode(json.value(QStringLiteral("response_code")).toString());

    d->setAvsCode(json.value(QStringLiteral("avs_code")).toString());

    d->setCvvCode(json.value(QStringLiteral("cvv_code")).toString());

    d->setAdviceCode(json.value(QStringLiteral("advice_code")).toString());

    d->setEciSubmitted(json.value(QStringLiteral("eci_submitted")).toString());

    d->setVpas(json.value(QStringLiteral("vpas")).toString());
}

