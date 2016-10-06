import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

ScrollView {
    id: settingsView
    objectName: "settingsView"
    width: parent.width
    height: parent.height

    property string pageTitle: "Settings"

    Flickable {
        anchors.fill: parent
        contentHeight: mainCol.height

        ColumnLayout {
            id: mainCol
            width: parent.width

            GroupBox {
                title: "PayPal"
                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            id: paypalclientidLabel
                            text: "Client ID"
                            Layout.minimumWidth: Math.max(paypalSecretLabel.contentWidth, paypalclientidLabel.contentWidth)
                        }

                        TextField {
                            id: paypalclientid
                            placeholderText: "Client ID"
                            Layout.fillWidth: true
                            text: config.payPalClientID

                            Binding { target: config; property: "payPalClientID"; value: paypalclientid.text }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            id: paypalSecretLabel
                            text: "Secret"
                            Layout.minimumWidth: Math.max(paypalSecretLabel.contentWidth, paypalclientidLabel.contentWidth)
                        }

                        TextField {
                            id: paypalSecret
                            placeholderText: "Secret"
                            Layout.fillWidth: true
                            text: config.payPalSecret

                            Binding { target: config; property: "payPalSecret"; value: paypalSecret.text }
                        }
                    }

                    Label {
                        Layout.fillWidth: true
                        text: "Default Values"
                        font.bold: true
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: "Return URL"
                        }

                        TextField {
                            id: ppReturnUrl
                            placeholderText: "Return URL"
                            Layout.fillWidth: true
                            text: config.paypalReturnUrl

                            Binding { target: config; property: "paypalReturnUrl"; value: ppReturnUrl.text }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: "Cancel URL"
                        }

                        TextField {
                            id: ppCancelUrl
                            placeholderText: "Cancel URL"
                            Layout.fillWidth: true
                            text: config.paypalCancelUrl

                            Binding { target: config; property: "paypalCancelUrl"; value: ppCancelUrl.text }
                        }
                    }
                }

            }
        }
    }
}
