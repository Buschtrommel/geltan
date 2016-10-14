/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/ShippingAddressView.qml
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

Item {
    property PPShippingAddress a: null

    height: grid.height

    ColumnLayout {
        id: grid

        LabeledText { label: "Recipient"; text: a ? a.recipientName : "" }
        LabeledText { label: "Street 1"; text: a ? a.line1 : "" }
        LabeledText { label: "Street 2"; text: a ? a.line2 : "" }
        LabeledText { label: "State"; text: a ? a.state : "" }
        LabeledText { label: "City"; text: a ? a.city : "" }
        LabeledText { label: "CC & ZIP"; text: a ? String("%1 %2").arg(a.countryCode).arg(a.postalCode) : "" }
        LabeledText { label: "Phone"; text: a ? a.phone : "" }
        LabeledText { label: "Type"; text: a ? a.type : "" }
        LabeledText { label: "Satus"; text: a ? a.status : "" }
    }

}
