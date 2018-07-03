import QtQuick 2.11
import io.backend 1.0;
import QtQuick.Window 2.11
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0

import "Pages/Dashboard"
import "Controls/Popups/LoginPopup"

Window {
    id: window
    visible: true
    minimumWidth: 540
    minimumHeight: 960
    title: qsTr("qBittorrent Mobile Client")

    Component.onCompleted: {
        loginPopup.open()
    }

    Connections {
        target: WebConnector
        onLoggedInChanged: {
            if(WebConnector.loggedIn) loginPopup.close()
            else loginPopup.open()
        }
    }

    StackView {
        anchors.fill: parent

        Dashboard {
            id: dashboard
            anchors.fill: parent
        }

    }

    LoginPopup {
        id: loginPopup
    }
}
