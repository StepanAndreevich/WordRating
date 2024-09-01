import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    id: root
    property string filePath: ""//"C:/Users/Stepa/OneDrive/Рабочий стол/light_example.txt"

    RowLayout {
        id: fileLayout
        anchors.fill: parent
        Rectangle {
            id: textRect
            radius: 10
            Layout.maximumHeight: 70
            Layout.maximumWidth: 65535
            border.width: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            opacity: 0.7
            TextEdit {
                id: input
                text: filePath
                textMargin: 5
                font.family: "Verdana"
                font.pointSize: 14
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                mouseSelectionMode: TextEdit.SelectCharacters
                selectByMouse: true

                onTextChanged: {
                    mainWindow.setFilePath(input.text)
                }
            }

        } //Rectangle

        Button {
            id: selectFileButton
            width: 70
            text: "Открыть"
            Layout.minimumWidth: 100
            Layout.maximumHeight: 70
            Layout.maximumWidth: 65535
            Layout.fillHeight: true
            Layout.fillWidth: false
            font.pointSize: 10
            background: Rectangle {
                anchors.fill: parent
                color: selectFileButton.down ? Qt.darker("white", 2.0) : "white"
                radius: 10
                border.color: "black"
                border.width: 1
                opacity: 0.7
            }

            onClicked: {
                fileDialog.open()
            }
        }//Button

    } //RowLayout

    FileDialog {
        id: fileDialog
        title: "Выберите файл"
        folder: shortcuts.home
        nameFilters: ["All Files (*.txt)"]
        onAccepted: {
             filePath = mainWindow.fixFilePath(fileDialog.fileUrl)
        }
        onRejected: {
            filePath = ""
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_x:208;anchors_y:87}
}
##^##*/
