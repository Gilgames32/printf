import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

Column {
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

                source: "file://" + model.path
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
                    textRole: "text" // ?
                    onCurrentIndexChanged: {
                    }

                    model: ListModel {
                        ListElement {
                            text: "todo"
                        }

                    }

                }

                Text {
                    color: palette.text
                    text: model.name
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    clip: true
                }

            }

        }

    }

}
