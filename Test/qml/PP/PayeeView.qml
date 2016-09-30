import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

Item {
    property PPPayee payee: null
    height: col.height

    visible: payee

    ColumnLayout {
        id: col

        LabeledText { label: "Email"; text: payee ? payee.email : "" }
        LabeledText { label: "Merchant ID"; text: payee ? payee.merchantId : "" }
    }
}
