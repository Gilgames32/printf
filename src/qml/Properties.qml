import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    Button {
        id: button

        text: "dont click me"
        onClicked: {
            console.log("Button clicked");
        }
    }

}
