import QtQuick 2.0
import QtQuick.Controls 2.5

Button {
    id: startButton
    text: "Старт"
    wheelEnabled: false
    font.family: "Verdana"
    font.pointSize: 14
    background: Rectangle {
        anchors.fill: parent
        color: startButton.down ? Qt.darker("white", 2.0) : "white"
        radius: 10
        border.color: "black"
        border.width: 1
        opacity: 0.7
    }
    onClicked: {
        mainWindow.start()
    }
}
