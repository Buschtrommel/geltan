/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/SaleView.qml
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
    property PPSale s: null
    property alias label: l.text

    height: col.height

    ColumnLayout {
        id: col

        Label { id: l; font.bold: true; visible: text }

        LabeledText { label: "ID"; text: s ? s.id : ""}
        LabeledText { label: "Purchase Unit"; text: s ? s.purchaseUnitReferenceId : "" }

        PaymentAmountView {
            Layout.fillWidth: true
            a: s.amount
        }

        LabeledText { label: "State"; text: s ? s.state : "" }
        LabeledText { label: "Reason Code"; text: s ? s.reasonCode : "" }
        LabeledText { label: "Protection Eligibility"; text: s ? s.protectionEligibility : "" }
        LabeledText { label: "Clearing Time"; text: s ? Qt.formatDateTime(s.clearingTime, Qt.DefaultLocaleShortDate) : "" }
        LabeledText { label: "Payment Hold Status"; text: s ? s.paymentHoldStatus : "" }
        LabeledTextList { label: "Payment Hold Reasons"; model: s ? s.paymentHoldReasons : null }
        CurrencyView { label: "Transaction Fee"; c: s ? s.transactionFee : null }
        CurrencyView { label: "Receivable Amount"; c: s ? s.receivableAmount : null }
        LabeledText { label: "Exchange Rate"; text: s ? s.exchangeRate : ""; visible: s && s.exchangeRate > 0.0 }
        FMFDetailsView { fmf: s ? s.fmfDetails : null }
        LabeledText { label: "Receipt ID"; text: s ? s.receiptId : "" }
        LabeledText { label: "Parent Payment"; text: s ? s.parentPayment : "" }
        ProcessorResponseView { pr: s ? s.processorResponse : "" }
        LabeledText { label: "Billing Agreement ID"; text: s ? s.billingAgreementId : "" }
        LabeledText { label: "Created"; text: s ? Qt.formatDateTime(s.createTime, Qt.DefaultLocaleShortDate) : "" }
        LabeledText { label: "Updated"; text: s ? Qt.formatDateTime(s.updateTime, Qt.DefaultLocaleShortDate) : "" }
    }

}
