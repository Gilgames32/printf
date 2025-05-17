import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Dialogs 6.9

FileDialog {
    id: fileDialog
    property var onAcceptDelegate: (file) => console.log("Save location:", file);
    property var onRejectDelegate: () => console.log("Saving canceled");

    title: "Select Save Location"

    defaultSuffix: "png"
    nameFilters: ["PNG (*.png)"]
    fileMode: FileDialog.SaveFile
    
    onAccepted: {
        onAcceptDelegate(fileDialog.selectedFile);
    }
    onRejected: {
        onRejectDelegate();
    }
}
