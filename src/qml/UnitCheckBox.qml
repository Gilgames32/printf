import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

RowLayout {
    property alias label: label
    property alias num: checkbox.checked
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

    CheckBox {
        id: checkbox

        checked: false
        onCheckedChanged: {
            generator.dirty = true
            onValueChangedDelegate(checkbox.checked);
        }
    }

    Item {
        Layout.preferredWidth: 89 // magic
    }

}
