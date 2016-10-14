/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/PP/authenticationtest.cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "authenticationtest.h"
#include <QDateTime>

#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace GeltanTest;

AuthenticationTest::AuthenticationTest(QObject *parent) :
    Geltan::PP::RequestAccessToken(parent)
{
    m_configuration = nullptr;
}


AuthenticationTest::~AuthenticationTest()
{

}


void AuthenticationTest::requestToken()
{
    if (!m_configuration) {
        return;
    }

    this->setClientID(m_configuration->getPayPalClientID());
    this->setSecret(m_configuration->getPayPalSecret());

    this->call();
}


GtConfig *AuthenticationTest::getConfiguration() const { return m_configuration; }


void AuthenticationTest::setConfiguration(GtConfig * configuration)
{
    if (configuration != m_configuration) {
        m_configuration = configuration;
#ifdef QT_DEBUG
        qDebug() << "Changed configuration to" << m_configuration;
#endif
        Q_EMIT configurationChanged(getConfiguration());
    }
}



void AuthenticationTest::successCallBack()
{
    RequestAccessToken::successCallBack();

    if (m_configuration) {
        m_configuration->setPayPalTokenExpiration(QDateTime::currentDateTimeUtc().addSecs(expiresIn() - 60));
        m_configuration->setPayPalToken(token());
        m_configuration->setPayPalTokenType(tokenType());
        m_configuration->setPayPalAppID(appID());
    }
}
