/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/Transaction.qml
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
    id: ppTransactionView
    objectName: "ppTransactionView"
    property int margin: 10
    width: mainCol.implicitWidth + 2 * margin
    height: mainCol.implicitHeight + 2 * margin

    property Transaction transaction: null
    property string pageTitle: "Edit Transaction"

    Flickable {
        anchors.fill: parent
        contentHeight: mainCol.height + margin

        ColumnLayout {
            id: mainCol
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: margin }

            GroupBox {
                title: "Reference ID (optional)"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: refIdField
                        placeholderText: "Reference ID (optional)"
                        Layout.fillWidth: true
                        text: transaction.referenceId
                        onTextChanged: transaction.referenceId = text
                    }

                    Text {
                        text: "Merchant identifier to the purchase unit. Maximum length: 256"
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        Layout.preferredWidth: 290
                    }
                }
            }

            PaymentAmount {
                title: "Amount (required)"
                Layout.fillWidth: true
                pa: transaction.amount
            }

//            GroupBox {
//                title: "Amount (required)"
//                Layout.fillWidth: true

//                RowLayout {
//                    anchors.fill: parent

//                    TextField {
//                        id: totalAmountField
//                        placeholderText: "Total Amount"
//                        Layout.fillWidth: true
//                        text: transaction.amount.total
//                        inputMethodHints: Qt.ImhFormattedNumbersOnly
//                        onTextChanged: if (text.length > 0) { transaction.amount.total = parseFloat(text) } else { transaction.amount.total = 0.0 }
//                    }

//                    TextField {
//                        id: totalAmountCurrency
//                        placeholderText: "Currency"
//                        Layout.fillWidth: true
//                        text: transaction.amount.currency
//                        onTextChanged: transaction.amount.currency = text
//                    }
//                }
//            }

            GroupBox {
                title: "Description (required)"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    TextField {
                        id: descField
                        placeholderText: "Description"
                        Layout.fillWidth: true
                        text: transaction.description
                        onTextChanged: transaction.description = text
                    }

                    Text {
                        text: "Description of what is being paid for. Maximum length: 127"
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                        Layout.preferredWidth: 290
                    }
                }
            }

            GroupBox {
                title: "Items (optional)"
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent

                    Repeater {
                        model: transaction.itemList ? transaction.itemList : null

                        Item {
                            Layout.fillWidth: true
                            height: itemRow.height

                            RowLayout {
                                id: itemRow
                                anchors { left: parent.left; right: parent.right }

                                Column {
                                    Layout.fillWidth: true

                                    Text {
                                        text: qsTr("%1x %2").arg(model.item.quantity).arg(model.item.name)
                                        width: parent.width
                                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                    }

                                    Text {
                                        text: qsTr("%1 %2").arg(model.item.currency).arg(model.item.price)
                                        width: parent.width
                                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                    }
                                }

                                Button {
                                    id: itemEditButton
                                    iconName: "document-edit"
                                    Layout.alignment: Qt.AlignTop
                                    onClicked: stack.push({item: Qt.resolvedUrl("Item.qml"), properties:{item: model.item}})
                                }

                                Button {
                                    id: itemDelButton
                                    iconName: "entry-delete"
                                    Layout.alignment: Qt.AlignTop
                                    onClicked: transaction.itemList.removeItem(model.index)
                                }
                            }
                        }
                    }

                    Button {
                        text: "Add Item"
                        Layout.alignment: Qt.AlignHCenter
                        onClicked: stack.push({item: Qt.resolvedUrl("Item.qml"), properties:{item: transaction.addNewItem()}})
                    }
                }
            }
        }
    }
}
