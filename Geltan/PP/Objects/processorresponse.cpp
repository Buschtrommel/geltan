/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * processorresponse.cpp
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
    QObject(parent), d_ptr(new ProcessorResponsePrivate)
{
}



ProcessorResponse::ProcessorResponse(const QJsonDocument &json, QObject *parent) :
    QObject(parent), d_ptr(new ProcessorResponsePrivate)
{
    loadFromJson(json);
}


ProcessorResponse::ProcessorResponse(const QJsonObject &json, QObject *parent) :
    QObject(parent), d_ptr(new ProcessorResponsePrivate)
{
    loadFromJson(json);
}


ProcessorResponse::~ProcessorResponse()
{
}


QString ProcessorResponse::responseCode() const { Q_D(const ProcessorResponse); return d->responseCode; }

void ProcessorResponse::setResponseCode(const QString &nResponseCode)
{
    Q_D(ProcessorResponse); 
    if (nResponseCode != d->responseCode) {
        d->responseCode = nResponseCode;
#ifdef QT_DEBUG
        qDebug() << "Changed responseCode to" << d->responseCode;
#endif
        Q_EMIT responseCodeChanged(responseCode());
    }
}




QString ProcessorResponse::avsCode() const { Q_D(const ProcessorResponse); return d->avsCode; }

void ProcessorResponse::setAvsCode(const QString &nAvsCode)
{
    Q_D(ProcessorResponse); 
    if (nAvsCode != d->avsCode) {
        d->avsCode = nAvsCode;
#ifdef QT_DEBUG
        qDebug() << "Changed avsCode to" << d->avsCode;
#endif
        Q_EMIT avsCodeChanged(avsCode());
    }
}




QString ProcessorResponse::cvvCode() const { Q_D(const ProcessorResponse); return d->cvvCode; }

void ProcessorResponse::setCvvCode(const QString &nCvvCode)
{
    Q_D(ProcessorResponse); 
    if (nCvvCode != d->cvvCode) {
        d->cvvCode = nCvvCode;
#ifdef QT_DEBUG
        qDebug() << "Changed cvvCode to" << d->cvvCode;
#endif
        Q_EMIT cvvCodeChanged(cvvCode());
    }
}




ProcessorResponse::AdviceCode ProcessorResponse::adviceCode() const { Q_D(const ProcessorResponse); return d->adviceCode; }

void ProcessorResponse::setAdviceCode(AdviceCode nAdviceCode)
{
    Q_D(ProcessorResponse); 
    if (nAdviceCode != d->adviceCode) {
        d->adviceCode = nAdviceCode;
#ifdef QT_DEBUG
        qDebug() << "Changed adviceCode to" << d->adviceCode;
#endif
        Q_EMIT adviceCodeChanged(adviceCode());
    }
}




QString ProcessorResponse::eciSubmitted() const { Q_D(const ProcessorResponse); return d->eciSubmitted; }

void ProcessorResponse::setEciSubmitted(const QString &nEciSubmitted)
{
    Q_D(ProcessorResponse); 
    if (nEciSubmitted != d->eciSubmitted) {
        d->eciSubmitted = nEciSubmitted;
#ifdef QT_DEBUG
        qDebug() << "Changed eciSubmitted to" << d->eciSubmitted;
#endif
        Q_EMIT eciSubmittedChanged(eciSubmitted());
    }
}




QString ProcessorResponse::vpas() const { Q_D(const ProcessorResponse); return d->vpas; }

void ProcessorResponse::setVpas(const QString &nVpas)
{
    Q_D(ProcessorResponse); 
    if (nVpas != d->vpas) {
        d->vpas = nVpas;
#ifdef QT_DEBUG
        qDebug() << "Changed vpas to" << d->vpas;
#endif
        Q_EMIT vpasChanged(vpas());
    }
}




void ProcessorResponse::loadFromJson(const QJsonDocument &json)
{
    loadFromJson(json.object());
}


void ProcessorResponse::loadFromJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    setResponseCode(json.value(QStringLiteral("response_code")).toString());

    setAvsCode(json.value(QStringLiteral("avs_code")).toString());

    setCvvCode(json.value(QStringLiteral("cvv_code")).toString());

    const QString ac = json.value(QStringLiteral("advice_code")).toString();
    if (ac == QLatin1String("01_NEW_ACCOUNT_INFORMATION")) {
        setAdviceCode(NewAccountInformation);
    } else if (ac == QLatin1String("02_TRY_AGAIN_LATER")) {
        setAdviceCode(TryAgainLater);
    } else if (ac == QLatin1String("02_STOP_SPECIFIC_PAYMENT")) {
        setAdviceCode(StopSpecificPayment);
    } else if (ac == QLatin1String("03_DO_NOT_TRY_AGAIN")) {
        setAdviceCode(DoNotTryAgain);
    } else if (ac == QLatin1String("03_REVOKE_AUTHORIZATION_FOR_FUTURE_PAYMENT")) {
        setAdviceCode(RevokeAuthorizationForFuturePayment);
    } else if (ac == QLatin1String("21_DO_NOT_TRY_AGAIN_CARD_HOLDER_CANCELLED_RECURRRING_CHARGE")) {
        setAdviceCode(DoNotTryAgainCardHolderCancelledRecurringCharge);
    } else if (ac == QLatin1String("21_CANCEL_ALL_RECURRING_PAYMENTS")) {
        setAdviceCode(CancelAllRecurringPayments);
    } else {
        setAdviceCode(NoAdviceCode);
    }

    setEciSubmitted(json.value(QStringLiteral("eci_submitted")).toString());

    setVpas(json.value(QStringLiteral("vpas")).toString());
}

