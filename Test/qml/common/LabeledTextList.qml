import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

RowLayout {

    property real labelMinWidth: 90

    property alias label: l.text
    property alias model: rep.model

    visible: rep.count > 0

    Label { id: l; Layout.minimumWidth: labelMinWidth; textFormat: Text.PlainText; visible: parent.visible }

    Repeater {
        id: rep

        Text { id: t; Layout.fillWidth: true; wrapMode: Text.WrapAnywhere; textFormat: Text.PlainText; visible: parent.visible; text: model.data }

    }
}
