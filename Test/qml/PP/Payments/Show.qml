/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/Payments/Show.qml
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

        GetPayment {
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
