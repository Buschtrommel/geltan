import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

ColumnLayout {
    id: root
    spacing: 0

    property alias label: l.text
    property alias text: f.text
    property alias inputMethodHints: f.inputMethodHints
    property alias placeHolderText: f.placeholderText

    Label { id: l; Layout.fillWidth: true; elide: Text.ElideRight }

    TextField {
        id: f
        placeholderText: l.text
        Layout.fillWidth: true
        text: pa ? pa.total : 0
    }
}
