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

#ifndef AUTHENTICATIONTEST_H
#define AUTHENTICATIONTEST_H

#include <QObject>
#include "../gtconfig.h"
#include <Geltan/PP/requestaccesstoken.h>

namespace GeltanTest {

class AuthenticationTest : public Geltan::PP::RequestAccessToken
{
    Q_OBJECT

    /*!
     * \brief Pointer to a GtConfig object.
     *
     * \par Access functions:
     * <TABLE><TR><TD>GtConfig*</TD><TD>getConfiguration() const</TD></TR><TR><TD>void</TD><TD>setConfiguration(GtConfig * configuration)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>configurationChanged(GtConfig * configuration)</TD></TR></TABLE>
     */
    Q_PROPERTY(GtConfig *configuration READ getConfiguration WRITE setConfiguration NOTIFY configurationChanged)
public:
    /*!
     * \brief Constructs an empty AuthenticationTest.
     */
    explicit AuthenticationTest(QObject *parent = nullptr);

    ~AuthenticationTest();

    Q_INVOKABLE void requestToken();


    /*!
     * \brief Returns a pointer to the currently set GtConfig object.
     *
     * Part of the \link AuthenticationTest::configuration configuration \endlink property.
     */
    GtConfig *getConfiguration() const;

    /*!
     * \brief Set the pointer to the GtConfig object.
     *
     * Part of the \link AuthenticationTest::configuration configuration \endlink property.
     */
    void setConfiguration(GtConfig *configuration);


Q_SIGNALS:
    /*!
     * \brief Emitted if the pointer to the GtConfig configuration object changes.
     *
     * Part of the \link AuthenticationTest::configuration configuration \endlink property.
     */
    void configurationChanged(GtConfig *configuration);

protected:
    void successCallBack() Q_DECL_OVERRIDE;

private:
    GtConfig *m_configuration;

};

}

#endif // AUTHENTICATIONTEST_H
