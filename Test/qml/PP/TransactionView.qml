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

        Label { text: "Items"; font.bold: true; visible: t && t.itemList }

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
    }
}
