import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Layouts 6.8

Rectangle {
    id: fileItem

    property var dataModel: null

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

                Image {
                    id: image
                    source: "file://" + model.path
                    
                    fillMode: Image.PreserveAspectFit
                    
                    Layout.fillWidth: true                    
                    Layout.preferredWidth: 1
                    Layout.preferredHeight: 100
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 4
                    spacing: 10

                    RowLayout {
                        spacing: 10
                        width: parent.width

                        Text {
                            text: model.path
                            font.pixelSize: 16
                            Layout.fillWidth: true
                            clip: true
                        }

                        Button {
                            id: deleteButton

                            Layout.preferredWidth: 30
                            Layout.preferredHeight: 30
                            text: "X"
                            onClicked: {
                                dataModel.remove(model.index)
                            }
                        }

                    }

                    RowLayout {
                        spacing: 10
                        width: parent.width

                        Text {
                            text: model.name
                            font.pixelSize: 16
                            Layout.fillWidth: true
                            clip: true
                        }

                        SpinBox {
                            id: spinbox

                            Layout.preferredWidth: 60
                            value: model.amount
                            from: 1
                            to: 1000
                            stepSize: 1
                            editable: true

                            onValueChanged: () => {
                                if (model.amount != spinbox.value){
                                    model.amount = spinbox.value;
                                }
                            }
                        }

                    }

                    Text {
                        text: model.imageSize.width + "x" + model.imageSize.height
                        font.pixelSize: 16
                    }

                }

            }

        }

    }

}
