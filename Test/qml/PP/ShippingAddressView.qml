import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

Item {
    property PPShippingAddress a: null

    height: grid.height

    ColumnLayout {
        id: grid

        LabeledText { label: "Recipient"; text: a ? a.recipientName : "" }
        LabeledText { label: "Street 1"; text: a ? a.line1 : "" }
        LabeledText { label: "Street 2"; text: a ? a.line2 : "" }
        LabeledText { label: "State"; text: a ? a.state : "" }
        LabeledText { label: "City"; text: a ? a.city : "" }
        LabeledText { label: "CC & ZIP"; text: a ? String("%1 %2").arg(a.countryCode).arg(a.postalCode) : "" }
        LabeledText { label: "Phone"; text: a ? a.phone : "" }
        LabeledText { label: "Type"; text: a ? a.type : "" }
        LabeledText { label: "Satus"; text: a ? a.status : "" }
    }

}
