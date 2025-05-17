import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

ApplicationWindow {
    readonly property var dmargin: 10

    visible: true
    width: 1280
    height: 720
    title: "printf"

    SystemPalette {
        id: palette

        colorGroup: SystemPalette.Active
    }

    ErrorSignal {
        id: errorSignal
    }

    GeneratorView {
        id: generator

        readonly property var providedImagePath: "image://previewprovider/"
        property var imageSource: ""
        property var dirty: true
    }

    SourceEntryView {
        id: sourceEntryView
    }

    DocumentPropertiesView {
        id: docProperties
    }

    RowLayout {
        anchors.fill: parent

        FileList {
            sourceEntryView: sourceEntryView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 1
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 2

            Preview {
                id: preview

                Layout.fillWidth: true
                Layout.fillHeight: true
                previewSource: generator.imageSource
            }

            OutputBar {
                id: outputBar

                Layout.fillWidth: true
                width: parent.width
            }

        }

        Properties {
            docProperties: docProperties
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredWidth: 1
        }

    }

}
