import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Example QML Window"

    RowLayout {
        anchors.fill: parent

        FileList {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 1
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
