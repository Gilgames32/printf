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
                        onValueChangedDelegate: (value) => {
                            if (docProperties.resolution != value)
                                docProperties.resolution = value;

                        }
                        from: 1
                        label.text: "Resolution"
                        unit.text: "ppi"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitInput {
                        num: docProperties.rollWidth
                        onValueChangedDelegate: (value) => {
                            if (docProperties.rollWidth != value)
                                docProperties.rollWidth = value;

                        }
                        from: 1
                        label.text: "Paper Width"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitSpinBox {
                        num: docProperties.margin
                        onValueChangedDelegate: (value) => {
                            if (docProperties.margin != value)
                                docProperties.margin = value;

                        }
                        label.text: "Margin"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitCheckBox {
                        id: guidesCheckBox

                        num: docProperties.guides
                        onValueChangedDelegate: (value) => {
                            if (docProperties.guides != value)
                                docProperties.guides = value;

                        }
                        label.text: "Guides"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitSpinBox {
                        id: gutterSpinBox

                        num: docProperties.gutter
                        onValueChangedDelegate: (value) => {
                            if (docProperties.gutter != value)
                                docProperties.gutter = value;

                        }
                        label.text: "Gutter"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                }

            }

            CheckBox {
                id: correctQuantityCheckBox

                text: "Corrected Quantity"
                checked: docProperties.correctQuantity
                onCheckedChanged: () => {
                    if (docProperties.correctQuantity != checked)
                        docProperties.correctQuantity = checked;

                }
            }

            RowLayout {
                width: parent.width

                Button {
                    id: generateButton

                    Layout.fillWidth: true
                    Layout.minimumWidth: 64
                    text: "Generate"
                    Component.onCompleted: {
                        generator.generationCompleted.connect(() => {
                            generator.imageSource = "";
                            generator.imageSource = generator.providedImagePath;
                            generateButton.enabled = true;
                        });
                    }
                    onClicked: {
                        generateButton.enabled = false;
                        generator.asyncGenerate(docProperties.getDocumentProperties(), sourceEntryView.getImageSources());
                    }
                }

                Button {
                    id: saveButton

                    Component.onCompleted: {
                        generator.saveCompleted.connect(() => {
                            saveButton.enabled = true;
                        });
                    }
                    Layout.fillWidth: true
                    Layout.minimumWidth: 64
                    text: "Save as"
                    onClicked: {
                        saveDialog.open();
                    }
                }

                Button {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 64
                    text: "Print"
                    onClicked: {
                        console.log("Print clicked");
                    }
                }

                SavePicker {
                    id: saveDialog

                    onAcceptDelegate: (url) => {
                        saveButton.enabled = false;
                        generator.asyncSave(url, docProperties.getDocumentProperties());
                    }
                }

            }

        }

    }

}
