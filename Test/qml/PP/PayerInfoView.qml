/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/PayerInfoView.qml
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
    property PPPayerInfo pi: null
    height: grid.height

    ColumnLayout {
        id: grid

        LabeledText { label: "ID"; text: pi ? pi.payerId : "" }

        LabeledText { label: "Salutation"; text: pi ? pi.salutation : "" }

        LabeledText { label: "Name"; text: pi ? String("%1 %2").arg(pi.firstName).arg(pi.lastName) : "" }

        LabeledText { label: "Suffix"; text: pi ? pi.suffix : "" }

        LabeledText { label: "Email"; text: pi ? pi.email : "" }

        LabeledText { label: "Phone"; text: pi ? pi.phone : "" }

        LabeledText { label: "Phone Type"; text: pi ? pi.phoneType : "" }

        LabeledText { label: "Birth Date"; text: pi ? Qt.formatDateTime(pi.birthDate, "YYYY-MM-dd") : "" }

        LabeledText { label: "Tax ID"; text: pi ? pi.taxId : "" }

        LabeledText { label: "Tax ID Type"; text: pi ? pi.taxIdType : "" }

        LabeledText { label: "Country Code"; text: pi ? pi.countryCode : "" }

        Label { text: "Payer Billing Address"; font.bold: true; visible: pi && pi.billingAddress }

        AddressView {
            Layout.fillWidth: true
            a: pi.billingAddress
            visible: pi && pi.billingAddress
        }
    }

}
