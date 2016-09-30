QT       += network

QT       -= gui

TARGET = geltan
TEMPLATE = lib

VERSION = 0.0.1

CONFIG -= console
CONFIG -= app_bundle
CONFIG += shared
CONFIG += c++11
CONFIG += no_keywords

DEFINES += GELTAN_LIBRARY

INCLUDEPATH += $$PWD/..

isEmpty(INSTALL_LIB_DIR): INSTALL_LIB_DIR = $$[QT_INSTALL_LIBS]

!isEmpty(GELTAN_PAYPAL_CLIENTID) {
DEFINES += GELTAN_PAYPAL_CLIENTID=\"\\\"$${GELTAN_PAYPAL_CLIENTID}\\\"\"
}

target.path = $$INSTALL_LIB_DIR
INSTALLS += target

HEADERS += geltan_global.h \
    component.h \
    component_p.h \
    error.h \
    error_p.h \
    PP/ppbase.h \
    PP/ppbase_p.h \
    PP/requestaccesstoken.h \
    PP/requestaccesstoken_p.h \
    PP/ppenums.h \
    PP/Objects/payer_p.h \
    PP/Objects/payer.h \
    PP/Objects/address_p.h \
    PP/Objects/address.h \
    PP/Objects/link.h \
    PP/Objects/link_p.h \
    PP/Objects/creditcard_p.h \
    PP/Objects/creditcard.h \
    PP/Objects/tokenizedcreditcard_p.h \
    PP/Objects/tokenizedcreditcard.h \
    PP/Objects/currency_p.h \
    PP/Objects/currency.h \
    PP/Objects/installmentdescription.h \
    PP/Objects/installmentdescription_p.h \
    PP/Objects/installmentoptions.h \
    PP/Objects/installmentoptions_p.h \
    PP/Objects/billinginstrument_p.h \
    PP/Objects/billinginstrument.h \
    PP/Objects/payerinfo_p.h \
    PP/Objects/payerinfo.h \
    PP/Objects/details.h \
    PP/Objects/details_p.h \
    PP/Objects/paymentamount.h \
    PP/Objects/paymentamount_p.h \
    PP/Objects/item.h \
    PP/Objects/item_p.h \
    PP/Objects/shippingaddress.h \
    PP/Objects/shippingaddress_p.h \
    PP/Objects/itemlist.h \
    PP/Objects/itemlist_p.h \
    PP/Objects/paymentoptions.h \
    PP/Objects/paymentoptions_p.h \
    PP/Objects/fmfdetails_p.h \
    PP/Objects/fmfdetails.h \
    PP/Objects/processorresponse.h \
    PP/Objects/processorresponse_p.h \
    PP/Objects/sale.h \
    PP/Objects/sale_p.h \
    PP/Objects/authorization_p.h \
    PP/Objects/authorization.h \
    PP/Objects/order_p.h \
    PP/Objects/order.h \
    PP/Objects/capture_p.h \
    PP/Objects/capture.h \
    PP/Objects/refund_p.h \
    PP/Objects/refund.h \
    PP/Objects/related.h \
    PP/Objects/related_p.h \
    PP/Objects/transaction.h \
    PP/Objects/transaction_p.h \
    PP/Objects/redirecturls.h \
    PP/Objects/redirecturls_p.h \
    PP/Objects/ppobjectsbase_p.h \
    PP/Objects/fundinginstrument.h \
    PP/Objects/fundinginstrument_p.h \
    PP/Objects/payment.h \
    PP/Objects/payment_p.h \
    PP/createpayment.h \
    PP/createpayment_p.h \
    PP/ppenumsmap.h \
    PP/executepayment.h \
    PP/executepayment_p.h \
    PP/showpayment.h \
    PP/showpayment_p.h \
    PP/Objects/payee.h \
    PP/Objects/payee_p.h

SOURCES += \
    component.cpp \
    error.cpp \
    PP/ppbase.cpp \
    PP/requestaccesstoken.cpp \
    PP/Objects/payer.cpp \
    PP/Objects/address.cpp \
    PP/Objects/link.cpp \
    PP/Objects/creditcard.cpp \
    PP/Objects/tokenizedcreditcard.cpp \
    PP/Objects/currency.cpp \
    PP/Objects/installmentdescription.cpp \
    PP/Objects/installmentoptions.cpp \
    PP/Objects/billinginstrument.cpp \
    PP/Objects/payerinfo.cpp \
    PP/Objects/details.cpp \
    PP/Objects/paymentamount.cpp \
    PP/Objects/item.cpp \
    PP/Objects/shippingaddress.cpp \
    PP/Objects/itemlist.cpp \
    PP/Objects/paymentoptions.cpp \
    PP/Objects/fmfdetails.cpp \
    PP/Objects/processorresponse.cpp \
    PP/Objects/sale.cpp \
    PP/Objects/authorization.cpp \
    PP/Objects/order.cpp \
    PP/Objects/capture.cpp \
    PP/Objects/refund.cpp \
    PP/Objects/related.cpp \
    PP/Objects/transaction.cpp \
    PP/Objects/redirecturls.cpp \
    PP/Objects/fundinginstrument.cpp \
    PP/Objects/payment.cpp \
    PP/createpayment.cpp \
    PP/ppenumsmap.cpp \
    PP/executepayment.cpp \
    PP/showpayment.cpp \
    PP/Objects/payee.cpp
