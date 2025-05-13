import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

Item {
    property var sourceEntryView: null

    ColumnLayout {
        id: filePanel

        anchors.fill: parent
        spacing: 10
        anchors.margins: 10
        anchors.rightMargin: 0

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
            model: sourceEntryView

            Item {
                id: marginFix

                anchors.fill: parent
                anchors.rightMargin: dmargin

                MouseArea {
                    id: mouseArea

                    anchors.fill: parent
                    onDoubleClicked: {
                        console.log("Double clicked");
                        imagePicker.open();
                    }
                    visible: sourceEntryView.count == 0 // FIXME: cant put it behind the list items like before, smth broke this idk
                }

                DropArea {
                    id: dropArea

                    anchors.fill: parent
                    onDropped: (drop) => {
                        if (drop.hasUrls)
                            sourceEntryView.addFiles(drop.urls);

                    }

                    Text {
                        id: noFilesText

                        text: "Double click to open or drag files here"
                        wrapMode: Text.WordWrap
                        anchors.fill: parent
                        anchors.margins: dmargin
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        color: palette.mid
                        visible: sourceEntryView.count == 0
                    }

                }

                Rectangle {
                    color: "transparent"
                    anchors.fill: parent
                    border.color: palette.mid
                    border.width: 1
                    radius: 5
                    visible: sourceEntryView.count == 0
                }

            }

            PresetView {
                id: imagePresetView

                path: "presets/image"
            }

            PresetView {
                id: maskPresetView

                path: "presets/mask"
            }

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
            }

            delegate: File {
                dataModel: sourceEntryView
                width: filePanel.width - dmargin
                imagePresetModel: imagePresetView
                maskPresetModel: maskPresetView
            }

        }

    }

}
