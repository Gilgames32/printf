import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "printf"

    
    readonly property var dmargin: 10
    

    SystemPalette {
        id: palette
        colorGroup: SystemPalette.Active
    }

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
            Layout.preferredWidth: 2
        }

        Properties {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredWidth: 1
        }

    }

}
