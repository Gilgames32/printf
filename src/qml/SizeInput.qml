import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

RowLayout {
    property var imageWidth: 1
    property var imageHeight: 1
    property var onWidthChangedDelegate: (value) => console.log("Width changed to: " + value)
    property var onHeightChangedDelegate: (value) => console.log("Height changed to: " + value)
    property alias locked: checkBox.checked

    CheckBox {
        
        Layout.fillHeight: true
        
        id: checkBox

        checked: true // TODO: on check force aspect ratio
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
            value: imageWidth
            onValueChangedDelegate: (value) => onWidthChangedDelegate(value)

            Layout.alignment: Qt.AlignRight
            label.text: "Width"
            unit.text: "mm"
            Layout.fillWidth: true
        }

        UnitInput {
            id: heightSpinbox
            value: imageHeight
            onValueChangedDelegate: (value) => onHeightChangedDelegate(value)

            Layout.alignment: Qt.AlignRight
            label.text: "Height"
            unit.text: "mm"
            Layout.fillWidth: true
        }

    }

}
