import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import printf 1.0

Item {
    ColumnLayout {
        id: filePanel

        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        Button {
            id: openButton

            text: "Open"
            onClicked: {
                fileHandler.openFile(model.display);
            }
        }

        ListView {
            id: fileListView

            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 10

            model: DataEntryModel {
            }

            delegate: File {
                width: filePanel.width
            }

        }

    }

}
