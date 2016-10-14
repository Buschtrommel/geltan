/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/Settings.qml
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
    id: settingsView
    objectName: "settingsView"
    width: parent.width
    height: parent.height

    property string pageTitle: "Settings"

    Flickable {
        anchors.fill: parent
        contentHeight: mainCol.height

        ColumnLayout {
            id: mainCol
            width: parent.width

            GroupBox {
                title: "PayPal"
                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            id: paypalclientidLabel
                            text: "Client ID"
                            Layout.minimumWidth: Math.max(paypalSecretLabel.contentWidth, paypalclientidLabel.contentWidth)
                        }

                        TextField {
                            id: paypalclientid
                            placeholderText: "Client ID"
                            Layout.fillWidth: true
                            text: config.payPalClientID

                            Binding { target: config; property: "payPalClientID"; value: paypalclientid.text }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            id: paypalSecretLabel
                            text: "Secret"
                            Layout.minimumWidth: Math.max(paypalSecretLabel.contentWidth, paypalclientidLabel.contentWidth)
                        }

                        TextField {
                            id: paypalSecret
                            placeholderText: "Secret"
                            Layout.fillWidth: true
                            text: config.payPalSecret

                            Binding { target: config; property: "payPalSecret"; value: paypalSecret.text }
                        }
                    }

                    Label {
                        Layout.fillWidth: true
                        text: "Default Values"
                        font.bold: true
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: "Return URL"
                        }

                        TextField {
                            id: ppReturnUrl
                            placeholderText: "Return URL"
                            Layout.fillWidth: true
                            text: config.paypalReturnUrl

                            Binding { target: config; property: "paypalReturnUrl"; value: ppReturnUrl.text }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: "Cancel URL"
                        }

                        TextField {
                            id: ppCancelUrl
                            placeholderText: "Cancel URL"
                            Layout.fillWidth: true
                            text: config.paypalCancelUrl

                            Binding { target: config; property: "paypalCancelUrl"; value: ppCancelUrl.text }
                        }
                    }
                }

            }
        }
    }
}
