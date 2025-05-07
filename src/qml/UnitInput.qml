import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

RowLayout {
    property alias unit: unit
    property alias label: label
    property var from: 0
    property var to: 100000
    property var num: from
    property var inum: num // internal number so that outisde binding is not affected
    property var onValueChangedDelegate: (value) => {
        return console.log("Value changed to: " + value);
    }

    function getFormattedNum() {
        // TODO: :skull:
        return textInput.focus ? inum : inum.toFixed(inum % 1 == 0 ? 0 : (inum * 10) % 1 == 0 ? 1 : 2);
    }

    spacing: 10
    onNumChanged: {
        if (inum == num)
            return ;
        inum = num;
    }

    Text {
        id: label

        color: palette.text
        font.pixelSize: 12
        clip: true
    }

    TextField {
        id: textInput

        Layout.preferredWidth: dinputsize
        text: getFormattedNum()
        horizontalAlignment: Qt.AlignRight
        inputMethodHints: Qt.ImhPreferNumbers
        onEditingFinished: {
            const parsedNum = parseFloat(text.replace(',', '.'));
            if (isNaN(parsedNum)) {
                inum = inum; // notify inum
                return ;
            }
            const clampedNum = Math.min(Math.max(parsedNum, from), to);
            if (inum != clampedNum) {
                inum = clampedNum;
                onValueChangedDelegate(inum);
            } else if (clampedNum != parsedNum) {
                inum = clampedNum;
                onValueChangedDelegate(inum);
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

}
