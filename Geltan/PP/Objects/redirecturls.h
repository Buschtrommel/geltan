/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * redirecturls.h
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

#ifndef REDIRECTURLS_H
#define REDIRECTURLS_H

#include <QObject>
#include <QUrl>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class RedirectUrlsPrivate;

/*!
 * \brief Set of redirect URLs you provide only for PayPal-based payments.
 *
 * \ppPaymentsApi{redirect_urls}
 *
 * \headerfile "" <Geltan/PP/Objects/redirecturls.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-09
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT RedirectUrls : public QObject
{
    Q_OBJECT
    /*!
     * \brief Url where the payer would be redirected to after approving the payment.
     *
     * \ppApiName{return_url}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QUrl</TD><TD>returnUrl() const</TD></TR><TR><TD>void</TD><TD>setReturnUrl(const QUrl &nReturnUrl)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>returnUrlChanged(const QUrl &returnUrl)</TD></TR></TABLE>
     */
    Q_PROPERTY(QUrl returnUrl READ returnUrl WRITE setReturnUrl NOTIFY returnUrlChanged)
    /*!
     * \brief Url where the payer would be redirected to after canceling the payment.
     *
     * \ppApiName{cancel_url}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QUrl</TD><TD>cancelUrl() const</TD></TR><TR><TD>void</TD><TD>setCancelUrl(const QUrl &nCancelUrl)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>cancelUrlChanged(const QUrl &cancelUrl)</TD></TR></TABLE>
     */
    Q_PROPERTY(QUrl cancelUrl READ cancelUrl WRITE setCancelUrl NOTIFY cancelUrlChanged)
public:
    /*!
     * \brief Constructs a new empty RedirectUrls object.
     */
    explicit RedirectUrls(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new RedirectUrls object with the given URLs.
     */
    RedirectUrls(const QUrl &returnUrl, const QUrl &cancelUrl, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new RedirectUrls object from JSON data.
     */
    RedirectUrls(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new RedirectUrls object from JSON data.
     */
    RedirectUrls(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the RedirectUrls object.
     */
    ~RedirectUrls();

    QUrl returnUrl() const;
    QUrl cancelUrl() const;

    void setReturnUrl(const QUrl &nReturnUrl);
    void setCancelUrl(const QUrl &nCancelUrl);

    /*!
     * \brief Returns a QVariantMap containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API.
     */
    QVariantMap toVariant() const;

    /*!
     * \brief Returns a QJsonObject containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API.
     */
    QJsonObject toJsonObject() const;


    /*!
     * \brief Returns true, if both URLs are valid.
     */
    bool isValid() const;

    /*!
     * \brief Loads data from a QJsonDocument into the RedirectUrls object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the RedirectUrls object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void returnUrlChanged(const QUrl &returnUrl);
    void cancelUrlChanged(const QUrl &cancelUrl);

protected:
    const QScopedPointer<RedirectUrlsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(RedirectUrls)
    Q_DECLARE_PRIVATE(RedirectUrls)

};

}
}


#endif // REDIRECTURLS_H
