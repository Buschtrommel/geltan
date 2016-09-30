/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * installmentoptions.h
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

#ifndef INSTALLMENTOPTIONS_H
#define INSTALLMENTOPTIONS_H

#include <QObject>
#include <QAbstractListModel>
#include <Geltan/PP/ppenums.h>
#include <Geltan/geltan_global.h>

namespace Geltan {
namespace PP {

class InstallmentOptionsPrivate;
class InstallmentDescription;

/*!
 * \brief Model containing information about installment options and a list of InstallmentDescription objects.
 *
 * \ppPaymentsApi{installment_options}
 *
 * \headerfile "" <Geltan/PP/Objects/installmentoptions.h>
 * \since 0.0.1
 * \version 0.0.1
 * \date 2016-09-08
 * \author Buschmann
 * \copyright GNU LESSER GENERAL PUBLIC LICENSE Version 3
 */
class GELTANSHARED_EXPORT InstallmentOptions : public QAbstractListModel
{
    Q_OBJECT
    /*!
     * \brief Installment id.
     *
     * \ppApiName{installment_id}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>installmentId() const</TD></TR><TR><TD>void</TD><TD>setInstallmentId(const QString &nInstallmentId)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>installmentIdChanged(const QString &installmentId)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString installmentId READ installmentId NOTIFY installmentIdChanged)
    /*!
     * \brief Credit card network.
     *
     * \ppApiName{network}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::CreditCardType</TD><TD>network() const</TD></TR><TR><TD>void</TD><TD>setNetwork(PayPal::CreditCardType nNetwork)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>networkChanged(PayPal::CreditCardType network)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::CreditCardType network READ network NOTIFY networkChanged)
    /*!
     * \brief Credit card issuer.
     *
     * \ppApiName{issuer}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QString</TD><TD>issuer() const</TD></TR><TR><TD>void</TD><TD>setIssuer(const QString &nIssuer)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>issuerChanged(const QString &issuer)</TD></TR></TABLE>
     */
    Q_PROPERTY(QString issuer READ issuer NOTIFY issuerChanged)
    /*!
     * \brief A resource describing an installment.
     *
     * \ppApiName{installment_optinos}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<InstallmentDescription*></TD><TD>installmentOptions() const</TD></TR><TR><TD>void</TD><TD>setInstallmentOptions(const QList<InstallmentDescription*> &nInstallmentOptions)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>installmentOptionsChanged(const QList<InstallmentDescription*> &installmentOptions)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<InstallmentDescription*> installmentOptions READ installmentOptions WRITE setInstallmentOptions NOTIFY installmentOptionsChanged)
public:
    /*!
     * \brief Constructs a new empty InstallmentOptions object.
     */
    explicit InstallmentOptions(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new InstallmentOptions object from JSON data.
     */
    InstallmentOptions(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new InstallmentOptions object from JSON data.
     */
    InstallmentOptions(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Deconstructs the InstallmentOptions object.
     */
    ~InstallmentOptions();



    /*!
     * \brief The model roles.
     *
     * To access the roles from QML, use the enumeration name starting lowercase.
     */
    enum Roles {
        Item = Qt::UserRole + 1 /**< Returns a pointer to the model item (InstallmentDescription) itself. */
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


    QString installmentId() const;
    PayPal::CreditCardType network() const;
    QString issuer() const;
    QList<InstallmentDescription*> installmentOptions() const;


    void setInstallmentId(const QString &nInstallmentId);
    void setNetwork(PayPal::CreditCardType nNetwork);
    void setIssuer(const QString &nIssuer);
    void setInstallmentOptions(const QList<InstallmentDescription*> &nInstallmentOptions);

    /*!
     * \brief Loads data from a QJsonDocument into the InstallmentOptions object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the InstallmentOptions object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void installmentIdChanged(const QString &installmentId);
    void networkChanged(PayPal::CreditCardType network);
    void issuerChanged(const QString &issuer);
    void installmentOptionsChanged(const QList<InstallmentDescription*> &installmentOptions);

protected:
    const QScopedPointer<InstallmentOptionsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(InstallmentOptions)
    Q_DECLARE_PRIVATE(InstallmentOptions)

};

}
}

#endif // INSTALLMENTOPTIONS_H
