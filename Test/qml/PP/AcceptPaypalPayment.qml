import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
//import QtWebEngine 1.2
import QtWebKit 3.0
import Buschtrommel.Geltan.PayPal 1.0

ScrollView {
    id: ppAuthTestView
    objectName: "acceptPaypalPaymentTestView"
    property int margin: 10
    width: parent.width
    height: parent.height

    property string pageTitle: "Accept PayPal Payment"

    Flickable {
        id: ppAuthTestFlick
        anchors.fill: parent
        contentHeight: compLoader.status != Loader.Null ? (compLoader.height + payButton.height) : parent.height

        BusyIndicator {
            anchors.centerIn: parent
            running: ppCreatePayment.inOperation || execPayment.inOperation
        }

        Button {
            anchors.centerIn: parent
            visible: !ppCreatePayment.inOperation && !ppCreatePayment.payment
            text: "Create new PayPal Payment"
            onClicked: {
                ppCreatePayment.newPayment()
                if (ppCreatePayment.payment) {
                    ppCreatePayment.payment.intent = PPPayment.Sale
                    ppCreatePayment.payment.payer.paymentMethod = PayPal.PayPalWallet
                    ppCreatePayment.payment.addRedirectUrls(config.paypalReturnUrl, config.paypalCancelUrl)
                    compLoader.setSource("Payment.qml", {"p": ppCreatePayment.payment})
                    payButton.visible = true
                }
            }
        }

        Loader {
            id: compLoader
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: margin }

            PPCreatePayment {
                id: ppCreatePayment
                token: config.payPalToken
                tokenType: config.payPalTokenType
                onSucceeded: {
                    if (payment) {
                        execPayment.payment = payment
                        compLoader.sourceComponent = authWeb
                    }
                }
            }

            PPExecutePayment {
                id: execPayment
                token: config.payPalToken
                tokenType: config.payPalTokenType
                onSucceeded: {
                    if (payment) {
                        compLoader.setSource("PaymentView.qml", {"py": payment})
                    }
                }
            }
        }

        Button {
            id: payButton
            text: "Pay with PayPal"
            anchors { top: compLoader.bottom; horizontalCenter: parent.horizontalCenter; margins: margin }
//            onClicked: ppCreatePayment.call()
            onClicked: { payButton.visible = false; ppCreatePayment.call() }
            visible: compLoader.item !== null && compLoader.item.objectName === "paymentData"
        }


        Component {
            id: authWeb

//            WebEngineView {
            WebView {
                id: webViewEngine
                anchors.fill: parent
                visible: !execPayment.inOperation

                onUrlChanged: execPayment.call(url)

                Component.onCompleted: url = ppCreatePayment.payment.getLinkURL("approval_url")
            }
        }
    }
}
