/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/MainView.qml
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

ScrollView {
    id: mainView
    objectName: "mainView"
    width: parent.width
    height: parent.height

    property string pageTitle: "Geltan Test"

    Flickable {
        anchors.fill: parent
        contentHeight: mainCol.height

        ColumnLayout {
            id: mainCol
            width: parent.width

            Button {
                text: "Request Token"
                Layout.fillWidth: true
                Layout.topMargin: 10
                enabled: config.payPalClientID !== "" && config.payPalSecret
                onClicked: stack.push(Qt.resolvedUrl("PP/AuthenticationTest.qml"))
            }

            Button {
                text: "Accept PayPal Payment"
                Layout.fillWidth: true
                Layout.topMargin: 10
                enabled: config.payPalTokenValid
                onClicked: stack.push(Qt.resolvedUrl("PP/Payments/AcceptPaypalPayment.qml"))
            }

            Button {
                text: "Show PayPal Payment"
                Layout.fillWidth: true
                Layout.topMargin: 10
                enabled: config.payPalTokenValid
                onClicked: stack.push(Qt.resolvedUrl("PP/Payments/Show.qml"))
            }

            Button {
                text: "List PayPal Payments"
                Layout.fillWidth: true
                Layout.topMargin: 10
                enabled: config.payPalTokenValid
                onClicked: stack.push(Qt.resolvedUrl("PP/Payments/List.qml"))
            }
        }
    }
}
