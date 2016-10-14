/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/processorresponse.h
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

#ifndef PROCESSORRESPONSE_H
#define PROCESSORRESPONSE_H

#include <QObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {



class ProcessorResponsePrivate;

/*!
 * \brief Collection of payment response related fields returned from a payment request.
 *
 * \ppPaymentsApi{processor_response}
 *
 * \headerfile "" <Geltan/PP/Objects/processorresponse.h>
 */
class GELTANSHARED_EXPORT ProcessorResponse : public QObject
{
    Q_OBJECT
    /*!
     * \brief Paypal normalized response code, generated from the processor's specific response code.
     *
     * \ppApiName{response_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>responseCode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>responseCodeChanged(const QString &responseCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString responseCode READ responseCode NOTIFY responseCodeChanged)
    /*!
     * \brief Address Verification System response code.
     *
     * https://developer.paypal.com/webapps/developer/docs/classic/api/AVSResponseCodes/
     *
     * \ppApiName{avs_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>avsCode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>avsCodeChanged(const QString &avsCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString avsCode READ avsCode NOTIFY avsCodeChanged)
    /*!
     * \brief CVV System response code.
     *
     * https://developer.paypal.com/webapps/developer/docs/classic/api/AVSResponseCodes/
     *
     * \ppApiName{cvv_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>cvvCode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>cvvCodeChanged(const QString &cvvCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString cvvCode READ cvvCode NOTIFY cvvCodeChanged)
    /*!
     * \brief Provides merchant advice on how to handle declines related to recurring payments.
     *
     * \ppApiName{advice_code}
     *
     * \par Access functions:
     * <TABLE><TR><TD>AdviceCode</TD><TD>adviceCode() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>adviceCodeChanged(AdviceCode adviceCode)</TD></TR></TABLE>
     */
    Q_PROPERTY(AdviceCode adviceCode READ adviceCode NOTIFY adviceCodeChanged)
    /*!
     * \brief Response back from the authorization. Provided by the processor.
     *
     * \ppApiName{eci_submitted}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>eciSubmitted() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>eciSubmittedChanged(const QString &eciSubmitted)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString eciSubmitted READ eciSubmitted NOTIFY eciSubmittedChanged)
    /*!
     * \brief Visa Payer Authentication Service status. Will be return from processor.
     *
     * \ppApiName{vpas}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>vpas() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>vpasChanged(const QString &vpas)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString vpas READ vpas NOTIFY vpasChanged)
public:
    /*!
     * \brief Constructs a new empty ProcessorResponse object.
     */
    explicit ProcessorResponse(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new ProcessorResponse object from JSON data.
     */
    ProcessorResponse(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new ProcessorResponse object from JSON data.
     */
    ProcessorResponse(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the ProcessorResponse object.
     */
    ~ProcessorResponse();


    /*!
     * \brief How to handle declines related to recurring payments Valid Values.
     */
    enum AdviceCode {
        NoAdviceCode                                    = 0,
        NewAccountInformation                           = 1,
        TryAgainLater                                   = 2,
        StopSpecificPayment                             = 3,
        DoNotTryAgain                                   = 4,
        RevokeAuthorizationForFuturePayment             = 5,
        DoNotTryAgainCardHolderCancelledRecurringCharge = 6,
        CancelAllRecurringPayments                      = 7
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(AdviceCode)
#else
    Q_ENUMS(AdviceCode)
#endif

    QString responseCode() const;
    QString avsCode() const;
    QString cvvCode() const;
    AdviceCode adviceCode() const;
    QString eciSubmitted() const;
    QString vpas() const;


    /*!
     * \brief Loads data from a QJsonDocument into the ProcessorResponse object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the ProcessorResponse object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void responseCodeChanged(const QString &responseCode);
    void avsCodeChanged(const QString &avsCode);
    void cvvCodeChanged(const QString &cvvCode);
    void adviceCodeChanged(AdviceCode adviceCode);
    void eciSubmittedChanged(const QString &eciSubmitted);
    void vpasChanged(const QString &vpas);

protected:
    const QScopedPointer<ProcessorResponsePrivate> d_ptr;

private:
    Q_DISABLE_COPY(ProcessorResponse)
    Q_DECLARE_PRIVATE(ProcessorResponse)

};

}
}

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::ProcessorResponse::AdviceCode)
#endif


#endif // PROCESSORRESPONSE_H
