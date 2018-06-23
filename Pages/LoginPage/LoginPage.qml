import QtQuick 2.0
import io.backend 1.0;
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.3

Item {
    id: loginPage
    width: 270
    height: 480
    enabled: !connector.authenticating

    MessageDialog {
        id: messageDialog
        icon: StandardIcon.Critical
        title: "Failed to log in"
        text: "Invalid Username/Password"
    }

    WebConnector {
        id: connector
        onAuthenticatingChanged: {
            if(connector.authenticating) loginPage.state = "authenticating"
            else loginPage.state = ""
        }
        onLoggedInChanged: {
            if(!connector.loggedIn) {
                messageDialog.open()
            }
        }
    }

    TextField {
        id: txt_URL
        selectByMouse: true
        text: connector.url
        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        placeholderText: qsTr("URL")
        onEditingFinished: connector.url = txt_URL.text
    }

    TextField {
        id: txt_Username
        selectByMouse: true
        text: connector.username
        anchors.top: txt_URL.bottom
        anchors.topMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        placeholderText: qsTr("Username")
        onEditingFinished: connector.username = txt_Username.text
    }

    TextField {
        id: txt_Password
        selectByMouse: true
        text: connector.password
        anchors.top: txt_Username.bottom
        anchors.topMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        placeholderText: qsTr("Password")
        echoMode: TextInput.Password
        onEditingFinished: connector.password = txt_Password.text
    }

    Button {
        id: btn_SignIn
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        text: qsTr("Sign in")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        onClicked: connector.attemptLogin()
    }

    BusyIndicator {
        id: busyIndicator
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        visible: false
        opacity: 0
    }

    states: [
        State {
            name: "authenticating"
            PropertyChanges {
                target: txt_URL
                visible: false
            }
            PropertyChanges {
                target: txt_Username
                visible: false
            }
            PropertyChanges {
                target: txt_Password
                visible: false
            }
            PropertyChanges {
                target: btn_SignIn
                visible: false
            }
            PropertyChanges {
                target: busyIndicator
                visible: true
                opacity: 1
            }
        }
    ]
}
