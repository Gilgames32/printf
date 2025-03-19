import QtQuick
import QtQuick.Controls

ListView {
    id: fileListView
    anchors.fill: parent
    model: fileModel
    clip: true

    delegate: Item {

        width: fileListView.width
        height: 40

        Row {
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter

            Text {
                text: model.filePath
                font.pixelSize: 16
            }

            Button {
                text: "Open"
                onClicked: {
                    fileHandler.openFile(model.filePath)
                }
            }
        }
    }
}