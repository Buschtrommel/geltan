import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

RowLayout {

    property real labelMinWidth: 90
    property PPCurrency c: null
    property alias label: l.text

    visible: c && c.value > 0.0

    Label { id: l; Layout.minimumWidth: labelMinWidth; textFormat: Text.PlainText; visible: parent.visible }

    Text { id: t; Layout.fillWidth: true; wrapMode: Text.WrapAnywhere; textFormat: Text.PlainText; visible: parent.visible; text: c ? String("%1 %2").arg(c.currency).arg(c.value) : "" }
}
