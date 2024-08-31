import QtQuick 2.12
//import QtQuick.Controls 2.5
//import QtQuick.Layouts 1.3
//import QtQuick.Dialogs 1.2
import QtCharts 2.3

Item {
    id: root
    property string resultText: ""
    property var words: []
    property var wordsCount: []

    Rectangle {
        id: rect
        anchors.fill: parent
        border.color: "black"
        radius: 10
        opacity: 0.7

        Canvas {
            id: canvas
            anchors.fill: parent
            width: rect.width
            height: rect.height
            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 20
                ctx.strokeStyle = "#287233"
                drawLines(ctx)
            }

            function drawLines(ctx)
            {
                var step = 40;
                ctx.beginPath()
                for(var i = 0; i < 15; i++)
                {
                    ctx.moveTo(step + i, parent.height)
                    ctx.lineTo(step + i, parent.height / 2)
                    ctx.font = "14pt Verdana";
                    ctx.fillText("Hello", step + i - 20, (parent.height / 2) - 5)
                    step += 40
                }
                ctx.stroke()
            }
        }

//        Text {
//            id: textElement
//            anchors.fill: parent
//            anchors.margins: 10
//            font.family: "Verdana"
//            font.pixelSize: 14
//            text: resultText
//        }

    }

    Connections {
        target: mainWindow
        onResultReady: {
            words = wordList
            wordsCount = entriesList
            console.log("++++++++++++++")
        }
    }

    Connections {
        target: mainWindow
        onClearHistogram: {
            resultText = ""
        }
    }

    Connections {
        target: mainWindow
        onOutTextReady: {
            resultText = outText
        }
    }
}
