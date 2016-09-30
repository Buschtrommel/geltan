import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

Item {
    property PPPayer p: null
    height: grid.height

    ColumnLayout {
        id: grid

        LabeledText { label: "Payment Method"; text: p ? p.paymentMethod : "" }
        LabeledText { label: "Status"; text: p ? p.status : "" }

        PayerInfoView {
            pi: p ? p.payerInfo : null
            Layout.fillWidth: true
        }
    }

}
