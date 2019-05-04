// This file is part of QLineSolver
// Copyright 2019 Metal and TurBoss

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    signal runSignal(string file_url)

    id: root
    visible: true
    width: 800
    height: 250
    color: "#99000000"
    title: qsTr("QLineSolver")

    flags: Qt.Window | Qt.FramelessWindowHint

    Rectangle {
        id: rectangle1

        width: parent.width
        height: parent.height
        color: "#00000000"
        radius: 20
        anchors.rightMargin: 97
        anchors.bottomMargin: 16
        anchors.leftMargin: 97
        anchors.topMargin: 16
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#00000000"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }

        border.width: 3
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        Button {
            id: close_button
            x: 612
            y: 151
            width: 130
            height: 40
            text: qsTr("Quit")
            spacing: 8
            onClicked: messageDialogQuit.open()
        }

        Image {
            anchors.rightMargin: 0;
            anchors.bottomMargin: 0;
            source: "images/bg.png";
            fillMode: Image.PreserveAspectCrop;
            anchors.fill: parent;
            opacity: 0.3
        }

        Button {
            id: open_button
            x: 37
            y: 151
            width: 130
            text: "Load"

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: fileDialog.visible = true
        }

        Text {
            x: 24
            y: 17
            width: 125
            height: 27
            color: "orange"
            text: qsTr("File loaded:")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            font.pointSize: 18
            font.bold: true
        }

        Text {
            color: "orange"
            id: filename
            x: 150
            y: 21
            width: 404
            height: 27
            text: qsTr("None")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 10
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
        }

        Button {
            x: 335
            y: 151
            width: 130
            text: "Run"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: runSignal(qsTr(filename.text))
        }


    }

    FileDialog {
        id: fileDialog
        title: qsTr("Please choose GCode file")
        nameFilters: ["Gcode Files (*.ngc *.tap *.nc)"];
        folder: shortcuts.home
        onAccepted: {
            //console.log("You chose: " + fileDialog.fileUrl)

            var path = fileDialog.fileUrl.toString();
            filename.text = path
            fileDialog.close()
        }
        onRejected: {
            // console.log("Canceled")
            fileDialog.close()
        }
    }

    MessageDialog {
        id: messageDialogQuit
        title: "Quit?"
        icon: StandardIcon.Question
        text: "Really?."

        standardButtons: StandardButton.Yes | StandardButton.No
        // Component.onCompleted: visible = true
        onYes: Qt.quit()
        // onNo: console.log("didn't copy")
    }

    onClosing:{
        close.accepted = false
        onTriggered: messageDialogQuit.open()
    }
}










