import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

Rectangle {
    id: fileItem

    border.color: "black"
    border.width: 1
    radius: 5
    implicitHeight: paddingCol.implicitHeight + 20 // FIXME: hack

    Item {
        id: container

        anchors.fill: parent
        anchors.margins: 10

        Column {
            id: paddingCol

            spacing: 10
            width: container.width

            RowLayout {
                id: detailsLayout

                width: parent.width
                spacing: 10

                Rectangle {
                    color: "orange"
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 100
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 10

                    RowLayout {
                        spacing: 10
                        width: parent.width

                        Text {
                            text: "path"
                            font.pixelSize: 16
                            Layout.fillWidth: true
                        }

                        Button {
                            id: deleteButton

                            Layout.preferredWidth: 30
                            Layout.preferredHeight: 30
                            text: "X"
                        }

                    }

                    RowLayout {
                        spacing: 10
                        width: parent.width

                        Text {
                            text: model.name
                            font.pixelSize: 16
                            Layout.fillWidth: true
                        }

                        SpinBox {
                            id: spinbox

                            Layout.preferredWidth: 60
                            value: 0
                            from: 0
                            stepSize: 1
                        }

                    }

                    Text {
                        text: "extra info about the file"
                        font.pixelSize: 16
                    }

                }

            }

        }

    }

}
