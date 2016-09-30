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
                text: pa ? pa.total : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.total = parseFloat(text) } else { pa.total = 0.0 }
            }

            LabeledTextField {
                label: "Subtotal (optional)"
                text: pa ? pa.subtotal : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.subtotal = parseFloat(text) } else { pa.subtotal = 0.0 }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            LabeledTextField {
                label: "Shipping (optional)"
                text: pa ? pa.shipping : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.shipping = parseFloat(text) } else { pa.shipping = 0.0 }
            }

            LabeledTextField {
                label: "Shipping Discount (optional)"
                text: pa ? pa.shippingDiscount : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.shippingDiscount = parseFloat(text) } else { pa.shippingDiscount = 0.0 }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            LabeledTextField {
                label: "Tax (optional)"
                text: pa ? pa.tax : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.tax = parseFloat(text) } else { pa.tax = 0.0 }
            }

            LabeledTextField {
                label: "Insurance (optional)"
                text: pa ? pa.insurance : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.insurance = parseFloat(text) } else { pa.insurance = 0.0 }
            }
        }


        RowLayout {
            Layout.fillWidth: true

            LabeledTextField {
                label: "Handling Fee (optional)"
                text: pa ? pa.handlingFee : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.handlingFee = parseFloat(text) } else { pa.handlingFee = 0.0 }
            }

            LabeledTextField {
                label: "Gift Wrap (optional)"
                text: pa ? pa.giftWrap : 0
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                onTextChanged: if (text.length > 0 && pa) { pa.giftWrap = parseFloat(text) } else { pa.giftWrap = 0.0 }
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
