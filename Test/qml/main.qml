import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: geltanTest
    visible: true
    title: "Geltan Test"

    width: config.applicationWidth
    height: 640

    minimumWidth: 320

    Component.onDestruction: config.applicationWidth = width

    toolBar: ToolBar {
        RowLayout {
            spacing: 0
            anchors.fill: parent

            ToolButton {
                tooltip: "Back"
                iconName: "go-previous"
                enabled: stack.depth > 1
                onClicked: stack.pop()
            }

            Label {
                id: pt
                text: stack.currentItem.pageTitle
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            ToolButton {
                tooltip: "Configuration"
                iconName: "configure"
                enabled: stack.currentItem.objectName !== "settingsView"
                onClicked: stack.push({item: Qt.resolvedUrl("Settings.qml")})
//                Layout.alignment: Qt.AlignRight
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: MainView {}
    }
}
