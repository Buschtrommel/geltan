/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/AuthenticationTest.qml
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

    property string pageTitle: "Request PayPal Token"

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
