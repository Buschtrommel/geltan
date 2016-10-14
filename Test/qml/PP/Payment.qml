/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/Payment.qml
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
import QtQuick.Layouts 1.1
import Buschtrommel.Geltan.PayPal 1.0

ColumnLayout {
    id: mainGrid
    anchors { left: parent.left; right: parent.right }

    objectName: "paymentData"

    property Payment p: null

    GroupBox {
        title: "Redirect URLs (required)"
        Layout.fillWidth: true

        ColumnLayout {
            anchors.fill: parent

            TextField {
                id: returnUrlField
                placeholderText: "Return URL"
                Layout.fillWidth: true
                inputMethodHints: Qt.ImhUrlCharactersOnly
                text: p && p.redirectUrls ? p.redirectUrls.returnUrl.toString() : ""
                onTextChanged: if (p.redirectUrls) { p.redirectUrls.returnUrl = returnUrlField.text }
            }

            TextField {
                id: cancelUrlField
                placeholderText: "Cancel URL"
                Layout.fillWidth: true
                inputMethodHints: Qt.ImhUrlCharactersOnly
                text: p && p.redirectUrls ? p.redirectUrls.cancelUrl.toString() : ""
                onTextChanged: if (p.redirectUrls) { p.redirectUrls.cancelUrl = cancelUrlField.text }
            }
        }
    }

    GroupBox {
        title: "Experience Profile ID (optional)"
        Layout.fillWidth: true

        ColumnLayout {
            anchors.fill: parent

            TextField {
                id: expProfileIdField
                placeholderText: "Experience Profile ID"
                Layout.fillWidth: true
                onTextChanged: p.experienceProfileId = text
            }

            Text {
                text: "PayPal generated identifier for the merchant's payment experience profile."
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
                Layout.preferredWidth: 290
            }
        }
    }

    GroupBox {
        title: "Note to Payer (optional)"
        Layout.fillWidth: true

        ColumnLayout {
            anchors.fill: parent

            TextArea {
                id: noteToPayerField
                Layout.fillWidth: true
                textFormat: TextEdit.PlainText
                onTextChanged: p.noteToPayer = text
            }

            Text {
                text: "Free-form field for the use of clients to pass in a message to the payer. Maximum length: 165"
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
                Layout.preferredWidth: 290
            }
        }
    }

    GroupBox {
        title: "Transactions (required)"
        Layout.fillWidth: true

        ColumnLayout {
            anchors.fill: parent

            Repeater {
                model: p

                Item {
                    Layout.fillWidth: true
                    height: transactionRow.height

                    RowLayout {
                        id: transactionRow
                        anchors { left: parent.left; right: parent.right }

                        Column {
                            Layout.fillWidth: true

                            Text {
                                id: descText
                                text: model.item.description
                                width: parent.width
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            }

                            Text {
                                id: amountText
                                text: model.item.amount ? "Amount: " + model.item.amount.currency + " " + model.item.amount.total : ""
                                width: parent.width
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            }
                        }

                        Button {
                            id: editButton
                            iconName: "document-edit"
                            Layout.alignment: Qt.AlignTop
                            onClicked: stack.push({item: Qt.resolvedUrl("Transaction.qml"), properties:{transaction: model.item}})
                        }

                        Button {
                            id: delButton
                            iconName: "entry-delete"
                            Layout.alignment: Qt.AlignTop
                            onClicked: p.removeTransaction(model.index)
                        }
                    }
                }
            }

            Button {
                text: "Add Transaction"
                Layout.alignment: Qt.AlignHCenter
                onClicked: stack.push({item: Qt.resolvedUrl("Transaction.qml"), properties:{transaction: p.addNewTransaction()}})
            }
        }
    }
}
