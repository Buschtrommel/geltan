/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/Payments/List.qml
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
import "../../common"

ScrollView {
    id: ppPaymentsListView
    objectName: "listPayPalPaymentsView"
    property int margin: 10
    width: parent.width
    height: parent.height

    property string pageTitle: "List PayPal Payments"

    Flickable {
        anchors.fill: parent
        contentHeight: col.visible ? col.height + margin : height

        ListPayments {
            id: ppListPayments
            token: config.payPalToken
            tokenType: config.payPalTokenType
            append: true
        }

        BusyIndicator {
            anchors.centerIn: parent
            running: ppListPayments.inOperation
        }

        ColumnLayout {
            id: col
            anchors { left: parent.left; right: parent.right; top: parent.top; margins: margin }
            visible: !ppListPayments.inOperation

            LabeledTextField {
                id: countField
                label: "Count"
                text: ppListPayments.count
                inputMethodHints: Qt.ImhDigitsOnly
                onTextChanged: if (text.length > 0) { ppListPayments.count = parseInt(text) } else { ppListPayments.count = 0 }
                visible: !ppListPayments.paymentList
            }

            LabeledTextField {
                id: startIdField
                label: "Start ID"
                onTextChanged: ppListPayments.startId = text
                visible: !ppListPayments.paymentList
            }

            LabeledTextField {
                id: startIndexField
                label: "Start Index"
                text: ppListPayments.startIndex
                inputMethodHints: Qt.ImhDigitsOnly
                onTextChanged: if (text.length > 0) { ppListPayments.startIndex = parseInt(text) } else { ppListPayments.startIndex = 0 }
                visible: !ppListPayments.paymentList
            }

            Label { text: "Start Time"; visible: !ppListPayments.paymentList }

            Calendar {
                Layout.fillWidth: true
                onClicked: ppListPayments.startTime = date
                visible: !ppListPayments.paymentList
            }

            Label { text: "End Time"; visible: !ppListPayments.paymentList }

            Calendar {
                Layout.fillWidth: true
                onClicked: ppListPayments.endTime = date
                visible: !ppListPayments.paymentList
            }

            Label { text: "Sort By"; visible: !ppListPayments.paymentList }

            ComboBox {
                Layout.fillWidth: true
                textRole: "text"
                model: ListModel {
                    id: sortByModel
                    ListElement { text: "Update Time"; value: ListPayments.UpdateTime }
                    ListElement { text: "Create Time"; value: ListPayments.CreateTime }
                }
                onCurrentIndexChanged: ppListPayments.sortBy = sortByModel.get(currentIndex).value
                visible: !ppListPayments.paymentList
            }

            Label { text: "Sort Order"; visible: !ppListPayments.paymentList }

            ComboBox {
                Layout.fillWidth: true
                textRole: "text"
                model: ListModel {
                    id: sortOrderModel
                    ListElement { text: "Ascending"; value: Qt.AscendingOrder }
                    ListElement { text: "Descending"; value: Qt.DescendingOrder }
                }
                onCurrentIndexChanged: ppListPayments.sortOrder = sortOrderModel.get(currentIndex).value
                visible: !ppListPayments.paymentList
            }

            Button {
                text: "Load Payments"
                Layout.alignment: Qt.AlignHCenter
                onClicked: ppListPayments.call()
                visible: !ppListPayments.paymentList
            }

            Repeater {
                model: ppListPayments.paymentList
                Rectangle {
                    Layout.fillWidth: true
                    height: itemCol.height + 10
                    color: "transparent"
                    border.width: lima.containsMouse ? 1 : 0
                    border.color: "black"

                    MouseArea {
                        id: lima // list item mouse area
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: stack.push(Qt.resolvedUrl("../PaymentPage.qml"), {payment: model.item})
                    }

                    ColumnLayout {
                        id: itemCol
                        width: parent.width

                        Label { text: model.id; Layout.fillWidth: true }

                        RowLayout {
                            Text {
                                text: model.item.state === Payment.Created ? "Created" : model.item.state === Payment.Approved ? "Approved" : "Failed"
                            }
                            Text {
                                text: model.item.intent === Payment.Sale ? "Sale" : model.item.intent === Payment.Authorize ? "Authorization" : "Order"
                            }
                            Text {
                                Layout.fillWidth: true
                                text: model.createTime
                                horizontalAlignment: Text.AlignRight
                            }
                        }

                        Repeater {
                            model: item

                            RowLayout {
                                Text {
                                    visible: amount
                                    text: amount ? amount.currency : ""
                                }

                                Text {
                                    visible: amount
                                    text: amount ? amount.total : ""
                                }

                                Text {
                                    visible: description
                                    text: description
                                }
                            }
                        }
                    }
                }
            }

            Button {
                text: "Load more"
                visible: !ppListPayments.inOperation && ppListPayments.paymentList && ppListPayments.paymentList.nextId !== ""
                onClicked: { ppListPayments.startId = ppListPayments.paymentList.nextId; ppListPayments.call() }
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }
}
