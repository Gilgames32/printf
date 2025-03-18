import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Example QML Window"

    Button {
        text: "Click Me"
        anchors.centerIn: parent
        onClicked: console.log("Button clicked!")
    }
}