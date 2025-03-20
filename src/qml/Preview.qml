import QtQuick 6.8
import QtQuick.Controls 6.8

Item {
    Rectangle {
        id: flickArea
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
        }
    }

    Flickable {
        id: flickable

        anchors.fill: parent
        contentWidth: Math.max(image.width * image.scale, flickArea.width)
        contentHeight: Math.max(image.height * image.scale, flickArea.height)
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
