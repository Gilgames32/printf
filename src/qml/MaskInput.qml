import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

Column {
    property var presetModel: null
    
    CheckBox {
        id: maskCheckBox

        checked: false
        text: "Mask"
    }

    GroupBox {
        visible: maskCheckBox.checked
        width: parent.width

        RowLayout {
            id: maskLayout

            width: parent.width
            spacing: 10

            Image {
                id: maskImage

                source: "file://" + model.entry.filePath
                fillMode: Image.PreserveAspectFit
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                Layout.preferredHeight: 50
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.preferredWidth: 3

                ComboBox {
                    width: parent.width
                    textRole: "name"
                    
                    onActivated: (index) => {
                        let path = imagePresetModel.getPath(index);
                        if (path == "")
                            return;

                        // absoluteModel.entry.setPreset(imagePresetModel.getPath(index));
                    }

                    model: presetModel
                }

                Text {
                    color: palette.text
                    text: model.entry.name
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    clip: true
                }

            }

        }

    }

}
