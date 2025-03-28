import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

RowLayout {
    CheckBox {
        
        Layout.fillHeight: true
        
        id: checkBox

        checked: true
        clip: true

        Rectangle {
            color: "transparent"
            border.color: palette.midlight
            border.width: 2

            width: parent.width
            height: parent.height * 0.6
            
            x: parent.width / 2
            
            anchors.verticalCenter: parent.verticalCenter

            radius: 5
        }
    }

    ColumnLayout {
        spacing: 10

        UnitInput {
            id: widthSpinbox

            Layout.alignment: Qt.AlignRight
            label.text: "Width"
            unit.text: "mm"
            Layout.fillWidth: true
        }

        UnitInput {
            id: heightSpinbox

            Layout.alignment: Qt.AlignRight
            label.text: "Height"
            unit.text: "mm"
            Layout.fillWidth: true
        }

    }

}
