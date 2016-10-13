import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import Buschtrommel.Geltan.PayPal 1.0

ScrollView {
    id: ppPaymentsListView
    objectName: "payPalPaymentPage"
    property int margin: 10
    width: parent.width
    height: parent.height

    property alias payment: pv.py
    property string pageTitle: "Payment"

    Flickable {
        anchors.fill: parent
        contentHeight: pv.height

        PaymentView {
            id: pv
        }
    }
}
