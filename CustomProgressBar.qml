import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Item {
    property int fromNum: 0
    property int toNum: 100
    property int val: 0
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
                text: (progress.value).toFixed(0) + "%"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

        }
    }

//    ProgressBar {
//        id: progressBar
//        font.family: "Verdana"
//        font.pointSize: 14
//        anchors.fill: parent
//        from: fromNum
//        to: toNum
//        value: val
//        visible: isVisible
////        contentItem: Rectangle {
////            id: progressRect
////            border.color: "black"
////            color: "#00FF00"
////            radius: 10
////            //anchors.fill: parent
////            width: progressRect + progressBar.value
////        }

////        Rectangle {
////            id: whiteRect
//////            anchors.top: progressRect.top
//////            anchors.right: progressRect.right
//////            anchors.bottom: progressRect.bottom
//////            implicitWidth: progressRect.width * (1 - progressBar.value)
//////            implicitHeight: progressRect.height
////            anchors.fill: progressRect
////            //implicitWidth: whiteRect.width - progressBar.value//progressRect.width * (1 - progressBar.value)
////            border.color: "black"
////            color: "white"
////            radius: 10
////        }
//    }

    Connections {
        target: mainWindow
        onShowProgressBar: {
            isVisible = visible
        }
    }
}
