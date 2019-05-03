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
    height: 600
    color: "#99000000"
    title: qsTr("QLineSolver")

    Image { source: "images/bg.png"; fillMode: Image.PreserveAspectCrop; anchors.fill: parent;  opacity: 0.3 }

    Rectangle {
        id: rectangle1
        x: 100
        y: 30
        width: 600
        height: 200
        color: "#b3424242"
        radius: 15

        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#b3424242"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }

        border.width: 2
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        Button {
            x: 37
            y: 62
            text: "Open File"
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
            x: 433
            y: 62
            text: "run optimization"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked: runSignal(qsTr(filename.text))
        }

        ProgressBar {
            id: runProgressBar
            x: 67
            y: 139
            width: 466
            height: 29
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            value: 0.5
        }


    }

    Rectangle {
        id: rectangle
        x: 100
        y: 250
        width: 600
        height: 320
        color: "#b3424242"
        radius: 15

        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#b3424242"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }

        border.width: 2
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        GridLayout {

            id: grid_layout
            anchors.fill: parent
            rows: 0

            columnSpacing: 44
            rowSpacing: 10

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            columns: 4

            Text {
                color: "orange"
                text: qsTr("Points")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
            }
            Text {
                color: "orange"
                text: qsTr("X")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
                horizontalAlignment: Text.AlignLeft
            }
            Text {
                color: "orange"
                text: qsTr("Y")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
            }
            Text {
                color: "orange"
                text: qsTr("Z")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
            }
            Text {
                color: "orange"
                text: qsTr("First")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("Second")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("Check")
                font.pointSize: 20
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.bold: true
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }

            Text {
                color: "orange"
                text: qsTr("0.000")
                font.pointSize: 20
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                rightPadding: 10
            }
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


}


















