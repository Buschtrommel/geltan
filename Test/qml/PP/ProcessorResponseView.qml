import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

ColumnLayout {
    anchors { left: parent.left; right: parent.right }

    property PPProcessorResponse pr :null

    visible: pr

    LabeledText { label: "Response Code"; text: pr ? pr.responseCode : "" }
    LabeledText { label: "AVS Code"; text: pr ? pr.avsCode : "" }
    LabeledText { label: "CVV Code"; text: pr ? pr.cvvCode : "" }
    LabeledText { label: "Advice Code"; text: pr ? pr.adviceCode : "" }
    LabeledText { label: "ECI Submitted"; text: pr ? pr.eciSubmitted : "" }
    LabeledText { label: "VPAS"; text: pr ? pr.vpas : "" }
}
