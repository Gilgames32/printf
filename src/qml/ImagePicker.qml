import QtQuick 6.9
import QtQuick.Controls 6.9
import Qt.labs.platform 1.1

FileDialog {
    id: fileDialog
    property var onAcceptDelegate: (files) => console.log("Selected files:", files);
    property var onRejectDelegate: () => console.log("File selection canceled");

    title: "Select an Image"
    nameFilters: ["Image files (*.png *.jpg *.jpeg *.pdf)"]
    fileMode: FileDialog.OpenFiles

    onAccepted: {
        onAcceptDelegate(fileDialog.files);
    }
    onRejected: {
        onRejectDelegate();
    }
}
