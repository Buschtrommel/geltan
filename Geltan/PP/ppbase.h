/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * ppbase.h
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

#ifndef PPBASE_H
#define PPBASE_H

#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>
#include <Geltan/component.h>


namespace Geltan {

namespace PP {

class PPBasePrivate;


/*!
 * \brief Base class for PayPal API operations.
 *
 * Provides basic functionalities to send requests to the PayPal API.
 *
 * \headerfile "" <Geltan/PP/ppbase.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT PPBase : public Component
{
    Q_OBJECT
    /*!
     * \brief Sets the PayPal token.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>token() const</TD></TR><TR><TD>void</TD><TD>setToken(const QString &nToken)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString token READ token WRITE setToken)
    /*!
     * \brief Sets the type of the PayPal token.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::TokenType</TD><TD>tokenType() const</TD></TR><TR><TD>void</TD><TD>setTokenType(PayPal::TokenType nTokenType)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::TokenType tokenType READ tokenType WRITE setTokenType)
public:
    /*!
     * \brief Constructs a new PPBase object.
     */
    explicit PPBase(QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the PPBase object.
     */
    ~PPBase();

    /*!
     * \brief The ExpectedJSONType enum
     */
    enum ExpectedJSONType {
        Empty   = 0,
        Array   = 1,
        Object  = 2
    };

    /*!
     * \brief Sets the PayPal App Client ID.
     *
     * \sa clientID()
     */
    void setClientID(const QString &id);

    /*!
     * \brief Return the currently set PayPal App Client ID.
     *
     * \sa setClientID()
     */
    QString clientID() const;

    /*!
     * \brief Sets the PayPal App Secret.
     *
     * \sa secret()
     */
    void setSecret(const QString &sec);

    /*!
     * \brief Returns the currently set PayPal App Secret.
     *
     * \sa setSecret()
     */
    QString secret() const;

    /*!
     * \brief Sets the authentication token.
     *
     * \sa token()
     */
    void setToken(const QString &t);

    /*!
     * \brief Returns the currently set authentication token.
     *
     * \sa setToken()
     */
    QString token() const;

    /*!
     * \brief Sets the type of the PayPal token.
     *
     * \sa tokenType()
     */
    void setTokenType(PayPal::TokenType nTokenType);

    /*!
     * \brief Returns the currently set type of the PayPal token.
     *
     * \sa setTokenType()
     */
    PayPal::TokenType tokenType() const;

protected:
    /*!
     * \brief Generates the value for the authentication header.
     *
     * If no token is specified, cliendID and secret are used to build it.
     */
    void setAuthentication();

    /*!
     * \brief Extracts error data returned by the PayPal API.
     */
    void extractError(QNetworkReply *reply) Q_DECL_OVERRIDE;

    /*!
     * \brief Performs basic checks on the returned request data.
     *
     * \note This will at first set the jsonResult().
     *
     * This only checks if the returned data is a valid JSON document and if it contains the expected
     * JSON type. If not, it returns false and creates a new Error of type Error::JSONParsingError.
     * You can set the expected JSON type via setExpectedType().
     *
     * If you create a subclass and reimplement this method, you can call this class' method to
     * perform this basic check and than do your own checks if it returns true.
     *
     * \code{.cpp}
     * bool MySubClass::checkOutput()
     * {
     *      if (PPBase::checkOutput()) {
     *          // my extra checks
     *      } else {
     *          return false;
     *      }
     * }
     * \endcode
     *
     * \sa setExpectedType()
     */
    bool checkOutput() Q_DECL_OVERRIDE;

    /*!
     * \brief Returns the current API reply data as JSON document.
     *
     * \sa setJsonResult()
     */
    QJsonDocument jsonResult() const;

    /*!
     * \brief Sets the API reply JSON document data from the return value of result().
     *
     * \sa jsonResult()
     */
    void setJsonResult();

    /*!
     * \brief Sets the API reply JSON document data.
     *
     * \sa jsonResult()
     */
    void setJsonResult(const QJsonDocument &nJsonResult);

    /*!
     * \brief Sets the API reply JSON docment data from the network reply data.
     *
     * \sa jsonResult()
     */
    void setJsonResult(const QByteArray &nJsonResult);

    /*!
     * \brief Sets the expected JSON type of the result data.
     *
     * This is used to perform the checks in checkOutput(). The default type
     * is PPBase::Empty.
     *
     * \sa expectedType(), checkOutput()
     */
    void setExpectedType(ExpectedJSONType t);

    /*!
     * \brief Returns the currently set expected JSON type.
     *
     * \sa setExpectedType(), checkOutput()
     */
    ExpectedJSONType expectedType() const;

    PPBase(PPBasePrivate &dd, QObject *parent = nullptr);


private:
    Q_DECLARE_PRIVATE(PPBase)
    Q_DISABLE_COPY(PPBase)
};

}

}

#endif // PPBASE_H
