import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

ScrollView {
    id: mainView
    objectName: "mainView"
    width: parent.width
    height: parent.height

    property string pageTitle: ""

    Flickable {
        anchors.fill: parent
        contentHeight: mainCol.height

        ColumnLayout {
            id: mainCol
            width: parent.width

            Button {
                text: "Request Token"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                enabled: config.payPalClientID !== "" && config.payPalSecret
                onClicked: stack.push({item: Qt.resolvedUrl("PP/AuthenticationTest.qml")})
            }

            Button {
                text: "Accept PayPal Payment"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                enabled: config.payPalTokenValid
                onClicked: stack.push({item: Qt.resolvedUrl("PP/AcceptPaypalPayment.qml")})
            }

            Button {
                text: "Show PayPal Payment"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                enabled: config.payPalTokenValid
                onClicked: stack.push({item: Qt.resolvedUrl("PP/ShowPayment.qml")})
            }

            Button {
                text: "List PayPal Payments"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                enabled: config.payPalTokenValid
                onClicked: stack.push({item: Qt.resolvedUrl("PP/Payments/List.qml")})
            }
        }
    }
}
