import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

Column {
    property var presetModel: null
    property var imageSource: null

    CheckBox {
        id: maskCheckBox

        checked: imageSource.mask.enabled
        onCheckedChanged: {
            generator.dirty = true
            imageSource.mask.enabled = maskCheckBox.checked;
        }
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

                source: imageSource.mask.absoluteFilePath ? "file://" + imageSource.mask.absoluteFilePath : ""
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
                        let path = presetModel.getPath(index);
                        if (path == "")
                            return;
                        
                        generator.dirty = true
                        imageSource.mask.setPreset(presetModel.getPath(index));
                    }
                    model: presetModel
                }

                Text {
                    color: palette.text
                    text: imageSource.mask.filePath
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    clip: true
                }

            }

        }

    }

}
