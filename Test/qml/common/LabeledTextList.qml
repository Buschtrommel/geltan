/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/common/LabeledTextList.qml
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
