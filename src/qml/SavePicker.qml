import QtQuick 6.9
import QtQuick.Controls 6.9
import Qt.labs.platform 1.1

FileDialog {
    id: fileDialog
    property var onAcceptDelegate: (file) => console.log("Save location:", file);
    property var onRejectDelegate: () => console.log("Saving canceled");

    title: "Select Save Location"

    defaultSuffix: "png"
    nameFilters: ["PNG (*.png)"]
    fileMode: FileDialog.SaveFile
    
    onAccepted: {
        onAcceptDelegate(fileDialog.file);
    }
    onRejected: {
        onRejectDelegate();
    }
}
