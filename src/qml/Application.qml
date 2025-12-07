import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

ApplicationWindow {
    readonly property var dmargin: 10
    // TODO: same thing with radius

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
        spacing: 0

        FileList {
            sourceEntryView: sourceEntryView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 1
        }

        Preview {
            id: preview

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 2
            previewSource: generator.imageSource
        }

        Properties {
            docProperties: docProperties
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 1
        }

    }

}
