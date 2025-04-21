import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

RowLayout {
    property alias unit: unit
    property alias label: label
    property alias num: spinbox.value
    property var onValueChangedDelegate: (value) => {
        return console.log("Value changed to: " + value);
    }

    spacing: 10

    Text {
        id: label

        color: palette.text
        font.pixelSize: 12
        clip: true
    }

    SpinBox {
        id: spinbox

        Layout.preferredWidth: 80
        value: 1
        from: 1
        to: 1000
        stepSize: 1
        editable: true
        onValueChanged: onValueChangedDelegate(spinbox.value)
    }

    Text {
        id: unit

        color: palette.text
        text: unit
        font.pixelSize: 12
        Layout.preferredWidth: 32
        clip: true
    }

}
