import QtQuick 2.0

Item {
    id: root
    property var words: []
    property var entries: []

    property string title:  ""
    property string yLabel: 'yLabel'
    property string xLabel: 'xLabel'
    property variant points: []

    property double factor: Math.min(width, height)

    property double yInterval:  1
    property double yMaximum:  10
    property double yMinimum:   0
    function toYPixels(y){
        return plot.height / (yMaximum - yMinimum) * (y - yMinimum)
    }

    property int xMaximum:   0

    onPointsChanged: {
        if(!points)
            return
        var xMaximum = 0, yMinimum = 0, yMaximum = 0
        for(var i = 0; i < points.length; i++)
        {
            if(points[i].y > yMaximum)
                yMaximum = points[i].y
            if(points[i].y < yMinimum)
                yMinimum = points[i].y
            if(points[i].x.length > xMaximum)
                xMaximum = points[i].x.length
        }

        var yLog10 = Math.log(yMaximum - yMinimum) / Math.LN10
        root.yInterval = Math.pow(10, Math.floor(yLog10)) / (yLog10 % 1 < 0.7? 4: 2)
        root.yMaximum  = Math.ceil( yMaximum / yInterval) * yInterval
        root.yMinimum  = Math.floor(yMinimum / yInterval) * yInterval

        root.xMaximum  = xMaximum
    }

    Rectangle { //rect
        id: rect
        anchors.fill: parent
        border.color: "black"
        radius: 10
        opacity: 0.7

        Text { // title
            text: title
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 0.03 * factor
        }

        Text { // y label
            text: yLabel
            font.pixelSize: 0.03 * factor
            y: 0.5 * (2 * plot.y + plot.height + width)
            rotation: -90
            transformOrigin: Item.TopLeft
            anchors.margins: 10
        }

        Text { // x label
            text: xLabel
            font.pixelSize: 0.03 * factor
            anchors {
                bottom: parent.bottom
                horizontalCenter: plot.horizontalCenter
                margins: 10
            }
        }

        Item {
            id: plot
            width: rect.width
            height: rect.height
            anchors {
                fill: parent
                topMargin: 0.05 * factor
                bottomMargin: (0.015 * xMaximum + 0.05) * factor
                leftMargin: 0.15 * factor
                rightMargin: 0.05 * factor
            }

            Repeater { // сетка
                model: Math.floor((yMaximum - yMinimum) / yInterval) + 1

                delegate: Rectangle {
                    property double value: index * yInterval + yMinimum
                    y: -toYPixels(value) + plot.height
                    width: plot.width;  height: 1
                    color: 'black'

                    Text {
                        text: parent.value
                        anchors {
                            right: parent.left
                            verticalCenter: parent.verticalCenter
                            margins: 0.01 * factor
                        }
                        font.pixelSize: 0.03 * factor
                    }
                }
            }

            Repeater {
                model: points

                delegate: Item {
                    width: plot.width / points.length;  height: plot.height
                    x: width * index

                    Rectangle { // столбцы гистограммы
                        anchors{
                            horizontalCenter: parent.horizontalCenter
                            bottom: modelData.y > 0? parent.bottom: undefined;
                            bottomMargin: toYPixels(0)
                            top: modelData.y < 0? parent.top: undefined;
                            topMargin: plot.height - toYPixels(0)
                        }
                        width: 0.7 * parent.width
                        height: toYPixels(Math.abs(modelData.y) + yMinimum)
                        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 255)
                    }

                    Text { // подпись по оси X
                        text: modelData.x
                        x: (parent.width - height) / 2
                        y: parent.height + width + 0.5 * height
                        rotation: -90
                        transformOrigin: Item.TopLeft
                        font.pixelSize: 0.03 * factor
                    }
                }
            }// data
        }// plot
    }//rect

    Connections {
        target: mainWindow
        onResultReady: {
            //points = []
            words = wordList
            entries = entriesList

            var tempPoints =[]

            for(var i = 0; i < words.length; i++)
            {
                var data = {x: words[i], y: entries[i]}
                tempPoints[i] = data
            }

            points = tempPoints
        }
    }
}
