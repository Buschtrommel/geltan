/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * error.h
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

#ifndef ERROR_H
#define ERROR_H

#include <Geltan/geltan_global.h>

#include <QtCore/qobject.h>
#include <QtCore/qstring.h>

class QNetworkReply;

namespace Geltan {

class ErrorPrivate;


/*!
 * \brief Contains information about occured errors.
 *
 * \headerfile "" <Geltan/error.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Error : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Error)
    /*!
     * \brief Text describing the error in a human readable way.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>text() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>textChanged(const QString &text)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    /*!
     * \brief Type of the error.
     *
     * \par Access functions:
     * <TABLE><TR><TD>ErrorType</TD><TD>type() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>typeChanged(ErrorType type)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::Error::ErrorType type READ type NOTIFY typeChanged)
    /*!
     * \brief Additional error data.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>data() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>dataChanged(const QString &data)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString data READ data NOTIFY dataChanged)
    /*!
     * \brief The severity of the error.
     *
     * \par Access functions:
     * <TABLE><TR><TD>ErrorSeverity</TD><TD>severity() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>severityChanged(ErrorSeverity severity)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::Error::ErrorSeverity severity READ severity NOTIFY severityChanged)
public:
    /*!
     * \brief Defines the error type.
     */
    enum ErrorType {
        NoError,            /**< No error has occured. */
        RequestError,       /**< The request was not setup correctly. */
        JSONParsingError,   /**< Failed to parse JSON data. */
        InputError,         /**< An error occured while providing data to the library methods. */
        OutputError         /**< An error occured while processing the returned data from the API. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(ErrorType)
#else
    Q_ENUMS(ErrorType)
#endif

    /*!
     * \brief Defines the severity of the error.
     */
    enum ErrorSeverity {
        Nothing,            /**< No error has occured */
        Warning,            /**< Only a warning, but operation was perfmormed */
        Critical,           /**< A critical error has occured, the operation has been canceled */
        Fatal               /**< A fatal error has occured, the application has been exited */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(ErrorSeverity)
#else
    Q_ENUMS(ErrorSeverity)
#endif

    /*!
     * \brief Creates an empty Error of type NoError
     */
    explicit Error(QObject *parent = nullptr);

    /*!
     * \overload
     */
    Error(ErrorType errorType, const QString &errorText, ErrorSeverity errorSeverity, const QString &errorData = QString(), QObject *parent = nullptr);

    /*!
     * \overload
     */
    Error(QNetworkReply *networkRepy, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs Error
     */
    ~Error();


    /*!
     * \brief Returns a human readbale error text if one was set.
     * \sa setText()
     */
    QString text() const;

    /*!
     * \brief Sets a human readable error text.
     */
    void setText(const QString &nText);


    /*!
     * \brief Returns the type of this error.
     */
    ErrorType type() const;

    /*!
     * \brief Sets the type of this error.
     */
    void setType(ErrorType nType);

    /*!
     * \brief Returns additional data for the error like payload or URL values.
     */
    QString data() const;

    /*!
     * \brief Sets additional data for the error.
     */
    void setData(const QString &errorData);

    /*!
     * \brief Returns the severity of the error.
     */
    ErrorSeverity severity() const;

    /*!
     * \brief Sets the severity of the error.
     */
    void setSeverity(ErrorSeverity nSeverity);

    /*!
     * \brief Resets the error to a NoError state.
     */
    void reset();


Q_SIGNALS:
    void textChanged(const QString &text);
    void typeChanged(ErrorType type);
    void dataChanged(const QString &data);
    void severityChanged(ErrorSeverity severity);


protected:
    const QScopedPointer<ErrorPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Error)
};

}

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::Error::ErrorSeverity)
Q_DECLARE_METATYPE(Geltan::Error::ErrorType)
#endif

#endif // ERROR_H
