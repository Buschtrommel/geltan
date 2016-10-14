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
