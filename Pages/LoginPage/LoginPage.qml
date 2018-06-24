import QtQuick 2.0
import io.backend 1.0;
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.3

Item {
    id: loginPage
    width: 270
    height: 480
    enabled: !WebConnector.authenticating

    MessageDialog {
        id: messageDialog
        icon: StandardIcon.Critical
        title: "Failed to log in"
        text: "Invalid Username/Password"
    }

    TextField {
        id: txt_URL
        selectByMouse: true
        text: WebConnector.url
        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        placeholderText: qsTr("URL")
        onEditingFinished: WebConnector.url = txt_URL.text
    }

    TextField {
        id: txt_Username
        selectByMouse: true
        text: WebConnector.username
        anchors.top: txt_URL.bottom
        anchors.topMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        placeholderText: qsTr("Username")
        onEditingFinished: WebConnector.username = txt_Username.text
    }

    TextField {
        id: txt_Password
        selectByMouse: true
        text: WebConnector.password
        anchors.top: txt_Username.bottom
        anchors.topMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 16
        placeholderText: qsTr("Password")
        echoMode: TextInput.Password
        onEditingFinished: WebConnector.password = txt_Password.text
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
        onClicked: WebConnector.attemptLogin()
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
