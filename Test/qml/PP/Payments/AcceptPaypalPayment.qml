/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/Payments/AcceptPaypalPayment.qml
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
                    compLoader.setSource("../Payment.qml", {"p": ppCreatePayment.payment})
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
                        compLoader.setSource("../PaymentView.qml", {"py": payment})
                    }
                }
            }
        }

        Button {
            id: payButton
            text: "Pay with PayPal"
            anchors { top: compLoader.bottom; horizontalCenter: parent.horizontalCenter; margins: margin }
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
