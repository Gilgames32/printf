import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

Rectangle {
    id: fileItem

    property var dataModel: null
    property var imagePresetModel: null
    property var maskPresetModel: null

    property var entry: model.entry

    color: palette.base
    radius: 5
    implicitHeight: paddingCol.implicitHeight + 20 // FIXME: hack

    Item {
        id: container

        clip: true
        anchors.fill: parent
        anchors.margins: 10

        Column {
            id: paddingCol

            spacing: 10
            width: container.width

            RowLayout {
                id: detailsLayout

                width: parent.width
                spacing: 10

                Image {
                    id: image

                    source: "file://" + entry.filePath
                    fillMode: Image.PreserveAspectFit
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    Layout.preferredHeight: 100
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 3

                    RowLayout {
                        spacing: 10
                        Layout.fillWidth: true

                        Text {
                            color: palette.text
                            text: entry.name
                            font.pixelSize: 16
                            font.bold: true
                            Layout.fillWidth: true
                            clip: true
                        }

                        Button {
                            id: deleteButton

                            Layout.preferredWidth: 30
                            Layout.preferredHeight: 30
                            text: "X"
                            onClicked: {
                                dataModel.remove(model.index);
                            }
                        }

                    }

                    Text {
                        Layout.fillWidth: true
                        color: palette.text
                        text: entry.filePath
                        font.pixelSize: 12
                        clip: true
                    }

                    RowLayout {
                        spacing: 10
                        Layout.fillWidth: true

                        Text {
                            color: palette.text
                            text: entry.resolution.width + "x" + entry.resolution.height
                            font.pixelSize: 12
                            Layout.fillWidth: true
                            clip: true
                        }

                        SpinBox {
                            id: spinbox

                            Layout.preferredWidth: 60
                            value: entry.amount
                            from: 1
                            to: 1000
                            stepSize: 1
                            editable: true
                            onValueChanged: () => {
                                if (entry.amount != value)
                                    entry.amount = value;

                            }
                        }

                    }

                }

            }

            ComboBox {
                id: comboBox

                width: parent.width
                textRole: "name"
                onActivated: (index) => {
                    let path = imagePresetModel.getPath(index);
                    if (path == "")
                        return;

                    entry.setPreset(path);
                    maskInput.mask.setPreset(path, "mask");
                    docProperties.setPreset(path, "document");
                }
                model: imagePresetModel
            }

            GroupBox {
                width: parent.width

                Column {
                    width: parent.width
                    spacing: 10

                    SizeInput {
                        id: sizeInput

                        sizeWidth: entry.width
                        sizeHeight: entry.height

                        onWidthChangedDelegate: (value) => {
                            if (entry.width != value)
                                entry.setSizeToWidth(value, sizeInput.locked);

                        }
                        onHeightChangedDelegate: (value) => {
                            if (entry.height != value)
                                entry.setSizeToHeight(value, sizeInput.locked);

                        }
                        width: parent.width
                    }

                    MaskInput {
                        id: maskInput

                        presetModel: maskPresetModel
                        imageSource: entry
                        width: parent.width
                    }

                }

            }

        }

    }

}
