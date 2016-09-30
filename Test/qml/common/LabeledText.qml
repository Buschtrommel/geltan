import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

RowLayout {

    property real labelMinWidth: 90

    property alias label: l.text
    property alias text: t.text

    visible: text

    Label { id: l; Layout.minimumWidth: labelMinWidth; textFormat: Text.PlainText; visible: parent.visible }

    Text { id: t; Layout.fillWidth: true; wrapMode: Text.WrapAnywhere; textFormat: Text.PlainText; visible: parent.visible }
}
