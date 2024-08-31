import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Item {
    id: root
    property string resultText: ""

    Rectangle {
        id: rect
//        width: 100
//        height: 100
        anchors.fill: parent
        border.color: "black"
        radius: 10
        opacity: 0.7

        Canvas
        {
            anchors.fill: parent
            width: parent.width
            height: parent.height
            onPaint:
            {
                function drawFantasy()
                {
                    ctx .beginPath ()
                    ctx.translate(parent.width / 2, parent.height / 2)
                    var fAngle = 91 * 3.14156 / 180
                    for (var i = 0; i < 300; ++i)
                    {
                        var n = i * 2
                        ctx.moveTo(0, 0)
                        ctx.lineTo(n, 0)
                        ctx.translate(n, 0)
                        ctx.rotate(fAngle)
                    }
                    ctx. closePath ()
                }
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, parent.width, parent.height)
                ctx.save();
                ctx.strokeStyle
                ctx.lineWidth = 1

                drawFantasy()

                ctx. stroke()
                ctx.restore()
            }
        }

//        Canvas {
//            id: canvas
//            anchors.fill: parent
//            width: rect.width
//            height: rect.height
//            onPaint: {
//                var ctx = getContext("2d")
//                ctx.lineWidth = 20
//                ctx.strokeStyle = "#287233"
//                drawLines(ctx)
//            }

//            function drawLines(ctx)
//            {
//                var step = 40;
//                ctx.beginPath()
//                for(var i = 0; i < 15; i++)
//                {
//                    ctx.moveTo(step + i, parent.height)
//                    ctx.lineTo(step + i, parent.height / 2)
//                    ctx.font = "14pt Verdana";
//                    ctx.fillText("Hello", step + i - 20, (parent.height / 2) - 5)
//                    step += 40
//                }
//                ctx.stroke()
//            }
//        }

////        Text {
////            id: textElement
////            anchors.fill: parent
////            anchors.margins: 10
////            font.family: "Verdana"
////            font.pixelSize: 24
////            text: resultText
////        }

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
