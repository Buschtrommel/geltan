/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/processorresponse_p.h
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

#ifndef PROCESSORRESPONSE_P_H
#define PROCESSORRESPONSE_P_H

#include "processorresponse.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

namespace Geltan {
namespace PP {


class ProcessorResponsePrivate
{
public:
    ProcessorResponsePrivate(ProcessorResponse *parent) :
        q_ptr(parent),
        adviceCode(ProcessorResponse::NoAdviceCode)
    {}

    ~ProcessorResponsePrivate() {}

    void setResponseCode(const QString &nResponseCode)
    {
        if (responseCode != nResponseCode) {
            Q_Q(ProcessorResponse);
            responseCode = nResponseCode;
#ifdef QT_DEBUG
            qDebug() << "Changed responseCode to" << responseCode;
#endif
            Q_EMIT q->responseCodeChanged(responseCode);
        }
    }

    void setAvsCode(const QString &nAvsCode)
    {
        if (avsCode != nAvsCode) {
            Q_Q(ProcessorResponse);
            avsCode = nAvsCode;
#ifdef QT_DEBUG
            qDebug() << "Changed responseCode avsCode" << avsCode;
#endif
            Q_EMIT q->avsCodeChanged(avsCode);
        }
    }

    void setCvvCode(const QString &nCvvCode)
    {
        if (cvvCode != nCvvCode) {
            Q_Q(ProcessorResponse);
            cvvCode = nCvvCode;
#ifdef QT_DEBUG
            qDebug() << "Changed cvvCode avsCode" << cvvCode;
#endif
            Q_EMIT q->cvvCodeChanged(cvvCode);
        }
    }

    void setAdviceCode(const QString &ac)
    {
        if (ac == QLatin1String("01_NEW_ACCOUNT_INFORMATION")) {
            setAdviceCode(ProcessorResponse::NewAccountInformation);
        } else if (ac == QLatin1String("02_TRY_AGAIN_LATER")) {
            setAdviceCode(ProcessorResponse::TryAgainLater);
        } else if (ac == QLatin1String("02_STOP_SPECIFIC_PAYMENT")) {
            setAdviceCode(ProcessorResponse::StopSpecificPayment);
        } else if (ac == QLatin1String("03_DO_NOT_TRY_AGAIN")) {
            setAdviceCode(ProcessorResponse::DoNotTryAgain);
        } else if (ac == QLatin1String("03_REVOKE_AUTHORIZATION_FOR_FUTURE_PAYMENT")) {
            setAdviceCode(ProcessorResponse::RevokeAuthorizationForFuturePayment);
        } else if (ac == QLatin1String("21_DO_NOT_TRY_AGAIN_CARD_HOLDER_CANCELLED_RECURRRING_CHARGE")) {
            setAdviceCode(ProcessorResponse::DoNotTryAgainCardHolderCancelledRecurringCharge);
        } else if (ac == QLatin1String("21_CANCEL_ALL_RECURRING_PAYMENTS")) {
            setAdviceCode(ProcessorResponse::CancelAllRecurringPayments);
        } else {
            setAdviceCode(ProcessorResponse::NoAdviceCode);
        }
    }

    void setAdviceCode(ProcessorResponse::AdviceCode nAdviceCode)
    {
        if (adviceCode != nAdviceCode) {
            Q_Q(ProcessorResponse);
            adviceCode = nAdviceCode;
#ifdef QT_DEBUG
            qDebug() << "Changed cvvCode adviceCode" << cvvCode;
#endif
            Q_EMIT q->adviceCodeChanged(adviceCode);
        }
    }

    void setEciSubmitted(const QString &nEciSubmitted)
    {
        if (eciSubmitted != nEciSubmitted) {
            Q_Q(ProcessorResponse);
            eciSubmitted = nEciSubmitted;
#ifdef QT_DEBUG
            qDebug() << "Changed eciSubmitted adviceCode" << eciSubmitted;
#endif
            Q_EMIT q->eciSubmittedChanged(eciSubmitted);
        }
    }

    void setVpas(const QString &nVpas)
    {
        if (vpas != nVpas) {
            Q_Q(ProcessorResponse);
            vpas = nVpas;
#ifdef QT_DEBUG
            qDebug() << "Changed vpas adviceCode" << vpas;
#endif
            Q_EMIT q->vpasChanged(vpas);
        }
    }

    ProcessorResponse * const q_ptr;
    Q_DECLARE_PUBLIC(ProcessorResponse)
    QString responseCode;
    QString avsCode;
    QString cvvCode;
    ProcessorResponse::AdviceCode adviceCode;
    QString eciSubmitted;
    QString vpas;
};

}
}

#endif // PROCESSORRESPONSE_P_H
