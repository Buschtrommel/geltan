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
