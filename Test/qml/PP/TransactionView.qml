/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/TransactionView.qml
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
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

Item {
    property PPTransaction t: null
    height: col.height

    ColumnLayout {
        id: col

        LabeledText { label: "Ref ID"; text: t ? t.referenceId : "" }

        LabeledText { label: "Desc."; text: t ? t.description : "" }

        PaymentAmountView {
            a: t.amount
            Layout.fillWidth: true
        }

        LabeledText { label: "Note"; text: t ? t.noteToPayee : "" }

        LabeledText { label: "Custom"; text: t ? t.custom : "" }

        LabeledText { label: "Soft Desc."; text: t ? t.softDescriptor : "" }

        LabeledText { label: "Notify URL"; text: t ? t.notifyUrl : "" }

        LabeledText { label: "Order URL"; text: t ? t.orderUrl : "" }

        Label { text: "Payee"; font.bold: true; visible: t && t.payee }

        PayeeView {
            payee: t ? t.payee : null
            Layout.fillWidth: true
        }

        Label { text: "Shipping Address"; font.bold: true; visible: t && t.itemList && t.itemList.shippingAddress  }

        ShippingAddressView {
            a: t && t.itemList && t.itemList.shippingAddress ? t.itemList.shippingAddress : null
            Layout.fillWidth: true
        }

        Label { text: "Items"; font.bold: true; visible: t && t.itemList; font.underline: true }

        Repeater {
            model: t ? t.itemList : null

            RowLayout {
                Layout.fillWidth: true

                Text { id: noText; text: String("#%1").arg(model.index + 1); Layout.alignment: Qt.AlignLeft | Qt.AlignTop }

                ItemDisplay {
                    i: model.item
                    Layout.fillWidth: true
                    labelMinWidth: 90 - noText.width - parent.spacing
                }
            }
        }

        Label { text: "Related"; font.bold: true; font.underline: true }

        Repeater {

            model: t

            Loader {
                id: relLoader
                Layout.fillWidth: true
                Component.onCompleted: {
                    if (model.sale) {
                        relLoader.setSource(Qt.resolvedUrl("SaleView.qml"), {"s": model.sale, "label": "Sale"})
                    }
                }
            }
        }
    }
}
