import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import printf 1.0

Item {
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
                textRole: "name"
                // TODO
                width: parent.width
            }

            GroupBox {
                width: parent.width

                ColumnLayout {
                    spacing: 10

                    UnitInput {
                        value: 300
                        label.text: "Resolution"
                        unit.text: "ppi"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitInput {
                        value: 610
                        label.text: "Paper Width"
                        unit.text: "mm"
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        label.Layout.fillWidth: true
                    }

                    UnitSpinBox {
                        value: 5
                        label.text: "Margin"
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
                checked: true
            }

            Button {
                text: "Generate"
            }

        }

    }

}
