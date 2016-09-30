/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * requestaccesstoken.h
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

#ifndef REQUESTACCESSTOKEN_H
#define REQUESTACCESSTOKEN_H

#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppbase.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {

namespace PP {

class RequestAccessTokenPrivate;


/*!
 * \brief Class to request an access token from the PayPal API.
 *
 * \headerfile "" <Geltan/PP/requestaccesstoken.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT RequestAccessToken : public PPBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(RequestAccessToken)
    /*!
     * \brief Scopes expressed in the form of resource URL endpoints.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QStringList</TD><TD>scopes() const</TD></TR><TR><TD>void</TD><TD>setScopes(const QStringList & scopes)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>scopesChanged(const QStringList & scopes)</TD></TR></TABLE>
     */
    Q_PROPERTY(QStringList scopes READ scopes NOTIFY scopesChanged)
    /*!
     * \brief The access token issued by PayPal.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>token() const</TD></TR><TR><TD>void</TD><TD>setToken(const QString & token)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>tokenChanged(const QString & token)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged)
    /*!
     * \brief The type of the token issued as described in OAuth2.0 RFC6749, Section 7.1.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::TokenType</TD><TD>tokenType() const</TD></TR><TR><TD>void</TD><TD>setTokenType(PayPal::TokenType nTokenType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>tokenTypeChanged(PayPal::TokenType tokenType)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::TokenType tokenType READ tokenType NOTIFY tokenTypeChanged)
    /*!
     * \brief The ID of the requesting App.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>appID() const</TD></TR><TR><TD>void</TD><TD>setAppID(const QString & appID)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>appIDChanged(const QString & appID)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString appID READ appID NOTIFY appIDChanged)

    /*!
     * \brief The lifetime in seconds of the access token.
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>expiresIn() const</TD></TR><TR><TD>void</TD><TD>setExpiresIn(const int & expiresIn)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>expiresInChanged(const int & expiresIn)</TD></TR></TABLE>
     */
    Q_PROPERTY(int expiresIn READ expiresIn NOTIFY expiresInChanged)
public:
    /*!
     * \brief Constructs an empty RequestAccessToken object.
     */
    explicit RequestAccessToken(QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the RequestAccessToken object.
     */
    virtual ~RequestAccessToken();

    /*!
     * \brief Inovkes the API call.
     */
    Q_INVOKABLE void call();


    QStringList scopes() const;
    QString token() const;
    PayPal::TokenType tokenType() const;
    QString appID() const;
    int expiresIn() const;

Q_SIGNALS:
    void scopesChanged(const QStringList &scopes);
    void tokenChanged(const QString &token);
    void tokenTypeChanged(PayPal::TokenType tokenType);
    void appIDChanged(const QString &appID);
    void expiresInChanged(int expiresIn);
    /*!
     * \brief This signal will be emitted when the request was successful.
     */
    void succeeded();
    /*!
     * \brief This signal will be emitted whe the request failed.
     */
    void failed();

protected:
    void successCallBack() Q_DECL_OVERRIDE;
    void errorCallBack() Q_DECL_OVERRIDE;
    bool checkInput() Q_DECL_OVERRIDE;
    bool checkOutput() Q_DECL_OVERRIDE;

    RequestAccessToken(RequestAccessTokenPrivate &dd, QObject *parent = nullptr);

private:
    /*!
     * \brief Part of the \link RequestAccessToken::scopes scopes \endlink property.
     *
     * This is set internally in the successCallBack()
     */
    void setScopes(const QStringList &scopes);

    /*!
     * \brief Part of the \link RequestAccessToken::token token \endlink property.
     *
     * This is set internally in the successCallBack()
     */
    void setToken(const QString &token);

    /*!
     * \brief Part of the \link RequestAccessToken::tokenType tokenType \endlink property.
     *
     * This is set internally in the successCallBack()
     */
    void setTokenType(PayPal::TokenType nTokenType);

    /*!
     * \brief Part of the \link RequestAccessToken::appID appID \endlink property.
     *
     * This is set internally in the successCallBack()
     */
    void setAppID(const QString &appID);

    /*!
     * \brief Part of the \link RequestAccessToken::expiresIn expiresIn \endlink property.
     *
     * This is set internally in the successCallBack()
     */
    void setExpiresIn(int expiresIn);

    Q_DISABLE_COPY(RequestAccessToken)

};

}

}

#endif // REQUESTACCESSTOKEN_H
