import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

Rectangle {
    id: fileItem

    property var dataModel: null
    property var imagePresetModel: null
    property var absoluteModel: model

    color: palette.base
    radius: 5
    implicitHeight: paddingCol.implicitHeight + 20 // FIXME: hack

    SystemPalette {
        id: palette

        colorGroup: SystemPalette.Active
    }

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

                    source: "file://" + model.path
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
                            text: model.name
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
                        text: model.path
                        font.pixelSize: 12
                        clip: true
                    }

                    RowLayout {
                        spacing: 10
                        Layout.fillWidth: true

                        Text {
                            color: palette.text
                            text: model.resolution.width + "x" + model.resolution.height
                            font.pixelSize: 12
                            Layout.fillWidth: true
                            clip: true
                        }

                        SpinBox {
                            id: spinbox

                            Layout.preferredWidth: 60
                            value: model.amount
                            from: 1
                            to: 1000
                            stepSize: 1
                            editable: true
                            onValueChanged: () => {
                                if (model.amount != spinbox.value)
                                    model.amount = spinbox.value;

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
                        return ;
                    dataModel.setPreset(absoluteModel.index, imagePresetModel.getPath(index));
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

                        imageWidth: model.size.width
                        imageHeight: model.size.height
                        onWidthChangedDelegate: (value) => {
                            if (model.size.width == value)
                                return ;

                            model.size.width = value;
                            if (sizeInput.locked)
                                model.size.height = value / model.aspect;

                        }
                        onHeightChangedDelegate: (value) => {
                            if (model.size.height == value)
                                return ;

                            model.size.height = value;
                            console.log(sizeInput.locked);
                            if (sizeInput.locked)
                                model.size.width = value * model.aspect;

                        }
                        width: parent.width
                    }

                    CheckBox {
                        id: guidesCheckBox

                        checked: true
                        text: "Guides"
                    }

                    MaskInput {
                        id: maskInput

                        width: parent.width
                    }

                }

            }

        }

    }

}
