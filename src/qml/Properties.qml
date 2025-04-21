// load
// document width
// margin
// bg color? nah, maybe an option for white and opaque
// resolution ppi
// try correcting quanity
// generate button

import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8
import printf 1.0

Item {
    Rectangle {
        anchors.fill: parent
        color: palette.base
        radius: 5
        anchors.margins: 10

        Item {
            id: container
            anchors.fill: parent
        }

        Column {
            spacing: 10
            
            anchors.fill: parent
            
            anchors.margins: 10
            
            width: parent.width

            ComboBox {
                textRole: "name"
                // TODO
                width: parent.width
            }

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
                    // TODO: double input
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    label.Layout.fillWidth: true
                }

                UnitInput {
                    value: 5
                    label.text: "Margin"
                    unit.text: "mm"
                    // TODO: double input
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    label.Layout.fillWidth: true
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
