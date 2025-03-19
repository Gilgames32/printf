import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Example QML Window"

    RowLayout {
        anchors.fill: parent
        spacing: 10

        FileList {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 1
        }

        ListModel {
            id: fileModel

            ListElement {
                filePath: "file1.txt"
            }

            ListElement {
                filePath: "file2.txt"
            }

            ListElement {
                filePath: "file3.txt"
            }

        }

        Preview {
            id: preview

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 3
        }

        Properties {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 1
        }

    }

}
