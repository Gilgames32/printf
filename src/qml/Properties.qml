import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

Item {
    property var docProperties: null

    Rectangle {
        anchors.margins: dmargin
        anchors.fill: parent
        color: palette.mid
        radius: 5
        clip: true

        ColumnLayout {
            id: paddingCol

            anchors.fill: parent
            anchors.margins: dmargin
            spacing: 10

            ComboBox {
                Layout.fillWidth: true
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

                UnitInput {
                    num: docProperties.minHeight
                    onValueChangedDelegate: (value) => {
                        if (docProperties.minHeight != value)
                            docProperties.minHeight = value;

                    }
                    from: 1
                    label.text: "Min Height"
                    unit.text: "mm"
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    label.Layout.fillWidth: true
                }

                UnitInput {
                    num: docProperties.maxHeight
                    onValueChangedDelegate: (value) => {
                        if (docProperties.maxHeight != value)
                            docProperties.maxHeight = value;

                    }
                    from: 1
                    label.text: "Max Height"
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

                ColumnLayout {
                    Layout.fillWidth: true
                    visible: guidesCheckBox.num
                    spacing: 10

                    UnitSpinBox {
                        id: lineWidthSpinBox

                        num: docProperties.lineWidth
                        onValueChangedDelegate: (value) => {
                            if (docProperties.lineWidth != value)
                                docProperties.lineWidth = value;

                        }
                        label.text: "Line Width"
                        unit.text: "px"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitSpinBox {
                        id: bleedSpinBox

                        num: docProperties.bleed
                        onValueChangedDelegate: (value) => {
                            if (docProperties.bleed != value)
                                docProperties.bleed = value;

                        }
                        label.text: "Bleed"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

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

            Item { 
                Layout.fillHeight: true 
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
                Layout.fillWidth: true

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
                            generator.dirty = false;
                        });
                    }
                    onClicked: {
                        generateButton.enabled = false;
                        generator.asyncGenerate(docProperties.getDocumentProperties(), sourceEntryView.getImageSources(docProperties.getDocumentProperties()));
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
                    enabled: !generator.dirty && preview.previewStatus == Image.Ready
                }

                Button {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 64
                    text: "Printf"
                    onClicked: {
                        console.log("Print clicked");
                    }
                    enabled: false
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
