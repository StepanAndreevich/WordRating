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

        CustomBarChart {
            id: barChart
            Layout.fillHeight: true
            Layout.fillWidth: true
            yLabel: "Кол-во вхождений"
            xLabel: "Слова"
        }

        CustomProgressBar {
            id: progressBar
            Layout.maximumHeight: 30
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RowLayout {
            StartButton {
                id: startButton
                Layout.maximumHeight: 50
                Layout.fillHeight: true
                Layout.fillWidth: true
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
