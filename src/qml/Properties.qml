import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

Item {
    property var docProperties: null

    implicitHeight: paddingCol.implicitHeight + 4 * dmargin

    Rectangle {
        anchors.margins: dmargin
        anchors.fill: parent
        color: palette.base
        radius: 5
        clip: true

        Column {
            id: paddingCol

            spacing: 10
            anchors.fill: parent
            anchors.margins: 10

            ComboBox {
                width: parent.width
                textRole: "name"
                onActivated: (index) => {
                    let path = presetModel.getPath(index);
                    if (path == "")
                        return ;

                    docProperties.setPreset(presetModel.getPath(index));
                }

                model: PresetView {
                    id: presetModel

                    path: "presets/document"
                }

            }

            GroupBox {
                width: parent.width

                ColumnLayout {
                    spacing: 10

                    UnitInput {
                        num: docProperties.resolution
                        label.text: "Resolution"
                        unit.text: "ppi"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitInput {
                        num: docProperties.rollWidth
                        label.text: "Paper Width"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitSpinBox {
                        num: docProperties.margin
                        label.text: "Margin"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    CheckBox {
                        // TODO: make pretty
                        id: guidesCheckBox

                        checked: true
                        text: "Guides"
                        font.pixelSize: 12
                    }

                    UnitSpinBox {
                        id: gutterSpinBox

                        num: docProperties.gutter
                        label.text: "Gutter"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                }

            }

            CheckBox {
                id: checkBox

                text: "Corrected Quantity"
                checked: docProperties.correctQuantity
            }

            Button {
                text: "Generate"
                onClicked: {
                    generator.generate(docProperties.getDocumentProperties(), sourceEntryView.getImageSources());
                    // we somehow have to signal to it...
                    var imageSource = generator.imageSource;
                    generator.imageSource = "";
                    generator.imageSource = imageSource;
                }
            }

        }

    }

}
