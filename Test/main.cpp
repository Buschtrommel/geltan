/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/main.cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <QApplication>
#include <QtQml>
#include <QQmlContext>
//#include <QtWebEngine>

#include "gtconfig.h"
#include "PP/authenticationtest.h"

#include <Geltan/PP/ppenums.h>
#include <Geltan/PP/Objects/address.h>
#include <Geltan/PP/Objects/authorization.h>
#include <Geltan/PP/Objects/billinginstrument.h>
#include <Geltan/PP/Objects/capture.h>
#include <Geltan/PP/Objects/creditcard.h>
#include <Geltan/PP/Objects/currency.h>
#include <Geltan/PP/Objects/details.h>
#include <Geltan/PP/Objects/fmfdetails.h>
#include <Geltan/PP/Objects/fundinginstrument.h>
#include <Geltan/PP/Objects/installmentdescription.h>
#include <Geltan/PP/Objects/installmentoptions.h>
#include <Geltan/PP/Objects/item.h>
#include <Geltan/PP/Objects/itemlist.h>
#include <Geltan/PP/Objects/link.h>
#include <Geltan/PP/Objects/order.h>
#include <Geltan/PP/Objects/payer.h>
#include <Geltan/PP/Objects/payerinfo.h>
#include <Geltan/PP/Objects/payment.h>
#include <Geltan/PP/Objects/paymentamount.h>
#include <Geltan/PP/Objects/paymentoptions.h>
#include <Geltan/PP/Objects/processorresponse.h>
#include <Geltan/PP/Objects/redirecturls.h>
#include <Geltan/PP/Objects/refund.h>
#include <Geltan/PP/Objects/related.h>
#include <Geltan/PP/Objects/sale.h>
#include <Geltan/PP/Objects/shippingaddress.h>
#include <Geltan/PP/Objects/tokenizedcreditcard.h>
#include <Geltan/PP/Objects/transaction.h>
#include <Geltan/PP/Objects/payee.h>
#include <Geltan/PP/Objects/paymentlist.h>

#include <Geltan/PP/Payments/create.h>
#include <Geltan/PP/Payments/execute.h>
#include <Geltan/PP/Payments/get.h>
#include <Geltan/PP/Payments/list.h>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationDisplayName(QStringLiteral("Geltan Test"));
    app.setApplicationName(QStringLiteral("geltanTest"));
    app.setOrganizationDomain(QStringLiteral("buschmann23.de"));
    app.setOrganizationName(QStringLiteral("Buschtrommel"));
    app.setApplicationVersion(QStringLiteral("0.0.1"));

//    QtWebEngine::initialize();

    GeltanTest::GtConfig config;

    qmlRegisterUncreatableType<Geltan::PP::PayPal>("Buschtrommel.Geltan.PayPal", 1, 0, "PayPal", QStringLiteral("You can not create PayPal"));
    qmlRegisterType<Geltan::PP::Address>("Buschtrommel.Geltan.PayPal", 1, 0, "PPAddress");
    qmlRegisterType<Geltan::PP::Authorization>("Buschtrommel.Geltan.PayPal", 1, 0, "PPAuthorization");
    qmlRegisterType<Geltan::PP::BillingInstrument>("Buschtrommel.Geltan.PayPal", 1, 0, "PPBillingInstrument");
    qmlRegisterType<Geltan::PP::Capture>("Buschtrommel.Geltan.PayPal", 1, 0, "PPCapture");
    qmlRegisterType<Geltan::PP::CreditCard>("Buschtrommel.Geltan.PayPal", 1, 0, "PPCreditCard");
    qmlRegisterType<Geltan::PP::Currency>("Buschtrommel.Geltan.PayPal", 1, 0, "PPCurrency");
    qmlRegisterType<Geltan::PP::Details>("Buschtrommel.Geltan.PayPal", 1, 0, "PPDetails");
    qmlRegisterType<Geltan::PP::FMFDetails>("Buschtrommel.Geltan.PayPal", 1, 0, "PPFMFDetails");
    qmlRegisterType<Geltan::PP::FundingInstrument>("Buschtrommel.Geltan.PayPal", 1, 0, "PPFundingInstrument");
    qmlRegisterType<Geltan::PP::InstallmentDescription>("Buschtrommel.Geltan.PayPal", 1, 0, "PPInstallmentDescription");
    qmlRegisterType<Geltan::PP::InstallmentOptions>("Buschtrommel.Geltan.PayPal", 1, 0, "PPInstallmentOptions");
    qmlRegisterType<Geltan::PP::Item>("Buschtrommel.Geltan.PayPal", 1, 0, "PPItem");
    qmlRegisterType<Geltan::PP::ItemList>("Buschtrommel.Geltan.PayPal", 1, 0, "PPItemList");
    qmlRegisterType<Geltan::PP::Link>("Buschtrommel.Geltan.PayPal", 1, 0, "PPLink");
    qmlRegisterType<Geltan::PP::Order>("Buschtrommel.Geltan.PayPal", 1, 0, "PPOrder");
    qmlRegisterType<Geltan::PP::Payer>("Buschtrommel.Geltan.PayPal", 1, 0, "PPPayer");
    qmlRegisterType<Geltan::PP::PayerInfo>("Buschtrommel.Geltan.PayPal", 1, 0, "PPPayerInfo");
    qmlRegisterType<Geltan::PP::Payment>("Buschtrommel.Geltan.PayPal", 1, 0, "PPPayment");
    qmlRegisterType<Geltan::PP::PaymentAmount>("Buschtrommel.Geltan.PayPal", 1, 0, "PPPaymentAmount");
    qmlRegisterType<Geltan::PP::PaymentOptions>("Buschtrommel.Geltan.PayPal", 1, 0, "PPPaymentOptions");
    qmlRegisterType<Geltan::PP::ProcessorResponse>("Buschtrommel.Geltan.PayPal", 1, 0, "PPProcessorResponse");
    qmlRegisterType<Geltan::PP::RedirectUrls>("Buschtrommel.Geltan.PayPal", 1, 0, "PPRedirectUrls");
    qmlRegisterType<Geltan::PP::Refund>("Buschtrommel.Geltan.PayPal", 1, 0, "PPRefund");
    qmlRegisterType<Geltan::PP::Related>("Buschtrommel.Geltan.PayPal", 1, 0, "PPRelated");
    qmlRegisterType<Geltan::PP::Sale>("Buschtrommel.Geltan.PayPal", 1, 0, "PPSale");
    qmlRegisterType<Geltan::PP::ShippingAddress>("Buschtrommel.Geltan.PayPal", 1, 0, "PPShippingAddress");
    qmlRegisterType<Geltan::PP::TokenizedCreditCard>("Buschtrommel.Geltan.PayPal", 1, 0, "PPTokenizedCreditCard");
    qmlRegisterType<Geltan::PP::Transaction>("Buschtrommel.Geltan.PayPal", 1, 0, "PPTransaction");
    qmlRegisterType<Geltan::PP::Payee>("Buschtrommel.Geltan.PayPal", 1, 0, "PPPayee");
    qmlRegisterUncreatableType<Geltan::PP::PaymentList>("Buschtrommel.Geltan.PayPal", 1, 0, "PPPaymentList", QStringLiteral("You can not create PaymentList"));

    qmlRegisterType<Geltan::PP::Payments::Create>("Buschtrommel.Geltan.PayPal", 1, 0, "PPCreatePayment");
    qmlRegisterType<Geltan::PP::Payments::Execute>("Buschtrommel.Geltan.PayPal", 1, 0, "PPExecutePayment");
    qmlRegisterType<Geltan::PP::Payments::Get>("Buschtrommel.Geltan.PayPal", 1, 0, "GetPayment");
    qmlRegisterType<Geltan::PP::Payments::List>("Buschtrommel.Geltan.PayPal", 1, 0, "PPListPayments");

    qmlRegisterType<GeltanTest::AuthenticationTest>("Buschtrommel.Geltan.PayPalTests", 1, 0, "PPAuthenticationTest");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("config"), &config);

    engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

    return app.exec();
}
