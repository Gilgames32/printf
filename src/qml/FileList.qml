import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8
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
                imagePicker.open();
            }

            ImagePicker {
                id: imagePicker
                onAcceptDelegate: (files) => {
                    sourceEntryView.addFiles(files);
                }
            }

        }

        ListView {
            id: fileListView

            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 10

            model: SourceEntryView {
                id: sourceEntryView
            }

            delegate: File {
                dataModel: sourceEntryView
                imagePresetModel: PresetView {
                    path: "presets/image"
                }
                maskPresetModel: PresetView {
                    path: "presets/mask"
                }
                width: filePanel.width
            }

        }

    }

}
