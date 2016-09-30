import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtWebEngine 1.2
import Buschtrommel.Geltan.PayPal 1.0

ScrollView {
    id: ppShowPaymentView
    objectName: "showPaymentTestView"
    property int margin: 10
    width: parent.width
    height: parent.height

    property string pageTitle: "Show Payment Details"

    Flickable {
        id: ppShowPaymentTestFlick
        anchors.fill: parent
        contentHeight: compLoader.status != Loader.Null ? compLoader.height : parent.height

        PPShowPayment {
            id: ppShowPayment
            token: config.payPalToken
            tokenType: config.payPalTokenType
            onSucceeded: {
                if (payment) {
                    compLoader.setSource("PaymentView.qml", {"py": payment})
                }
            }
        }

        BusyIndicator {
            anchors.centerIn: parent
            running: ppShowPayment.inOperation
        }

        Item {
            anchors.centerIn: parent
            width: parent.width - 2 * margin
            height: paymentIdField.height + requestButton.height + margin
            visible: !ppShowPayment.inOperation && !ppShowPayment.payment

            TextField {
                id: paymentIdField
                anchors { left: parent.left; right: parent.right }
                placeholderText: "Payment ID"
            }

            Button {
                id: requestButton
                anchors { top: paymentIdField.bottom; topMargin: margin; horizontalCenter: parent.horizontalCenter }
                text: "Request Details"
                onClicked: ppShowPayment.call(paymentIdField.text)
            }

        }

        Loader {
            id: compLoader
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: margin }
        }
    }
}
