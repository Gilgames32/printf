import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

Rectangle {
    id: outputBar

    
    Component.onCompleted: {
        errorSignal.onError.connect((error) => {
            errorText.text = error;
            errorText.color = "#ff5555";
            errorText.font.bold = true;         
        });
        errorSignal.onInfo.connect((info) => {
            errorText.text = info;
            errorText.color = palette.text;
            errorText.font.bold = false;
        });
    }
    

    height: 40
    color: palette.base

    Row {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 8

        Text {
            id: errorText

            verticalAlignment: Text.AlignVCenter
        }

    }

}
