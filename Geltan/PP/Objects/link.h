/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/link.h
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

#ifndef LINK_H
#define LINK_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <QUrl>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class LinkPrivate;

/*!
 * \brief Contains information about a PayPal <a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> API link.
 *
 * \ppPaymentsApi{link}
 *
 * \headerfile "" <Geltan/PP/Objects/link.h>
 */
class GELTANSHARED_EXPORT Link : public QObject
{
    Q_OBJECT
    /*!
     * \brief URL of the related <a href="https://en.wikipedia.org/wiki/HATEOAS">HATEOAS</a> link you can use for subsequent calls
     *
     * \ppApiName{href}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QUrl</TD><TD>href() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>hrefChanged(const QUrl &href)</TD></TR></TABLE>
     */
    Q_PROPERTY(QUrl href READ href NOTIFY hrefChanged)
    /*!
     * \brief Link relation that describes how this link relates to the previous call.
     *
     * Examples include self (get details of the current call), parent_payment (get details of the parent payment), 
     * or a related call such as execute or refund.
     *
     * \ppApiName{rel}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>rel() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>relChanged(const QString &rel)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString rel READ rel NOTIFY relChanged)
    /*!
     * \brief The HTTP method required for the related call.
     *
     * \ppApiName{method}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QNetworkAccessManager::Operation</TD><TD>method() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>methodChanged(QNetworkAccessManager::Operation method)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::Link::MethodType method READ method NOTIFY methodChanged)
public:
    /*!
     * \brief Constructs a new empty Link object.
     */
    explicit Link(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Link object from JSON data.
     */
    Link(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Link object from JSON data.
     */
    Link(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Link object.
     */
    ~Link();

    /*!
     * \brief HTTP method required for the link.
     */
    enum MethodType {
        Undefined   = 0,    /**< The method is undefined. Should not happen. */
        Get         = 1,    /**< A GET has to be used to request the information. */
        Redirect    = 2,    /**< Redirect links lead the user to another website. */
        Post        = 3     /**< A POST has to be used to set/update the information. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(MethodType)
#else
    Q_ENUMS(MethodType)
#endif


    QUrl href() const;
    QString rel() const;
    MethodType method() const;


    /*!
     * \brief Loads data from a QJsonDocument into the Link object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Link object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void hrefChanged(const QUrl &href);
    void relChanged(const QString &rel);
    void methodChanged(MethodType method);


protected:
    const QScopedPointer<LinkPrivate> d_ptr;


private:
    Q_DISABLE_COPY(Link)
    Q_DECLARE_PRIVATE(Link)

};

}
}
#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::Link::MethodType)
#endif

#endif // LINK_H
