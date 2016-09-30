import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

Item {
    id: root
    property PPItem i: null

    property real labelMinWidth: 90

    height: grid.height

    ColumnLayout {
        id: grid

        LabeledText { label: "SKU"; text: i ? i.sku : ""; labelMinWidth: root.labelMinWidth }
        LabeledText { label: "Name"; text: i ? i.name : ""; labelMinWidth: root.labelMinWidth }
        LabeledText { label: "Description"; text: i ? i.description : ""; labelMinWidth: root.labelMinWidth }
        LabeledText { label: "Quantity"; text: i ? i.quantity : ""; visible: i.quantity; labelMinWidth: root.labelMinWidth }
        LabeledText { label: "Price"; text: i ? String("%1 %2").arg(i.currency).arg(Number(i.price).toLocaleString()) : ""; visible: i.price; labelMinWidth: root.labelMinWidth }
        LabeledText { label: "Tax"; text: i ? String("%1 %2").arg(i.currency).arg(Number(i.tax).toLocaleString()) : ""; visible: i.tax; labelMinWidth: root.labelMinWidth }
        LabeledText { label: "URL"; text: i ? i.url : ""; labelMinWidth: root.labelMinWidth }
    }

}
