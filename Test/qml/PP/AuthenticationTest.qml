import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import Buschtrommel.Geltan.PayPal 1.0
import Buschtrommel.Geltan.PayPalTests 1.0

ScrollView {
    id: ppAuthTestView
    objectName: "ppAuthTestView"
    width: parent.width
    height: parent.height

    BusyIndicator {
        anchors.centerIn: parent
        running: ppAuthTest.inOperation
    }

    Button {
        anchors.centerIn: parent
        visible: !ppAuthTest.inOperation && !config.payPalTokenValid
        text: qsTr("Request new PayPal token")
        onClicked: ppAuthTest.requestToken()
    }

    Flickable {
        anchors.fill: parent
        contentHeight: mainGrid.height

        PPAuthenticationTest {
            id: ppAuthTest
            configuration: config
        }

        GridLayout {
            id: mainGrid
            anchors { left: parent.left; leftMargin: 15; right: parent.right; rightMargin: 15; top: parent.top; topMargin: 15 }
            visible: !ppAuthTest.inOperation && config.payPalTokenValid
            columns: 2

            Label { text: "Token Type"; textFormat: Text.PlainText }
            Text { text: config.payPalTokenType === PayPal.Bearer ? "Bearer" : config.payPalTokenType === PayPal.MAC ? "MAC" : "No token type set"; textFormat: Text.PlainText }


            Label { text: "Token"; Layout.alignment: Qt.AlignLeft | Qt.AlignTop; textFormat: Text.PlainText }
            Text { text: config.payPalToken; Layout.fillWidth: true; wrapMode: Text.WrapAnywhere; textFormat: Text.PlainText }


            Label { text: "App ID"; textFormat: Text.PlainText }
            Text { text: config.payPalAppID; textFormat: Text.PlainText }


            Label { text: "Expiration"; textFormat: Text.PlainText }
            Text { text: config.payPalTokenExpiration; textFormat: Text.PlainText }

            Button {
                text: qsTr("Remove PayPal token data")
                Layout.alignment: Qt.AlignHCenter
                Layout.columnSpan: parent.columns
                onClicked: {
                    config.payPalTokenType = PayPal.NoTokenType
                    config.payPalToken = ""
                    config.payPalAppID = ""
                }
            }
        }
    }
}
