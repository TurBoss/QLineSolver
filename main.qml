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
    title: qsTr("QLineSolver")

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

    ColumnLayout {
        width: 564
        height: 448


        RowLayout {
            id: row_layout
            Button {
                text: "Open File"
                onClicked: fileDialog.visible = true
            }
            Text {
                text: qsTr("File loaded:")
            }
            Text {
                id: filename
                text: qsTr("None")
            }
        }

        ProgressBar {
            id: loadProgressBar
            x: 69
            y: 349
            value: 0.5
        }

        Button {
            text: "run optimization"
            onClicked: runSignal(qsTr(filename.text))
        }

        ProgressBar {
            id: runProgressBar
            x: 69
            y: 349
            value: 0.5
        }
        GridLayout {
            id: grid_layout
            columns: 4

            Text {
                text: qsTr("Points")
            }
            Text {
                text: qsTr("X")
            }
            Text {
                text: qsTr("Y")
            }
            Text {
                text: qsTr("Z")
            }
            Text {
                text: qsTr("First")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("Second")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("Check")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("0.000")
            }

            Text {
                text: qsTr("0.000")
            }
        }
    }
}


