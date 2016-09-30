import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

ColumnLayout {
    anchors { left: parent.left; right: parent.right }

    property PPPayment py: null

    LabeledText { label: "ID"; text: py.id }
    LabeledText { label: "State"; text: py.state }
    LabeledText { label: "Created"; text: Qt.formatDateTime(py.createTime, Qt.DefaultLocaleShortDate) }

    Label { text: "Payer"; font.bold: true; font.underline: true }

    PayerView {
        p: py.payer
        Layout.fillWidth: true
    }

    Label { text: "Transactions"; font.bold: true; font.underline: true }

    Repeater {
        model: py

        RowLayout {
            Layout.fillWidth: true

            Button {
                id: trButton
                text: model.index + 1
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.maximumWidth: height
                onClicked: stack.push({item: Qt.resolvedUrl("TransactionPage.qml"), properties:{transaction: model.item}})
            }

            ColumnLayout {
                Layout.fillWidth: true

                LabeledText { label: "Total"; text: String("%1 %2").arg(model.item.amount.currency).arg(model.item.amount.total); labelMinWidth: 90 - trButton.width - parent.spacing }
                LabeledText { label: "Desc"; text: model.item.description; labelMinWidth: 90 - trButton.width - parent.spacing }
            }
        }
    }
}
