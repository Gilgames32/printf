import QtQuick 6.8
import QtQuick.Controls 6.8

Item {
    Rectangle {
        width: 10
        height: 10
        color: "#323232"
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onWheel: (wheel) => {
            let zoomFactor = 1.1;
            if (wheel.angleDelta.y > 0)
                image.scale *= zoomFactor;
            else
                image.scale /= zoomFactor;
            flickable.contentWidth = image.width * image.scale;
            flickable.contentHeight = image.height * image.scale;
        }
    }

    Flickable {
        id: flickable

        anchors.fill: parent
        contentWidth: image.width * image.scale
        contentHeight: image.height * image.scale
        clip: true

        Image {
            id: image

            source: "3.png"
            anchors.centerIn: parent
            transformOrigin: Item.Center
            scale: 1
        }

        MouseArea {
            anchors.fill: parent
            onWheel: (wheel) => {
                return mouseArea.wheel(wheel);
            } // emit the signal to the main mouse area
        }

    }

}
