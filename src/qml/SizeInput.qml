import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

RowLayout {
    property var imageSize: null
    property var onWidthChangedDelegate: (value) => {
        return console.log("Width changed to: " + value);
    }
    property var onHeightChangedDelegate: (value) => {
        return console.log("Height changed to: " + value);
    }
    property alias locked: checkBox.checked

    CheckBox {
        id: checkBox

        Layout.fillHeight: true
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

            value: imageSize.width
            onValueChangedDelegate: (value) => {
                return onWidthChangedDelegate(value);
            }
            label.text: "Width"
            unit.text: "mm"
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
        }

        UnitInput {
            id: heightSpinbox

            value: imageSize.height
            onValueChangedDelegate: (value) => {
                return onHeightChangedDelegate(value);
            }
            label.text: "Height"
            unit.text: "mm"
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
        }

    }

}
