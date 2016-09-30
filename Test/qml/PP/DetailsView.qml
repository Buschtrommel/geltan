import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0
import "../common"

Item {
    property string curr
    property PPDetails d: null

    visible: d

    height: grid.height

    ColumnLayout {
        id: grid

        LabeledText { label: "Subtotal"; text: d ? String("%1 %2").arg(curr).arg(Number(d.subtotal).toLocaleString()) : ""; visible: d && d.subtotal }

        LabeledText { label: "Shipping"; text: d ? String("%1 %2").arg(curr).arg(Number(d.shipping).toLocaleString()) : ""; visible: d && d.shipping }

        LabeledText { label: "Tax"; text: d ? String("%1 %2").arg(curr).arg(Number(d.tax).toLocaleString()) : ""; visible: d && d.tax }

        LabeledText { label: "Handling Fee"; text: d ? String("%1 %2").arg(curr).arg(Number(d.handlingFee).toLocaleString()) : ""; visible: d && d.handlingFee }

        LabeledText { label: "Shipping Discount"; text: d ? String("%1 %2").arg(curr).arg(Number(d.shippingDiscount).toLocaleString()) : ""; visible: d && d.shippingDiscount }

        LabeledText { label: "Insurance"; text: d ? String("%1 %2").arg(curr).arg(Number(d.insurance).toLocaleString()) : ""; visible: d && d.insurance }

        LabeledText { label: "Gift Wrap"; text: d ? String("%1 %2").arg(curr).arg(Number(d.giftWrap).toLocaleString()) : ""; visible: d && d.giftWrap }
    }

}
