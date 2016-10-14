/* libgeltan - Qt based payment service library
 * Copyright (C) 2016 Buschtrommel / Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Geltan/PP/Objects/payer.h
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

#ifndef PAYER_H
#define PAYER_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariantList>
#include <QVariantMap>
#include <QJsonObject>
#include <Geltan/geltan_global.h>
#include <Geltan/PP/ppenums.h>

namespace Geltan {
namespace PP {

class PayerInfo;
class PayerPrivate;
class FundingInstrument;

/*!
 * \brief Containes basic information about a Payer that funds a payment.
 *
 * This also contains a list of FundingInstrument objects, provided through a QAbstractListModel.
 *
 * \ppPaymentsApi{payer}
 *
 * \headerfile "" <Geltan/PP/Objects/payer.h>
 */
class GELTANSHARED_EXPORT Payer : public QAbstractListModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Payer)
    /*!
     * \brief Payment method being used.
     *
     * \ppApiName{payment_method}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::PaymentMethod</TD><TD>paymentMethod() const</TD></TR><TR><TD>void</TD><TD>setPaymentMethod(PayPal::PaymentMethod nPaymentMethod)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>paymentMethodChanged(PayPal::PaymentMethod paymentMethod)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayPal::PaymentMethod paymentMethod READ paymentMethod WRITE setPaymentMethod NOTIFY paymentMethodChanged)
    /*!
     * \brief Status of payer's PayPal account
     *
     * \ppApiName{status}
     *
     * \par Access functions:
     * <TABLE><TR><TD>Status</TD><TD>status() const</TD></TR><TR><TD>void</TD><TD>setStatus(Status nStatus)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>statusChanged(Status status)</TD></TR></TABLE>
     */
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    /*!
     * \brief A resource representing a Payer's funding instrument.
     *
     * An instance of this schema is valid if and only if it is valid against exactly one of it's supported
     * properties. Contains a list of pointers to FundingInstrument objects. If they are created internally, they will be
     * children of the Payer object and will be destroyed if the parent get destroyed. They are accessible through the Payer
     * model.
     *
     * \ppApiName{funding_instruments}
     *
     * \par Access functions:
     * <TABLE><TR><TD>QList<FundingInstrument*></TD><TD>fundingInstruments() const</TD></TR><TR><TD>void</TD><TD>setFundingInstruments(const QList<FundingInstrument*> &nFundingInstruments)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>fundingInstrumentsChanged(const QList<FundingInstrument*> &fundingInstruments)</TD></TR></TABLE>
     */
    Q_PROPERTY(QList<Geltan::PP::FundingInstrument*> fundingInstruments READ fundingInstruments WRITE setFundingInstruments NOTIFY fundingInstrumentsChanged)
    /*!
     * \brief Instrument type pre-selected by the user outside of PayPal and passed along the payment creation.
     *
     * \ppApiName{external_selected_funding_instrument_type}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayPal::FundingInstrumentType</TD><TD>externalSelectedFundingInstrumentType() const</TD></TR><TR><TD>void</TD><TD>setExternalSelectedFundingInstrumentType(PayPal::FundingInstrumentType nExternalSelectedFundingInstrumentType)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>externalSelectedFundingInstrumentTypeChanged(PayPal::FundingInstrumentType externalSelectedFundingInstrumentType)</TD></TR></TABLE>
     */
    Q_PROPERTY(FundingInstrumentType externalSelectedFundingInstrumentType READ externalSelectedFundingInstrumentType WRITE setExternalSelectedFundingInstrumentType NOTIFY externalSelectedFundingInstrumentTypeChanged)
    /*!
     * \brief A resource representing more information about Payer.
     *
     * Contains a pointer to a PayerInfo object, if any, otherwise contains a nullptr. If created internally, the PayerInfo object will be a child
     * of the Payer object and will be destroyed if the parent gets destroyed.
     *
     * \ppApiName{payer_info}
     *
     * \par Access functions:
     * <TABLE><TR><TD>PayerInfo*</TD><TD>payerInfo() const</TD></TR><TR><TD>void</TD><TD>setPayerInfo(PayerInfo *nPayerInfo)</TD></TR></TABLE>
     * \par Notifier signal:
     * <TABLE><TR><TD>void</TD><TD>payerInfoChanged(PayerInfo *payerInfo)</TD></TR></TABLE>
     */
    Q_PROPERTY(Geltan::PP::PayerInfo *payerInfo READ payerInfo WRITE setPayerInfo NOTIFY payerInfoChanged)
public:
    /*!
     * \brief Constructs a new empty Payer object.
     */
    explicit Payer(QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Payer object from JSON data.
     */
    Payer(const QJsonDocument &json, QObject *parent = nullptr);

    /*!
     * \brief Constructs a new Payer object from JSON data.
     */
    Payer(const QJsonObject &json, QObject *parent = nullptr);

    /*!
     * \brief Destroys the Payer object.
     */
    ~Payer();

    /*!
     * \brief Status of the payer's PayPal account.
     */
    enum Status {
        NoStatus    = 0,    /**< No status set. */
        Verified    = 1,    /**< Account is verified. */
        Unverified  = 2     /**< Account is not verified. */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(Status)
#else
    Q_ENUMS(Status)
#endif

    /*!
     * \brief Instrument type pre-selected by the user outside of PayPal and passed along the payment creation.
     */
    enum FundingInstrumentType {
        NoFundingInstrumentType = 0,    /**< No type set. */
        Credit                  = 1,    /**< Credit. PayPal API Name: CREDIT */
        PayUponInvoice          = 2     /**< Pay upon invoice. PayPal API Name: PAY_UPON_INVOICE */
    };
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(FundingInstrumentType)
#else
    Q_ENUMS(FundingInstrumentType)
#endif

    /*!
     * \brief Model roles.
     *
     * To use the model data in QML, use the enumeration name starting lowercase.
     */
    enum Roles {
        Item = Qt::UserRole + 1 /**< Returns the FundingInstrument object itself. */
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


    PayPal::PaymentMethod paymentMethod() const;
    Status status() const;
    QList<FundingInstrument*> fundingInstruments() const;
    FundingInstrumentType externalSelectedFundingInstrumentType() const;
    PayerInfo *payerInfo() const;


    void setPaymentMethod(PayPal::PaymentMethod nPaymentMethod);
    /*!
     * \brief Sets the status of this payer.
     */
    void setStatus(Status nStatus);
    void setFundingInstruments(const QList<FundingInstrument*> &nFundingInstruments);
    void setExternalSelectedFundingInstrumentType(FundingInstrumentType nExternalSelectedFundingInstrumentType);
    void setPayerInfo(PayerInfo *nPayerInfo);


    /*!
     * \brief Adds a new FundingInstrument to the Payer object's model.
     *
     * If the FundingInstrument is living in another thread, it will be tried to move it
     * to the model's thread. If that fails, the FundingInstrument will not be added. If the
     * move was successful, the model Payer object will be set as parent of the FundingInstrument.
     *
     * Returns true if the FundingInstrument has been addes successful.
     */
    bool addFundingInstrument(FundingInstrument *fi);

    /*!
     * \brief Adds a list of FundingInstrument objects to the Payer object's model.
     *
     * If the FundingInstrument is living in another thread, it will be tried to move it
     * to the model's thread. If that fails, the FundingInstrument will not be added. If the
     * move was successful, the model Payer object will be set as parent of the FundingInstrument.
     */
    void addFundingInstruments(const QList<FundingInstrument*> &fis);


    /*!
     * \brief Returns a QVariantMap containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API. Will only contain properties that are not read only.
     */
    QVariantMap toVariant();

    /*!
     * \brief Returns a QJsonObject containing the object's data members.
     *
     * The names of the keys will be the name used by the PayPal API. Will only contain properties that are not read only.
     */
    QJsonObject toJsonObject();

    /*!
     * \brief Loads data from a QJsonDocument into the Payer object.
     */
    void loadFromJson(const QJsonDocument &json);

    /*!
     * \brief Loads data from a QJsonObject into the Payer object.
     */
    void loadFromJson(const QJsonObject &json);


Q_SIGNALS:
    void paymentMethodChanged(PayPal::PaymentMethod paymentMethod);
    void statusChanged(Status status);
    void fundingInstrumentsChanged(const QList<FundingInstrument*> &fundingInstruments);
    void externalSelectedFundingInstrumentTypeChanged(FundingInstrumentType externalSelectedFundingInstrumentType);
    void payerInfoChanged(PayerInfo *payerInfo);

protected:
    const QScopedPointer<PayerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(Payer)

};

}
}

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
Q_DECLARE_METATYPE(Geltan::PP::Payer::Status)
Q_DECLARE_METATYPE(Geltan::PP::Payer::FundingInstrumentType)
#endif

#endif // PAYER_H
