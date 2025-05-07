import QtQuick.Controls.FluentWinUI3 6.9
import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

ApplicationWindow {
    readonly property var dmargin: 10
    readonly property var dspacing: 10
    readonly property var dinputsize: 120

    visible: true
    width: 640
    height: 480
    title: "printf"

    SystemPalette {
        id: palette

        colorGroup: SystemPalette.Active
    }

    GeneratorView {
        id: generator

        readonly property var providedImagePath: "image://previewprovider/"
        property var imageSource: ""
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

        Preview {
            id: preview

            previewSource: generator.imageSource
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 2
        }

        Properties {
            docProperties: docProperties
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredWidth: 1
        }

    }

}
