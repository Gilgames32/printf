import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Dialogs 6.8

FileDialog {
    id: fileDialog
    property var onAcceptDelegate: (files) => console.log("Selected files:", files);
    property var onRejectDelegate: () => console.log("File selection canceled");

    title: "Select an Image"
    nameFilters: ["Image files (*.png *.jpg *.jpeg)"]
    fileMode: FileDialog.OpenFiles

    onAccepted: {
        onAcceptDelegate(fileDialog.selectedFiles);
    }
    onRejected: {
        onRejectDelegate();
    }
}
