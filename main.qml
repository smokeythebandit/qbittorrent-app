import QtQuick 2.11
import io.backend 1.0;
import QtQuick.Window 2.11
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0

import "Pages/LoginPage"

Window {
    id: window
    visible: true
    width: 540
    height: 960
    title: qsTr("qBittorrent Mobile Client")

    Component.onCompleted: {
        connector.attemptLogin();
    }

    WebConnector {
        id: connector
        onLoggedInChanged: {
            if(!connector.loggedIn) loginPopup.open();
        }
    }

    Popup {
        id: loginPopup
        width: parent.width
        height: parent.height
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        modal: true
        focus: true
        enter: Transition {
            NumberAnimation { property: "opacity"; easing.type: Easing.InOutQuart; from: 0; to: 0.9; duration: 300 }
            NumberAnimation { property: "y"; easing.type: Easing.InOutQuart; from: window.height; to: 0; duration: 300 }
        }
        exit: Transition {
            NumberAnimation { property: "y"; easing.type: Easing.InOutQuart; from: 0; to: window.height; duration: 250 }
            NumberAnimation { property: "opacity"; easing.type: Easing.InOutQuart; from: 0.9; to: 0; duration: 250 }

        }
        LoginPage
        {
            id: loginPage
            anchors.fill: parent

        }
    }
}
