import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtWebEngine 1.2

WebEngineView {
    id: webViewEngine
    anchors.fill: parent

    onUrlChanged: console.log(url)
}
