/* Geltan Test - geltan library test application
 * Copyright (C) 2016 Buschtrommel/Matthias Fehring
 * Contact: https://www.buschmann23.de
 *
 * Test/qml/PP/TransactionPage.qml
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
