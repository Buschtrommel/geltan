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

#include "gtconfig.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace GeltanTest;

GtConfig::GtConfig(QObject *parent) :
    QSettings(parent)
{
    m_payPalClientID = value(QStringLiteral("paypal/clientid")).toString();
    m_payPalSecret = value(QStringLiteral("paypal/secret")).toString();
    m_payPalToken = value(QStringLiteral("paypal/token")).toString();
    m_payPalTokenExpiration = QDateTime::fromTime_t(value(QStringLiteral("paypal/expiration"), 0).toInt());
    m_payPalTokenType = (Geltan::PP::PayPal::TokenType)value(QStringLiteral("paypal/tokentype"), 0).toInt();
    m_payPalAppID = value(QStringLiteral("paypal/appid")).toString();
    m_applicationWidth = value(QStringLiteral("application/width"), 320).toInt();
    m_paypalReturnUrl = value(QStringLiteral("paypal/returnURL")).toString();
    m_paypalCancelUrl = value(QStringLiteral("paypal/cancelURL")).toString();
}



QString GtConfig::getPayPalClientID() const { return m_payPalClientID; }

void GtConfig::setPayPalClientID(const QString & payPalClientID)
{
    if (payPalClientID != m_payPalClientID) {
        m_payPalClientID = payPalClientID;
#ifdef QT_DEBUG
        qDebug() << "Changed payPalClientID to" << m_payPalClientID;
#endif
        setValue(QStringLiteral("paypal/clientid"), m_payPalClientID);

        Q_EMIT payPalClientIDChanged(getPayPalClientID());
    }
}



QString GtConfig::getPayPalSecret() const { return m_payPalSecret; }

void GtConfig::setPayPalSecret(const QString & payPalSecret)
{
    if (payPalSecret != m_payPalSecret) {
        m_payPalSecret = payPalSecret;
#ifdef QT_DEBUG
        qDebug() << "Changed payPalSecret to" << m_payPalSecret;
#endif
        setValue(QStringLiteral("paypal/secret"), m_payPalSecret);

        Q_EMIT payPalSecretChanged(getPayPalSecret());
    }
}



QString GtConfig::getPayPalToken() const { return m_payPalToken; }

void GtConfig::setPayPalToken(const QString & payPalToken)
{
    if (payPalToken != m_payPalToken) {
        m_payPalToken = payPalToken;
#ifdef QT_DEBUG
        qDebug() << "Changed payPalToken to" << m_payPalToken;
#endif
        setValue(QStringLiteral("paypal/token"), m_payPalToken);

        Q_EMIT payPalTokenChanged(getPayPalToken());
        Q_EMIT payPalTokenValidChanged(isPayPalTokenValid());
    }
}



QDateTime GtConfig::getPayPalTokenExpiration() const { return m_payPalTokenExpiration; }

void GtConfig::setPayPalTokenExpiration(const QDateTime &payPalTokenExpiration)
{
    if (payPalTokenExpiration != m_payPalTokenExpiration) {
        m_payPalTokenExpiration = payPalTokenExpiration;
#ifdef QT_DEBUG
        qDebug() << "Changed payPalTokenExpiration to" << m_payPalTokenExpiration;
#endif
        setValue(QStringLiteral("paypal/expiration"), m_payPalTokenExpiration.toTime_t());

        Q_EMIT payPalTokenExpirationChanged(getPayPalTokenExpiration());
        Q_EMIT payPalTokenValidChanged(isPayPalTokenValid());
    }
}




Geltan::PP::PayPal::TokenType GtConfig::getPayPalTokenType() const { return m_payPalTokenType; }

void GtConfig::setPayPalTokenType(Geltan::PP::PayPal::TokenType payPalTokenType)
{
    if (payPalTokenType != m_payPalTokenType) {
        m_payPalTokenType = payPalTokenType;
#ifdef QT_DEBUG
        qDebug() << "Changed payPalTokenType to" << m_payPalTokenType;
#endif
        setValue(QStringLiteral("paypal/tokentype"), (int)m_payPalTokenType);

        Q_EMIT payPalTokenTypeChanged(getPayPalTokenType());
        Q_EMIT payPalTokenValidChanged(isPayPalTokenValid());
    }
}



QString GtConfig::getPayPalAppID() const { return m_payPalAppID; }

void GtConfig::setPayPalAppID(const QString &payPalAppID)
{
    if (payPalAppID != m_payPalAppID) {
        m_payPalAppID = payPalAppID;
#ifdef QT_DEBUG
        qDebug() << "Changed payPalAppID to" << m_payPalAppID;
#endif
        setValue(QStringLiteral("paypal/appid"), m_payPalAppID);

        Q_EMIT payPalAppIDChanged(getPayPalAppID());
        Q_EMIT payPalTokenValidChanged(isPayPalTokenValid());
    }
}


bool GtConfig::isPayPalTokenValid() const
{
    return (!m_payPalToken.isEmpty() && m_payPalTokenExpiration > QDateTime::currentDateTimeUtc() && m_payPalTokenType != Geltan::PP::PayPal::NoTokenType && !m_payPalAppID.isEmpty());
}



int GtConfig::getApplicationWidth() const { return m_applicationWidth; }

void GtConfig::setApplicationWidth(int applicationWidth)
{
    if (applicationWidth != m_applicationWidth) {
        m_applicationWidth = applicationWidth;
#ifdef QT_DEBUG
        qDebug() << "Changed applicationWidth to" << m_applicationWidth;
#endif
        setValue(QStringLiteral("application/width"), m_applicationWidth);

        Q_EMIT applicationWidthChanged(getApplicationWidth());
    }
}




QString GtConfig::getPaypalReturnUrl() const { return m_paypalReturnUrl; }

void GtConfig::setPaypalReturnUrl(const QString &paypalReturnUrl)
{
    if (paypalReturnUrl != m_paypalReturnUrl) {
        m_paypalReturnUrl = paypalReturnUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed paypalReturnUrl to" << m_paypalReturnUrl;
#endif
        setValue(QStringLiteral("paypal/returnURL"), m_paypalReturnUrl);

        emit paypalReturnUrlChanged(getPaypalReturnUrl());
    }
}




QString GtConfig::getPaypalCancelUrl() const { return m_paypalCancelUrl; }

void GtConfig::setPaypalCancelUrl(const QString &paypalCancelUrl)
{
    if (paypalCancelUrl != m_paypalCancelUrl) {
        m_paypalCancelUrl = paypalCancelUrl;
#ifdef QT_DEBUG
        qDebug() << "Changed paypalCancelUrl to" << m_paypalCancelUrl;
#endif
        setValue(QStringLiteral("paypal/cancelURL"), m_paypalCancelUrl);

        emit paypalCancelUrlChanged(getPaypalCancelUrl());
    }
}
