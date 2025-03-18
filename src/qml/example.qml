import QtQuick
import QtQuick.Controls

// https://doc.qt.io/qt-6/qml-tutorial2.html

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

    Rectangle {
        id: page
        // width: 320; height: 480
        color: "lightgray"
        anchors.fill: parent

        Text {
            id: helloText
            text: "Hello world!"
            y: 30
            anchors.centerIn: parent
            anchors.horizontalCenter: page.horizontalCenter
            font.pointSize: 24; font.bold: true
        }
    }
}
