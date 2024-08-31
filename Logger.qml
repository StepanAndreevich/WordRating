import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item{
    property string messageTitle: ""
    property string messageText: ""
    MessageDialog {
        id: messageDlg
        title: messageTitle
        text: customText.text
        standardButtons: StandardButton.Ok
    }
    Text {
        id: customText
        text: messageText
        font.family: "Verdana"
        font.pointSize: 14
        visible: false
    }

    Connections {
        target: mainWindow
        onFileError: {
            messageTitle = "Ошибка"
            messageText = errorText
            messageDlg.icon = StandardIcon.Critical
            messageDlg.open()
        }
    }
}
