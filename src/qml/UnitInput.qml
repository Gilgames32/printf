import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

RowLayout {
    property alias unit: unit
    property alias label: label
    readonly property var from: 0
    readonly property var to: 100_000
    property var num: from
    property var forceBindUpdate: true

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
        
        text: getFormattedNum()
        
        inputMethodHints: Qt.ImhPreferNumbers
        onEditingFinished: {
            const parsedNum = parseFloat(text.replace(',', '.'));

            if (isNaN(parsedNum)) {
                num = num; // notify num
                return;
            }

            const clampedNum = Math.min(Math.max(parsedNum, from), to);
            num = clampedNum; // notify num
            if (num != clampedNum) {
                num = clampedNum;
                onValueChangedDelegate(num);
            }
            else if (clampedNum != parsedNum) {
            }
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

    
    function getFormattedNum () {
        // TODO: :skull:
        return textInput.focus ? num : num.toFixed(num % 1 == 0 ? 0 : (num * 10) % 1 == 0 ? 1 : 2);
    }

    onNumChanged: {
        console.log("num changed: " + num);
        textInput.text = getFormattedNum();
    }

}
