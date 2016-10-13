/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Payments/list.h
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

#ifndef LISTPAYMENTS_H
#define LISTPAYMENTS_H

#include "../ppbase.h"
#include <QDateTime>

namespace Geltan {
namespace PP {

class PaymentList;

namespace Payments {

class ListPrivate;

/*!
 * \brief Requests a list of Payment objects from the API.
 *
 * Lists payments that were created by the Geltan::PP::Payments::Create call and are in any state.
 * The list shows the payments that are made to the merchant who makes the call.
 *
 * \headerfile "" <Geltan/PP/Payments/list.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-10-06
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT List : public PPBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(List)
    /*!
     * \brief The number of items to list in the response. The default is \a 10.
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>count() const</TD></TR><TR><TD>void</TD><TD>setCount(int nCount)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>countChanged(int count)</TD></TR></TABLE>
     */
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    /*!
     * \brief The ID of the starting resource in the response.
     *
     * When results are paged, you can use the nextId value as the startId to continue with the next set of results.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>startId() const</TD></TR><TR><TD>void</TD><TD>setStartId(const QString &nStartId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>startIdChanged(const QString &startId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString startId READ startId WRITE setStartId NOTIFY startIdChanged)
    /*!
     * \brief The start index of the resource to return.
     *
     * Typically used to jump to a specific position in the resource history based on its cart.
     *
     * \par Access functions:
     * <TABLE><TR><TD>int</TD><TD>startIndex() const</TD></TR><TR><TD>void</TD><TD>setStartIndex(int nStartIndex)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>startIndexChanged(int startIndex)</TD></TR></TABLE>
     */
    Q_PROPERTY(int startIndex READ startIndex WRITE setStartIndex NOTIFY startIndexChanged)
    /*!
     * \brief The date and time when the resource was created.
     *
     * Indicates the start of a range of results.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>startTime() const</TD></TR><TR><TD>void</TD><TD>setStartTime(const QDateTime &nStartTime)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>startTimeChanged(const QDateTime &startTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    /*!
     * \brief The date and time when the resource was created.
     *
     * Indicates the end of a range of results.
     *
     * \par Access functions:
     * <TABLE><TR><TD>QDateTime</TD><TD>endTime() const</TD></TR><TR><TD>void</TD><TD>setEndTime(const QDateTime &nEndTime)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>endTimeChanged(const QDateTime &endTime)</TD></TR></TABLE>
     */
    Q_PROPERTY(QDateTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
    /*!
     * \brief The value the results should be sorted by.
     *
     * Possible values \c update_time and \c create_time. Default: \c update_time
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>sortBy() const</TD></TR><TR><TD>void</TD><TD>setSortBy(const QString &nSortBy)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>sortByChanged(const QString &sortBy)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString sortBy READ sortBy WRITE setSortBy NOTIFY sortByChanged)
    /*!
     * \brief The way the results are sorted.
     *
     * Default: Qt::AscendingOrder
     *
     * \par Access functions:
     * <TABLE><TR><TD>Qt::SortOrder</TD><TD>sortOrder() const</TD></TR><TR><TD>void</TD><TD>setSortOrder(const Qt::SortOrder &nSortOrder)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>sortOrderChanged(const Qt::SortOrder &sortOrder)</TD></TR></TABLE>
     */
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    /*!
     * \brief The list that contains the replied payments.
     *
     * \par Access functions:
     * <TABLE><TR><TD>PaymentList*</TD><TD>paymentList() const</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentListChanged(PaymentList *paymentList)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PaymentList *paymentList READ paymentList NOTIFY paymentListChanged)
    /*!
     * \brief If set to true, new Payment items will be appended to the paymentList.
     *
     * If set to false, the content of the model will be replaced by the new entries. The default is \a false.
     *
     * \par Access functions:
     * <TABLE><TR><TD>bool</TD><TD>append() const</TD></TR><TR><TD>void</TD><TD>setAppend(bool nAppend)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>appendChanged(bool append)</TD></TR></TABLE>
     */
    Q_PROPERTY(bool append READ append WRITE setAppend NOTIFY appendChanged)
public:
    /*!
     * \brief Constructs a new List object.
     */
    List(QObject *parent = nullptr);

    /*!
     * \brief Invokes the API call.
     */
    Q_INVOKABLE void call();

    /*!
     * \brief Invokes the API call.
     * \overload
     */
    Q_INVOKABLE void call(int count, const QString &startId, int startIndex, const QDateTime &startTime, const QDateTime &endTime, const QString &sortBy, Qt::SortOrder sortOrder);


    int count() const;
    QString startId() const;
    int startIndex() const;
    QDateTime startTime() const;
    QDateTime endTime() const;
    QString sortBy() const;
    Qt::SortOrder sortOrder() const;
    PaymentList *paymentList() const;
    bool append() const;

    void setCount(int nCount);
    void setStartId(const QString &nStartId);
    void setStartIndex(int nStartIndex);
    void setStartTime(const QDateTime &nStartTime);
    void setEndTime(const QDateTime &nEndTime);
    void setSortBy(const QString &nSortBy);
    void setSortOrder(const Qt::SortOrder &nSortOrder);
    void setAppend(bool nAppend);

Q_SIGNALS:
    /*!
     * \brief This signal will be emitted when the request was successful.
     */
    void succeeded();

    /*!
     * \brief This signal will be emitted when the request failed.
     */
    void failed();

    void countChanged(int count);
    void startIdChanged(const QString &startId);
    void startIndexChanged(int startIndex);
    void startTimeChanged(const QDateTime &startTime);
    void endTimeChanged(const QDateTime &endTime);
    void sortByChanged(const QString &sortBy);
    void sortOrderChanged(const Qt::SortOrder &sortOrder);
    void paymentListChanged(PaymentList *paymentList);
    void appendChanged(bool append);


protected:
    void successCallBack() Q_DECL_OVERRIDE;
    void errorCallBack() Q_DECL_OVERRIDE;
    bool checkInput() Q_DECL_OVERRIDE;
    bool checkOutput() Q_DECL_OVERRIDE;

    List(ListPrivate &dd, QObject *parent = nullptr);

private:
    Q_DISABLE_COPY(List)
};

}
}
}

#endif // LISTPAYMENTS_H
