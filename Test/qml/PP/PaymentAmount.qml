/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/PaymentAmount.qml
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
import "../common"

GroupBox {
    id: root

    property PPPaymentAmount pa: null

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            LabeledTextField {
                label: "Total"
                text: pa ? pa.total.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.total = Number.fromLocaleString(Qt.locale(), text) } else { pa.total = 0.0 }
            }

            LabeledTextField {
                label: "Subtotal (optional)"
                text: pa ? pa.subtotal.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.subtotal = Number.fromLocaleString(Qt.locale(), text) } else { pa.subtotal = 0.0 }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            LabeledTextField {
                label: "Shipping (optional)"
                text: pa ? pa.shipping.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.shipping = Number.fromLocaleString(Qt.locale(), text) } else { pa.shipping = 0.0 }
            }

            LabeledTextField {
                label: "Shipping Discount (optional)"
                text: pa ? pa.shippingDiscount.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.shippingDiscount = Number.fromLocaleString(Qt.locale(), text) } else { pa.shippingDiscount = 0.0 }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            LabeledTextField {
                label: "Tax (optional)"
                text: pa ? pa.tax.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.tax = Number.fromLocaleString(Qt.locale(), text) } else { pa.tax = 0.0 }
            }

            LabeledTextField {
                label: "Insurance (optional)"
                text: pa ? pa.insurance.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.insurance = Number.fromLocaleString(Qt.locale(), text) } else { pa.insurance = 0.0 }
            }
        }


        RowLayout {
            Layout.fillWidth: true

            LabeledTextField {
                label: "Handling Fee (optional)"
                text: pa ? pa.handlingFee.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.handlingFee = Number.fromLocaleString(Qt.locale(), text) } else { pa.handlingFee = 0.0 }
            }

            LabeledTextField {
                label: "Gift Wrap (optional)"
                text: pa ? pa.giftWrap.toLocaleString() : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.giftWrap = Number.fromLocaleString(Qt.locale(), text) } else { pa.giftWrap = 0.0 }
            }
        }

        TextField {
            placeholderText: "Currency"
            Layout.fillWidth: true
            text: pa ? pa.currency : ""
            onTextChanged: if (pa) { pa.currency = text }
        }
    }
}
