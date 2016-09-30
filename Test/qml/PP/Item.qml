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
                title: "Price, Tax & Currency"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    Text { text: "Price" }

                    TextField {
                        id: totalAmountField
                        placeholderText: "Price"
                        Layout.fillWidth: true
                        text: item.price
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        onTextChanged: if (text.length > 0) { item.price = parseFloat(text) } else { item.price = 0.0 }
                    }

                    Text { text: "Tax" }

                    TextField {
                        id: taxField
                        placeholderText: "Tax"
                        Layout.fillWidth: true
                        text: item.price
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        onTextChanged: if (text.length > 0) { item.tax = parseFloat(text) } else { item.tax = 0.0 }
                    }

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

            GroupBox {
                title: "URL"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: urlField
                        placeholderText: "Quantity"
                        Layout.fillWidth: true
                        text: item.quantity
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
