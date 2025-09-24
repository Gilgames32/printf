import QtQuick 6.9
import QtQuick.Controls 6.9

Item {
    property alias previewSource: image.source
    property alias previewStatus: image.status

    property var zoom: 1.0
    onZoomChanged: {
        // TODO: mouse position as the zoom center
        var zoomPoint = Qt.point(flickable.width/2 + flickable.contentX,
                                flickable.height/2 + flickable.contentY);

        flickable.resizeContent((image.width * zoom), (image.height * zoom), zoomPoint);
        //flickable.returnToBounds();
    }

    Rectangle {
        id: flickArea

        color: palette.base
        anchors.fill: parent
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onWheel: (wheel) => {
            zoom *= wheel.angleDelta.y > 0 ? 1.25 : 1/1.25
            flickable.returnToBounds();
        }
    }

    Flickable {
        id: flickable

        anchors.fill: parent
        contentWidth: Math.max(image.width * zoom, flickArea.width)
        contentHeight: Math.max(image.height * zoom, flickArea.height)
        clip: true

        Image {
            id: image

            anchors.centerIn: parent
            scale: zoom
            fillMode: Image.PreserveAspectFit
            smooth: false
            mipmap: false
            asynchronous: true
            cache: false
            onStatusChanged: {
                if (status != Image.Ready)
                    return ;
                
                // fit image
                if (width > height)
                    zoom = flickArea.width / width;
                else
                    zoom = flickArea.height / height;
                flickable.returnToBounds();
            }
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

    Text {
        text: "Loading preview..."
        anchors.centerIn: parent
        color: palette.midlight
        visible: image.status == Image.Loading
    }

    Text {
        text: "//TODO: greeting"
        anchors.centerIn: parent
        color: palette.midlight
        visible: image.status == Image.Null
    }

    Text {
        text: "Error generating image"
        anchors.centerIn: parent
        color: palette.midlight
        visible: image.status == Image.Error
    }

}
