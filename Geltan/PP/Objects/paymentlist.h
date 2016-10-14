/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/paymentlist.h
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

#ifndef PAYMENTLIST_H
#define PAYMENTLIST_H

#include <QAbstractListModel>
#include "payment.h"
#include "../../geltan_global.h"

class QJsonDocument;
class QJsonObject;

namespace Geltan {
namespace PP {

class PaymentListPrivate;

/*!
 * \brief Model containing a list of Payment objects.
 *
 * \headerfile "" <Geltan/PP/Objects/paymentlist.h>
 */
class GELTANSHARED_EXPORT PaymentList : public QAbstractListModel
{
    Q_OBJECT
    /*!
     * \brief Contains a list of Payment objects.
     *
     * The single Payment objects are also accessible by the methods of the QAbstractListModel.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<Payment*></TD><TD>payments() const</TD></TR><TR><TD>void</TD><TD>setPayments(const QList<Payment*> &nPayments)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentsChanged(const QList<Payment*> &payments)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Payment*> payments READ payments NOTIFY paymentsChanged)
    /*!
     * \brief Number of items returned in each range of results.
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>count() const</TD></TR><TR><TD>void</TD><TD>setCount(int nCount)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>countChanged(int count)</TD></TR></TABLE>
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    /*!
     * \brief Identifier of the next element to get the next range of results.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>nextId() const</TD></TR><TR><TD>void</TD><TD>setNextId(const QString &nNextId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>nextIdChanged(const QString &nextId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString nextId READ nextId NOTIFY nextIdChanged)
public:
    /*!
     * \brief Constructs a new PaymentList model.
     */
    explicit PaymentList(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Transaction object from JSON data.
     */
    PaymentList(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Transaction object from JSON data.
     */
    PaymentList(const QJsonObject &json, QObject * parent = nullptr);

    /*!
     * \brief Deconstructs the PaymentList model.
     */
    ~PaymentList();

    /*!
     * \brief The roles of this model.
     *
     * To access them from QML, use the enumeration name starting lowercase.
     */
    enum Roles {
        Item = Qt::UserRole + 1,    /**< Pointer to the complete Payment object. */
        Id,                         /**< The ID of the Payment. */
        CreateTime,                 /**< The creation time of the Payment. */
        UpdateTime,                 /**< The time the Payment has been last updated. */
        State,                      /**< The state of the Payment. */
        Intent,                     /**< The intent of the Payment. */
        Payer                       /**< Pointer to the Payer object of the Payment. */
    };

    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractListModel.
     */
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /*!
     * \brief Reimplemented from QAbstractItemModel.
     */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;



    QList<Payment*> payments() const;
    int count() const;
    QString nextId() const;

    void setPayments(const QList<Payment*> &nPayments);
    void setCount(int nCount);
    void setNextId(const QString &nNextId);

    /*!
     * \brief Loads data from a QJsonDocument into the Transaction object.
     *
     * If \c append is set to true, the loaded Payment items will be appended
     * to the model list, otherwise the current content will be replaced.
     */
    void loadFromJson(const QJsonDocument &json, bool append = false);

    /*!
     * \brief Loads data from a QJsonArray into the Transaction object.
     *
     * If \c append is set to true, the loaded Payment items will be appended
     * to the model list, otherwise the current content will be replaced.
     */
    void loadFromJson(const QJsonObject &json, bool append = false);

Q_SIGNALS:
    void paymentsChanged(const QList<Payment*> &payments);
    void countChanged(int count);
    void nextIdChanged(const QString &nextId);


protected:
    const QScopedPointer<PaymentListPrivate> d_ptr;

private:
    Q_DISABLE_COPY(PaymentList)
    Q_DECLARE_PRIVATE(PaymentList)

};

}
}

#endif // PAYMENTLIST_H
