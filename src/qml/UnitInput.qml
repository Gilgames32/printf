import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

RowLayout {
    property alias unit: unit
    property alias label: label
    readonly property var from: 0
    readonly property var to: 100000
    property var num: from
    property var onValueChangedDelegate: (value) => {
        return console.log("Value changed to: " + value);
    }

    function getFormattedNum() {
        // TODO: :skull:
        return textInput.focus ? num : num.toFixed(num % 1 == 0 ? 0 : (num * 10) % 1 == 0 ? 1 : 2);
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
        horizontalAlignment: Qt.AlignRight
        inputMethodHints: Qt.ImhPreferNumbers
        onEditingFinished: {
            const parsedNum = parseFloat(text.replace(',', '.'));
            if (isNaN(parsedNum)) {
                num = num; // notify num
                return ;
            }
            const clampedNum = Math.min(Math.max(parsedNum, from), to);
            if (num != clampedNum) {
                num = clampedNum;
                onValueChangedDelegate(num);
            } else if (clampedNum != parsedNum) {
                num = clampedNum; // notify num
            }
        }
        onFocusChanged: {
            textInput.text = getFormattedNum();
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
