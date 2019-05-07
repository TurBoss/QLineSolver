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
import QtMultimedia 5.8

ApplicationWindow {
    signal runSignal(string file_url)

    signal volumeSignal()
    signal pauseSignal()
    signal playSignal()
    signal nextSignal()

    id: root
    visible: true
    width: 600
    height: 225

    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width

    color: "#00000000"
    title: qsTr("QLineSolver")

    flags: Qt.Window | Qt.FramelessWindowHint

    Audio {
        id: audioPlayer
        source: "music/jaume.wav"
    }

    MouseArea {
        anchors.fill: parent;
        property variant clickPos: "1,1"

        onPressed: {
            clickPos = Qt.point(mouse.x,mouse.y)
        }

        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            var new_x = root.x + delta.x
            var new_y = root.y + delta.y
            if (new_y <= 0)
                root.visibility = Window.Maximized
            else
            {
                if (root.visibility === Window.Maximized)
                    root.visibility = Window.Windowed
                root.x = new_x
                root.y = new_y
            }
        }
    }


    Rectangle {
        id: rectangle1

        width: parent.width
        height: parent.height
        color: "#000000"
        radius: 20
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
        anchors.rightMargin: 97
        anchors.bottomMargin: 16
        anchors.leftMargin: 97
        anchors.topMargin: 16

        border.width: 3
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        Image {
            z: -1
            anchors.rightMargin: 0;
            anchors.bottomMargin: 0;
            source: "images/bg.svg"
            fillMode: Image.PreserveAspectCrop;
            anchors.fill: parent;
            opacity: 0.8
        }

        Text {
            id: element
            x: 206
            y: 140
            width: 331
            height: 58
            color: "#ffa500"
            text: qsTr("QLineSolver")
            visible: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignLeft
            font.family: "Arial"
            font.bold: true
            z: 2
            font.pixelSize: 48

            Rectangle {
                id: rectangle
                x: 242
                y: -128
                width: 140
                height: 45
                color: "#b3000000"
                radius: 20
                border.color: "#000000"
                opacity: 1
                border.width: 3

                Image {
                    id: image
                    x: 16
                    y: 4
                    width: 110
                    height: 35
                    source: "images/miniplayer.svg"
                    fillMode: Image.Stretch

                    Image {
                        id: image1
                        x: 12
                        y: 5
                        width: 19
                        height: 25
                        source: "images/volumen.svg"
                        fillMode: Image.PreserveAspectFit
                    }
                }

                MouseArea {
                    id: volumeArea
                    x: 16
                    y: 8
                    width: 33
                    height: 27
                    onClicked: {audioPlayer.volume = 1.0}
                }

                MouseArea {
                    id: pauseArea
                    x: 49
                    y: 9
                    width: 22
                    height: 26
                    onClicked: {audioPlayer.pause()}
                }

                MouseArea {
                    id: playArea
                    x: 72
                    y: 9
                    width: 25
                    height: 26
                    onClicked: {audioPlayer.play()}
                }

                MouseArea {
                    id: nextArea
                    x: 96
                    y: 9
                    width: 25
                    height: 26
                }
            }
        }

        Text {
            x: 206
            y: 44
            width: 125
            height: 27
            color: "orange"
            text: qsTr("File loaded:")
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignLeft
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            font.pointSize: 18
            font.bold: true
        }

        Text {
            color: "orange"
            id: filename
            x: 206
            y: 99
            width: 336
            height: 27
            text: qsTr("None")
            font.bold: true
            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 10
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
        }

        Rectangle {
            id: load_rectangle
            x: 32
            y: 38
            width: 150
            height: 39
            color: "#cc000000"
            radius: 20
            border.width: 3

            MouseArea {
                id: load_mouseArea
                anchors.fill: parent;
                onClicked: fileDialog.visible = true
            }

            Text {
                id: load_text
                anchors.fill: parent;
                color: "#ffa500"
                text: qsTr("LOAD")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 17
            }
        }
        Rectangle {
            id: run_rectangle
            x: 32
            y: 93
            width: 150
            height: 39
            color: "#cc000000"
            radius: 20
            border.width: 3

            MouseArea {
                id: run_mouseArea
                anchors.fill: parent;
                onClicked: runSignal(qsTr(filename.text))
            }

            Text {
                id: run_text
                anchors.fill: parent;
                color: "#ffa500"
                text: qsTr("RUN")
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: quit_rectangle
            x: 32
            y: 149
            width: 150
            height: 39
            color: "#cc000000"
            radius: 20
            border.width: 3
            MouseArea {
                id: quit_mouseArea
                anchors.fill: parent;
                onClicked: messageDialogQuit.open()
            }

            Text {
                id: quit_text
                anchors.fill: parent;
                color: "#ffa500"
                text: qsTr("QUIT")
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                font.pixelSize: 17
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                verticalAlignment: Text.AlignVCenter
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










