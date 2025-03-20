import QtQuick 6.8
import QtQuick.Controls 6.8

Item {
    Button {
        id: button

        text: "dont click me"
        onClicked: {
            console.log("Button clicked");
        }
    }

}
