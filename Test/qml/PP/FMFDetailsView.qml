import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

ColumnLayout {
    anchors { left: parent.left; right: parent.right }

    property PPFMFDetails fmf: null

    visible: fmf

    LabeledText { label: "Filter Type"; text: fmf ? fmf.filterType : "" }
    LabeledText { label: "Filter ID"; text: fmf ? fmf.filterId : "" }
    LabeledText { label: "Name"; text: fmf ? fmf.name : "" }
    LabeledText { label: "Description"; text: fmf ? fmf.description : "" }

}
