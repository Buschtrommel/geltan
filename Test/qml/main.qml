/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/main.qml
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
                text: stack.currentItem ? stack.currentItem.pageTitle : "Geltan Test"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            ToolButton {
                tooltip: "Configuration"
                iconName: "configure"
                enabled: stack.currentItem ? stack.currentItem.objectName !== "settingsView" : true
                onClicked: stack.push({item: Qt.resolvedUrl("Settings.qml")})
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: MainView {}
    }
}
