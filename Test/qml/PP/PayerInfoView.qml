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

        Label { text: "Payer Shipping Address"; font.bold: true; visible: pi.shippingAddress }

        ShippingAddressView {
            Layout.fillWidth: true
            a: pi.shippingAddress
            visible: pi.shippingAddress
        }

        Label { text: "Payer Billing Address"; font.bold: true; visible: pi.billingAddress }

        AddressView {
            Layout.fillWidth: true
            a: pi.billingAddress
            visible: pi.billingAddress
        }
    }

}
