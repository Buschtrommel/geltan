/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/Item.qml
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

ScrollView {
    id: ppItemView
    objectName: "ppItemView"
    property int margin: 10
    width: mainCol.implicitWidth + 2 * margin
    height: mainCol.implicitHeight + 2 * margin

    property PPItem item: null
    property string pageTitle: "Edit Item"

    Flickable {
        anchors.fill: parent
        contentHeight: mainCol.height + margin

        ColumnLayout {
            id: mainCol
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: margin }

            GroupBox {
                title: "Stock Keeping Unit"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: skuField
                        placeholderText: "SKU"
                        Layout.fillWidth: true
                        text: item.sku
                        onTextChanged: item.sku = text
                    }

                    Text {
                        text: "Stock keeping unit (SKU) corresponding to item. Maximum length: 127"
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        Layout.preferredWidth: 290
                    }
                }
            }

            GroupBox {
                title: "Name"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: nameField
                        placeholderText: "Name"
                        Layout.fillWidth: true
                        text: item.name
                        onTextChanged: item.name = text
                    }

                    Text {
                        text: "Item name. 127 characters max."
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        Layout.preferredWidth: 290
                    }
                }
            }

            GroupBox {
                title: "Description"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: descField
                        placeholderText: "Description"
                        Layout.fillWidth: true
                        text: item.description
                        onTextChanged: item.description = text
                    }

                    Text {
                        text: "Description of the item. Only supported when the payment_method is set to paypal. 127 characters max."
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        Layout.preferredWidth: 290
                    }
                }
            }

            GroupBox {
                title: "Quantity"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: quantField
                        placeholderText: "Quantity"
                        Layout.fillWidth: true
                        text: item.quantity
                        inputMethodHints: Qt.ImhDigitsOnly
                        onTextChanged: if (text.length > 0) { item.quantity = parseInt(text) } else { item.quantity = 1 }
                    }

                    Text {
                        text: "Number of a particular item. 10 characters max."
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        Layout.preferredWidth: 290
                    }
                }
            }

            GroupBox {
                title: "Price, Tax and Currency"
                Layout.fillWidth: true

                RowLayout {
                    anchors.fill: parent

                    ColumnLayout {

                        Text { text: "Price" }

                        TextField {
                            id: totalAmountField
                            placeholderText: "Price"
                            Layout.fillWidth: true
                            text: item.price.toLocaleString()
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                            onTextChanged: if (text.length > 0) { item.price = Number.fromLocaleString(Qt.locale(), text) } else { item.price = 0.0 }
                        }
                    }

                    ColumnLayout {

                        Text { text: "Tax" }

                        TextField {
                            id: taxField
                            placeholderText: "Tax"
                            Layout.fillWidth: true
                            text: item.tax.toLocaleString()
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                            onTextChanged: if (text.length > 0) { item.tax = Number.fromLocaleString(Qt.locale(), text) } else { item.tax = 0.0 }
                        }
                    }

                    ColumnLayout {

                        Text { text: "Currency" }

                        TextField {
                            id: totalAmountCurrency
                            placeholderText: "Currency"
                            Layout.fillWidth: true
                            text: item.currency
                            onTextChanged: item.currency = text
                        }
                    }
                }
            }

            GroupBox {
                title: "URL (optional)"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: urlField
                        placeholderText: "URL"
                        Layout.fillWidth: true
                        text: item.url
                        inputMethodHints: Qt.ImhDigitsOnly
                        onTextChanged: item.url = text
                    }

                    Text {
                        text: "URL linking to item information. Available to payer in transaction history."
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        Layout.preferredWidth: 290
                    }
                }
            }
        }
    }
}
