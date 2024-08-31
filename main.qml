import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Window {
    visible: true
    width: 900
    height: 700
    title: qsTr("Word rating")
    //property bool showProgress: false

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "#71BC78"
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 10

        FileSelector{
            Layout.maximumHeight: 50
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        CustomHistogram {
            id: histogram
            Layout.fillHeight: true
            Layout.fillWidth: true

        }
        CustomProgressBar {
            id: progressBar
            Layout.maximumHeight: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
            //visible: showProgress
        }

        RowLayout {
            StartButton {
                id: startButton
                Layout.maximumHeight: 50
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            PauseButton {
                id: pauseButton
                Layout.maximumHeight: 50
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: {
                    progressBar.val = progressBar.val + 10
                }
            }

            CanselButton {
                id: canselButton
                Layout.maximumHeight: 50
                Layout.fillHeight: true
                Layout.fillWidth: true
                onClicked: {
                    progressBar.val = progressBar.val - 10
                }
            }

        } //RowLayout

    } // ColumnLayout

    Logger {}
}
