import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

RowLayout {
    property alias unit: unit
    property alias label: label
    property var value: null
    readonly property var from: 0
    readonly property var to: 100_000

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

    TextField {
        id: textInput

        Layout.preferredWidth: 80
        text: value
        inputMethodHints: Qt.ImhPreferNumbers
        onEditingFinished: {
            const parsedValue = parseFloat(text.replace(',', '.'));

            if (isNaN(parsedValue)) {
                text = value;
                return;
            }

            const clampedValue = Math.min(Math.max(parsedValue, from),to);
            if (clampedValue != parsedValue) text = clampedValue;
            if (value == clampedValue) return;

            value = clampedValue;
            onValueChangedDelegate(value);
        }

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
