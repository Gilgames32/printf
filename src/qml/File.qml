import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: fileItem
    height: 50

    Row {
        spacing: 10      

        Text {
            id: textItem
            text: model.filePath
            font.pixelSize: 16
        }

        Button {
            text: "Open"
            onClicked: {
                fileHandler.openFile(model.filePath);
            }
        }

    }

}
