import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Item {
    property int fromNum: 0
    property int toNum: 100
    property real val: 0
    property bool isVisible: false

    ProgressBar {
        id: progress
        anchors.fill: parent
        width: 200
        height: 20
        from: fromNum
        to: toNum
        value : val
        visible: isVisible

        background: Rectangle {
            implicitHeight:  parent.height
            implicitWidth:  parent.width
            border.color:"black"
            opacity: 0.8
            radius: 10
        }

        contentItem: Item {
            Rectangle {
                id: progValue
                width: progress.visualPosition * parent.width
                height: parent.height
                color: "#00FF00"
                radius: 10
                border.color:"black"
            }
            Label {
                anchors.centerIn: parent
                text: (progress.value).toFixed(2) + "%"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Connections {
        target: mainWindow
        onChangeProgress: {
            if(!isVisible)
                isVisible = !isVisible
            val = value
        }
    }
}
