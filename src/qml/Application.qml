import QtQuick.Controls.FluentWinUI3 6.9
import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

ApplicationWindow {
    readonly property var dmargin: 10
    // TODO: same thing with radius
    readonly property var dspacing: 10
    readonly property var dinputsize: 120

    visible: true
    width: 1280
    height: 720
    title: "printf"

    palette {
        window: "#1d2021"
        button: "#282828"        
        text: "#ebdbb2"
        buttonText: "#ebdbb2"

        light: "#ebdbb2"
        midlight: "#a89984"
        mid: "#282828"
        dark: "#1d2021"

        accent: "#8ec07c"

        disabled {
            button: "#1d2021"
            text: "#665c54"
            buttonText: "#665c54"
        }
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
