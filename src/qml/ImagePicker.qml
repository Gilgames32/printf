import QtQuick 6.8
import QtQuick.Controls 6.8
import QtQuick.Dialogs 6.8

FileDialog {
    id: fileDialog

    title: "Select an Image"
    nameFilters: ["Image files (*.png *.jpg *.jpeg)"]
    fileMode: FileDialog.OpenFiles

    onAccepted: {
        console.log("Selected file:", fileDialog.selectedFiles);
    }
    onRejected: {
        console.log("File selection canceled");
    }
}
