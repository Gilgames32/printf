import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

RowLayout {
    property alias sizeWidth: widthInput.num
    property alias sizeHeight: heightInput.num
    property alias onWidthChangedDelegate: widthInput.onValueChangedDelegate
    property alias onHeightChangedDelegate: heightInput.onValueChangedDelegate
    property alias locked: checkBox.checked

    CheckBox {
        id: checkBox

        Layout.fillHeight: true
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
            id: widthInput

            from: 1
            label.text: "Width"
            unit.text: "mm"
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
        }

        UnitInput {
            id: heightInput

            from: 1
            label.text: "Height"
            unit.text: "mm"
            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
        }

    }

}
