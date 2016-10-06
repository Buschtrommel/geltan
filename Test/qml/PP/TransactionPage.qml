import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtWebEngine 1.2
import Buschtrommel.Geltan.PayPal 1.0

ScrollView {
    id: ppTransactionPage
    objectName: "transactionPage"
    property int margin: 10
    width: parent.width
    height: parent.height

    property string pageTitle: "Transaction"

    property alias transaction: trView.t

    Flickable {
        id: ppTransactionPageFlick
        anchors.fill: parent
        contentHeight: trView.height + margin

        TransactionView {
            id: trView
            anchors { left: parent.left; top: parent.top; right: parent.right; margins: margin }
        }
    }

}
