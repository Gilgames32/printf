import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9

Item {
    //flickable.returnToBounds();

    property alias previewSource: image.source
    property alias previewStatus: image.status
    property var mousePos: Qt.point(0, 0)
    property var zoom: 1

    onZoomChanged: {
        flickable.resizeContent((image.width * zoom), (image.height * zoom), mousePos);
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10
        anchors.rightMargin: 0
        anchors.leftMargin: 0

        Rectangle {
            id: flickArea

            color: palette.mid
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 5
            clip: true

            Text {
                text: "Loading preview..."
                anchors.centerIn: parent
                color: palette.midlight
                visible: image.status == Image.Loading
            }

            Text {
                text: "Click generate to create a preview"
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

        }

        OutputBar {
            id: outputBar

            Layout.fillWidth: true
            width: parent.width
        }

    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onWheel: (wheel) => {
            mousePos = Qt.point(wheel.x, wheel.y);
            zoom *= wheel.angleDelta.y > 0 ? 1.25 : 1 / 1.25;
            flickable.returnToBounds();
        }
    }

}
