import QtQuick 6.9
import QtQuick.Controls 6.9

Item {
    property alias previewSource: image.source
    property alias previewStatus: image.status

    Rectangle {
        id: flickArea

        color: palette.base
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

            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            smooth: false
            mipmap: false
            asynchronous: true
            cache: false
            onStatusChanged: {
                if (status != Image.Ready)
                    return ;

                scale = 1;
                // fit image
                if (width > height)
                    scale = flickArea.width / width;
                else
                    scale = flickArea.height / height;
            }
        }

        Text {
            text: "Loading preview..."
            anchors.centerIn: parent
            color: palette.mid
            visible: image.status == Image.Loading
        }

        Text {
            text: "//TODO: greeting"
            anchors.centerIn: parent
            color: palette.mid
            visible: image.status == Image.Null
        }

        Text {
            text: "Error generating image"
            anchors.centerIn: parent
            color: palette.mid
            visible: image.status == Image.Error
        }

        MouseArea {
            anchors.fill: parent
            onWheel: (wheel) => {
                return mouseArea.wheel(wheel);
            } // emit the signal to the main mouse area
            onPositionChanged: (mouse) => {
                return mouseArea.positionChanged(mouse);
            } // emit the signal to the main mouse area
        }

    }

}
