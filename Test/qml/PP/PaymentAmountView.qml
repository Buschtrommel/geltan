import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

Item {
    property PPPaymentAmount a: null
    height: grid.height

    visible: a

    ColumnLayout {
        id: grid

        LabeledText { label: "Total"; text: a ? String("%1 %2").arg(a.currency).arg(Number(a.total).toLocaleString()) : "" }

        DetailsView {
            d: a ? a.details : null
            Layout.fillWidth: true
            curr: a ? a.currency : ""
        }
    }

}
