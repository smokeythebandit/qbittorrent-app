import QtQuick 2.11
import QtQuick.Controls 2.2

Popup {
    modal: true
    focus: true
    width: parent.width
    height: parent.height
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    enter: Transition {
        NumberAnimation { property: "opacity"; easing.type: Easing.InOutQuart; from: 0; to: 0.9; duration: 300 }
        NumberAnimation { property: "y"; easing.type: Easing.InOutQuart; from: window.height; to: 0; duration: 300 }
    }
    exit: Transition {
        NumberAnimation { property: "y"; easing.type: Easing.InOutQuart; from: 0; to: window.height; duration: 250 }
        NumberAnimation { property: "opacity"; easing.type: Easing.InOutQuart; from: 0.9; to: 0; duration: 250 }
    }

    Loader {
        source: "../../../Pages/LoginPage/LoginPage.qml"
        asynchronous: true
        anchors.fill: parent
        visible: status == Loader.Ready
    }
}
