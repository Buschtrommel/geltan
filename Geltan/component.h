/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/component.h
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

#ifndef COMPONENT_H
#define COMPONENT_H

#include <Geltan/geltan_global.h>

#include <QtCore/qobject.h>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qauthenticator.h>
#include <QtNetwork/qsslerror.h>
#include <QtCore/qurl.h>
#include <QtCore/qurlquery.h>

#include <Geltan/error.h>

namespace Geltan {

class ComponentPrivate;


/*!
 * \brief Base class for all API requests.
 *
 * \headerfile "" <Geltan/component.h>
 */
class GELTANSHARED_EXPORT Component : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Component)
    /*!
     * \brief Define a custom QNetworkAccessManager to perform network operations.
     *
     * When no custom QNetworkAccessManager is set, a new one will be created when sending the API
     * request via sendRequest(). The internal created network manager will be a child object of
     * this class. If you set your own custom QNetworkAccessManager, this will not automatically be
     * a child object of this class.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QNetworkAccessManager*</TD><TD>networkAccessManager() const</TD></TR><TR><TD>void</TD><TD>setNetworkAccessManager(QNetworkAccessManager * networkAccessManager)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>networkAccessManagerChanged(QNetworkAccessManager * networkAccessManager)</TD></TR></TABLE>
     */
    Q_PROPERTY(QNetworkAccessManager *networkAccessManager READ networkAccessManager WRITE setNetworkAccessManager NOTIFY networkAccessManagerChanged)
    /*!
     * \brief Returns true while the request is in operation.
     *
     * \par Access functions:
     * <TABLE><TR><TD>bool</TD><TD>inOperation() const</TD></TR><TR><TD>void</TD><TD>setInOperation(bool nInOperation)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>inOperationChanged(bool inOperation)</TD></TR></TABLE>
     */
    Q_PROPERTY(bool inOperation READ inOperation NOTIFY inOperationChanged)
    /*!
     * \brief Timeout in seconds for network requests.
     *
     * If you set the timeout to 0 or lower, it wil be disabled.
     *
     * Default value: 60 seconds
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>requestTimeout() const</TD></TR><TR><TD>void</TD><TD>setRequestTimeout(int nRequestTimeout)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>requestTimeoutChanged(int requestTimeout)</TD></TR></TABLE>
     */
    Q_PROPERTY(int requestTimeout READ requestTimeout WRITE setRequestTimeout NOTIFY requestTimeoutChanged)
    /*!
     * \brief Pointer to an error object if any error occured.
     *
     * If no error occured, it will return a \c nullptr. The error is set internally by setError().
     *
     * \par Access functions:
     * <TABLE><TR><TD>Error*</TD><TD>error() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>errorChanged(Error *error)</TD></TR></TABLE>
     */
    Q_PROPERTY(Error *error READ error NOTIFY errorChanged)
public:
    /*!
     * \brief Constructs a new Component
     */
    Component(QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Component
     */
    ~Component();


    QNetworkAccessManager* networkAccessManager() const;
    void setNetworkAccessManager(QNetworkAccessManager *networkAccessManager);

    bool inOperation() const;

    int requestTimeout() const;
    void setRequestTimeout(int nRequestTimeout);

    /*!
     * \brief Returns the currently set QNetworkAccessManager::Operation
     *
     * Default is QNetworkAccessManager::GetOperation
     *
     * \sa setNetworkOperation()
     */
    QNetworkAccessManager::Operation networkOperation() const;


    /*!
     * \brief Returns the currently set API URL.
     *
     * \sa setApiUrl();
     */
    QUrl apiUrl() const;

    /*!
     * \brief Returns the currently set API path.
     *
     * \sa setApiPath()
     */
    QString apiPath() const;

    /*!
     * \brief Returns the currently set HTTP request headers.
     *
     * \sa setRequestHeaders()
     */
    QHash<QByteArray, QByteArray> requestHeaders() const;

    /*!
     * \brief Returns the currently set payload to send with the request.
     *
     * \sa setPayload()
     */
    QByteArray payload() const;


    /*!
     * \brief Returns the current Error
     */
    Error* error() const;


    /*!
     * \brief Returns the currently set values for the url query.
     *
     * \sa setUrlQuery()
     */
    QUrlQuery urlQuery() const;


Q_SIGNALS:
    void networkAccessManagerChanged(QNetworkAccessManager *networkAccessManager);
    void inOperationChanged(bool inOperation);
    void requestTimeoutChanged(int requestTimeout);
    void errorChanged(Error *error);

protected:
    /*!
     * \brief Sets the QNetworkAccessManager::Operation to perform.
     *
     * By default a QNetworkAccessManager::GetOperation is performed.
     *
     * \sa networkOperation()
     */
    void setNetworkOperation(QNetworkAccessManager::Operation operation);

    /*!
     * \brief Part of the \link Component::inOperation inOperation \endlink property.
     */
    void setInOperation(bool nInOperation);

    /*!
     * \brief Sets the API URL to use. Should be the domain part of the URL.
     *
     * \sa apiUrl()
     */
    void setApiUrl(const QUrl &url);

    /*!
     * \brief Sets the API path to use.
     *
     * \sa apiPath()
     */
    void setApiPath(const QString &path);

    /*!
     * \brief Sets the headers to use in the request.
     *
     * The \a key is used as header name, the \a value as header value.
     *
     * \sa requestHeaders()
     */
    void setRequestHeaders(const QHash<QByteArray, QByteArray> &headers);

    /*!
     * \brief Adds a single header to the dictionary of request headers.
     *
     * If there is already a header with \a headerName, it's value will be replaced by \a headerValue.
     */
    void addRequestHeader(const QByteArray &headerName, const QByteArray &headerValue);

    /*!
     * \brief Adds the headers defined in \a headers to the dictionary of request headers.
     *
     * The \a key is used as header name, the \a value as header value. If ther is alread a header
     * with a name like \a key, it's value will be replaced by the key's \a value.
     *
     * \sa addRequestHeader(), setRequestHeaders()
     */
    void addRequestHeaders(const QHash<QByteArray, QByteArray> &headers);

    /*!
     * \brief Sets the payload data to send with the request.
     *
     * \sa payload()
     */
    void setPayload(const QByteArray &nPayload);

    /*!
     * \overload
     */
    void setPayload(const QString &nPayload);

    /*!
     * \brief Sets a new Error if one occured.
     *
     * \sa error()
     */
    void setError(Error *nError);


    /*!
     * \brief Sets the values used as url query.
     *
     * \sa urlQuery()
     */
    void setUrlQuery(const QUrlQuery &query);


    /*!
     * \overload
     */
    void setUrlQuery(const QList<QPair<QString, QString> > &queryItems);


    /*!
     * \brief Adds a new item to the url query.
     *
     * \sa setUrlQuery(), setUrlQueryItems()
     */
    void addUrlQueryItem(const QString &key, const QString &value);


    /*!
     * \overload
     */
    void addUrlQueryItem(const QPair<QString, QString> &queryItem);


    /*!
     * \brief Adds multiple new items to the url query.
     *
     * \sa setUrlQuery(), setUrlQueryItem()
     */
    void addUrlQueryItems(const QList<QPair<QString, QString> > &queryItems);


    /*!
     * \brief Sets the characters used for delimiting between keys and values, and between key-value pairs in the URL's query string.
     *
     * \sa QuerlQuery::setQueryDelimeters()
     */
    void setUrlQueryDelimeters(QChar valueDelimeter, QChar pairDelimeter);


    /*!
     * \brief Sets the value for the Authentication Header.
     */
    void setAuth(const QString &nAuth);


    /*!
     * \brief Returns the currently set value for the Authentication Header.
     */
    QString auth() const;


    /*!
     * \brief Returns the result data of the request, the content of the QNetworkReply.
     */
    QByteArray result() const;


    /*!
     * \brief Sends a request to the API.
     *
     * The request is defined by setApiUrl(), setApiPath(), setRequestHeaders(), setUrlQuery() and setPayload().
     */
    void sendRequest();


    /*!
     * \overload
     */
    void sendRequest(const QUrl &url, const QString &path, const QHash<QByteArray, QByteArray> &headers, const QUrlQuery &query = QUrlQuery(), const QByteArray &payLoad = QByteArray());


    /*!
     * \brief successCallBack
     */
    virtual void successCallBack() = 0;

    /*!
     * \brief errorCallBack
     */
    virtual void errorCallBack() = 0;

    /*!
     * \brief extractError
     */
    virtual void extractError(QNetworkReply *reply) = 0;

    /*!
     * \brief Returns true if the given input data is valid.
     *
     * Reimplement this in a subclass. The default implementation always returns true.
     */
    virtual bool checkInput();

    /*!
     * \brief Returns true if the reply data is valid.
     *
     * Reimplement this in a subclass. The default implementation always returns true.
     */
    virtual bool checkOutput();

    const QScopedPointer<ComponentPrivate> d_ptr;
    Component(ComponentPrivate &dd, QObject *parent = nullptr);

private Q_SLOTS:
    /*!
     * \brief Receives the QNetworkAccessManager::finished() signal and does first error checks.
     */
    void _q_requestFinished();

    /*!
     * \brief Receives the QTimer::timeout() signal from the request timeout timer.
     */
    void _q_requestTimedOut();


private:
    Q_DISABLE_COPY(Component)
};

}

#endif // COMPONENT_H
