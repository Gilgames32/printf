import QtQuick
import QtQuick.Controls

ListView {
    id: fileListView
    model: fileModel
    clip: true

    delegate: File {
    }
    spacing: 10
}