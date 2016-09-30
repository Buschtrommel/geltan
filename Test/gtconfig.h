/*
   Copyright 2016 Buschtrommel/Matthias Fehring <kontakt@buschmann23.de>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef GTCONFIG_H
#define GTCONFIG_H

#include <QSettings>
#include <QObject>
#include <QDateTime>
#include <Geltan/PP/ppenums.h>

namespace GeltanTest {

/*!
 * \brief Configuration interface for geltanTest
 */
class GtConfig : public QSettings
{
    Q_OBJECT
    /*!
     * \brief The PayPal App Client ID.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>getPayPalClientID() const</TD></TR><TR><TD>void</TD><TD>setPayPalClientID(const QString & payPalClientID)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payPalClientIDChanged(const QString & payPalClientID)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString payPalClientID READ getPayPalClientID WRITE setPayPalClientID NOTIFY payPalClientIDChanged)

    /*!
     * \brief The PayPal App Secret.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>getPayPalSecret() const</TD></TR><TR><TD>void</TD><TD>setPayPalSecret(const QString & payPalSecret)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payPalSecretChanged(const QString & payPalSecret)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString payPalSecret READ getPayPalSecret WRITE setPayPalSecret NOTIFY payPalSecretChanged)

    /*!
     * \brief The PayPal Authentication Token.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>getPayPalToken() const</TD></TR><TR><TD>void</TD><TD>setPayPalToken(const QString & payPalToken)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payPalTokenChanged(const QString & payPalToken)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString payPalToken READ getPayPalToken WRITE setPayPalToken NOTIFY payPalTokenChanged)
    /*!
     * \brief Time the PayPal token expires.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>getPayPalTokenExpiration() const</TD></TR><TR><TD>void</TD><TD>setPayPalTokenExpiration(const QDateTime &payPalTokenExpiration)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payPalTokenExpirationChanged(const QDateTime &payPalTokenExpiration)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime payPalTokenExpiration READ getPayPalTokenExpiration WRITE setPayPalTokenExpiration NOTIFY payPalTokenExpirationChanged)
    /*!
     * \brief The type of the PayPal token.
     *
     * \par Access functions:
     * <TABLE><TR><TD>Geltan::PP::PayPal::TokenType</TD><TD>getPayPalTokenType() const</TD></TR><TR><TD>void</TD><TD>setPayPalTokenType(Geltan::PP::PayPal::TokenType payPalTokenType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payPalTokenTypeChanged(Geltan::PP::PayPal::TokenType payPalTokenType)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::TokenType payPalTokenType READ getPayPalTokenType WRITE setPayPalTokenType NOTIFY payPalTokenTypeChanged)
    /*!
     * \brief Stores the App ID returned by PayPal API.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>getPayPalAppID() const</TD></TR><TR><TD>void</TD><TD>setPayPalAppID(const QString &payPalAppID)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payPalAppIDChanged(const QString &payPalAppID)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString payPalAppID READ getPayPalAppID WRITE setPayPalAppID NOTIFY payPalAppIDChanged)
    /*!
     * \brief Returns true if the current PayPalToken is valid.
     *
     * \par Access functions:
     * <TABLE><TR><TD>bool</TD><TD>isPayPalTokenValid() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payPalTokenValidChanged(bool payPalTokenValid)</TD></TR></TABLE>
     */
    Q_PROPERTY(bool payPalTokenValid READ isPayPalTokenValid NOTIFY payPalTokenValidChanged)
    /*!
     * \brief Last width of the application.
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>getApplicationWidth() const</TD></TR><TR><TD>void</TD><TD>setApplicationWidth(int applicationWidth)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>applicationWidthChanged(int applicationWidth)</TD></TR></TABLE>
     */
    Q_PROPERTY(int applicationWidth READ getApplicationWidth WRITE setApplicationWidth NOTIFY applicationWidthChanged)
    /*!
     * \brief Default PayPal return URL.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>getPaypalReturnUrl() const</TD></TR><TR><TD>void</TD><TD>setPaypalReturnUrl(const QString &paypalReturnUrl)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paypalReturnUrlChanged(const QString &paypalReturnUrl)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString paypalReturnUrl READ getPaypalReturnUrl WRITE setPaypalReturnUrl NOTIFY paypalReturnUrlChanged)
    /*!
     * \brief Default PayPal cancel URL.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>getPaypalCancelUrl() const</TD></TR><TR><TD>void</TD><TD>setPaypalCancelUrl(const QString &paypalCancelUrl)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paypalCancelUrlChanged(const QString &paypalCancelUrl)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString paypalCancelUrl READ getPaypalCancelUrl WRITE setPaypalCancelUrl NOTIFY paypalCancelUrlChanged)
public:
    /*!
     * \brief Constructs a new GtConfig object.
     */
    explicit GtConfig(QObject *parent = 0);


    QString getPayPalClientID() const;
    QString getPayPalSecret() const;


    void setPayPalClientID(const QString &payPalClientID);
    void setPayPalSecret(const QString &payPalSecret);


    QString getPayPalToken() const;
    void setPayPalToken(const QString &payPalToken);


    QDateTime getPayPalTokenExpiration() const;
    void setPayPalTokenExpiration(const QDateTime &payPalTokenExpiration);


    Geltan::PP::PayPal::TokenType getPayPalTokenType() const;
    void setPayPalTokenType(Geltan::PP::PayPal::TokenType payPalTokenType);


    QString getPayPalAppID() const;
    void setPayPalAppID(const QString &payPalAppID);

    bool isPayPalTokenValid() const;

    int getApplicationWidth() const;
    void setApplicationWidth(int applicationWidth);

    QString getPaypalReturnUrl() const;
    void setPaypalReturnUrl(const QString &paypalReturnUrl);

    QString getPaypalCancelUrl() const;
    void setPaypalCancelUrl(const QString &paypalCancelUrl);

Q_SIGNALS:
    void payPalClientIDChanged(const QString &payPalClientID);
    void payPalSecretChanged(const QString &payPalSecret);
    void payPalTokenChanged(const QString &payPalToken);
    void payPalTokenExpirationChanged(const QDateTime &payPalTokenExpiration);
    void payPalTokenTypeChanged(Geltan::PP::PayPal::TokenType payPalTokenType);
    void payPalAppIDChanged(const QString &payPalAppID);
    void payPalTokenValidChanged(bool payPalTokenValid);
    void applicationWidthChanged(int applicationWidth);
    void paypalReturnUrlChanged(const QString &paypalReturnUrl);
    void paypalCancelUrlChanged(const QString &paypalCancelUrl);

private:
    QString m_payPalClientID;
    QString m_payPalSecret;
    QString m_payPalToken;
    QDateTime m_payPalTokenExpiration;
    Geltan::PP::PayPal::TokenType m_payPalTokenType;
    QString m_payPalAppID;
    int m_applicationWidth;
    QString m_paypalReturnUrl;
    QString m_paypalCancelUrl;
    Q_DISABLE_COPY(GtConfig)
};

}

#endif // GTCONFIG_H
