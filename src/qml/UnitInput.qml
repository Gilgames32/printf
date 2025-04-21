import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

RowLayout {
    property alias unit: unit
    property alias label: label
    property alias spinbox: spinbox
    property alias value: spinbox.value
    
    property var onValueChangedDelegate: (value) => console.log("Value changed to: " + value)
    

    spacing: 10

    Text {
        id: label

        color: palette.text
        font.pixelSize: 12
        clip: true
    }

    // TODO: double input
    SpinBox {
        id: spinbox

        Layout.preferredWidth: 60
        value: 1
        from: 1
        to: 1000
        stepSize: 1
        editable: true

        onValueChanged: onValueChangedDelegate(spinbox.value);
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
