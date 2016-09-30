/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * item.h
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

#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QUrl>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {


class ItemPrivate;

/*!
 * \brief Contains information about a single item.
 *
 * \ppPaymentsApi{item}
 *
 * \headerfile "" <Geltan/PP/Objects/item.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT Item : public QObject
{
    Q_OBJECT
    /*!
     * \brief Stock keeping unit (SKU) corresponding to item.
     *
     * Maximum length: 127.
     *
     * \ppApiName{sku}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>sku() const</TD></TR><TR><TD>void</TD><TD>setSku(const QString &nSku)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>skuChanged(const QString &sku)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString sku READ sku WRITE setSku NOTIFY skuChanged)
    /*!
     * \brief Item name.
     *
     * 127 characters max.
     *
     * \ppApiName{name}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>name() const</TD></TR><TR><TD>void</TD><TD>setName(const QString &nName)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>nameChanged(const QString &name)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    /*!
     * \brief Description of the item.
     *
     * Only supported when the \c payment_method is set to \c paypal.
     *
     * \ppApiName{description}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>description() const</TD></TR><TR><TD>void</TD><TD>setDescription(const QString &nDescription)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>descriptionChanged(const QString &description)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    /*!
     * \brief Number of a particular item.
     *
     * \ppApiName{quantity}
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>quantity() const</TD></TR><TR><TD>void</TD><TD>setQuantity(const int &nQuantity)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>quantityChanged(const int &quantity)</TD></TR></TABLE>
     */
    Q_PROPERTY(int quantity READ quantity WRITE setQuantity NOTIFY quantityChanged)
    /*!
     * \brief Item cost.
     *
     * \ppApiName{price}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>price() const</TD></TR><TR><TD>void</TD><TD>setPrice(float nPrice)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>priceChanged(float price)</TD></TR></TABLE>
     */
    Q_PROPERTY(float price READ price WRITE setPrice NOTIFY priceChanged)
    /*!
     * \brief 3-letter currency code.
     *
     * \ppApiName{currency}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>currency() const</TD></TR><TR><TD>void</TD><TD>setCurrency(const QString &nCurrency)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>currencyChanged(const QString &currency)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString currency READ currency WRITE setCurrency NOTIFY currencyChanged)
    /*!
     * \brief Tax of the item.
     *
     * Only supported when the \c payment_method is set to \c paypal.
     *
     * \ppApiName{tax}
     *
     * \par Access functions:
     * <TABLE><TR><TD>float</TD><TD>tax() const</TD></TR><TR><TD>void</TD><TD>setTax(float nTax)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>taxChanged(float tax)</TD></TR></TABLE>
     */
    Q_PROPERTY(float tax READ tax WRITE setTax NOTIFY taxChanged)
    /*!
     * \brief URL linking to item information.
     *
     * \ppApiName{url}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QUrl</TD><TD>url() const</TD></TR><TR><TD>void</TD><TD>setUrl(const QUrl &nUrl)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>urlChanged(const QUrl &url)</TD></TR></TABLE>
     */
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
public:
    /*!
     * \brief Constructs a new empty Item object.
     */
    explicit Item(QObject *parent = nullptr);

    /*!
     * \brief Clones \a other Item.
     *
     * Creates a new Item object that gets its values from \a other.
     */
    Item(Item *other, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Item object from JSON data.
     */
    Item(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Item object from JSON data.
     */
    Item(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the Item object.
     */
    ~Item();

    QString sku() const;
    QString name() const;
    QString description() const;
    int quantity() const;
    float price() const;
    QString currency() const;
    float tax() const;
    QUrl url() const;


    void setSku(const QString &nSku);
    void setName(const QString &nName);
    void setDescription(const QString &nDescription);
    void setQuantity(int nQuantity);
    void setPrice(float nPrice);
    void setCurrency(const QString &nCurrency);
    void setTax(float nTax);
    void setUrl(const QUrl &nUrl);


    /*!
     * \brief Returns a QVariantMap containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API.
     */
    QVariantMap toVariant();

    /*!
     * \brief Returns a QJsonObject containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API.
     */
    QJsonObject toJsonObject();

    /*!
     * \brief Loads data from a QJsonDocument into the Item object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Item object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void skuChanged(const QString &sku);
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);
    void quantityChanged(int quantity);
    void priceChanged(float price);
    void currencyChanged(const QString &currency);
    void taxChanged(float tax);
    void urlChanged(const QUrl &url);

protected:
    const QScopedPointer<ItemPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Item)
    Q_DECLARE_PRIVATE(Item)

};

}
}


#endif // ITEM_H
