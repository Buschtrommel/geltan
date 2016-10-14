/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/FMFDetailsView.qml
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
