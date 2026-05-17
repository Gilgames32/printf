import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

Rectangle {
    id: outputBar

    Component.onCompleted: {
        errorSignal.onError.connect((error) => {
            errorText.text = error;
            errorText.color = "#fb4934";
            errorText.font.bold = true;
        });
        errorSignal.onInfo.connect((info) => {
            errorText.text = info;
            errorText.color = palette.text;
            errorText.font.bold = false;
        });
    }
    height: 40
    color: palette.mid
    radius: 5
    clip: true

    Row {
        
        anchors.centerIn: parent
        width: parent.width - 2 * dmargin
        
        anchors.margins: dmargin

        Text {
            id: errorText

            verticalAlignment: Text.AlignVCenter
        }

    }

}
