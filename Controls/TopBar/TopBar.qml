import QtQuick 2.0
import "../BurgerMenuButton"
import QtQuick.Controls 2.3

Item {
    width: 400
    height: 50
    id: topBar

    signal toggledChanged(bool toggled)

    Rectangle {
        id: rectangle
        height: 50
        color: "#ffffff"
        anchors.fill: parent

        Rectangle {
            id: bottomLine
            y: 70
            height: 1
            color: "#000000"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            opacity: 0.9
        }

        BurgerMenuButton {
            id: btn_menu
            width: 24
            height: 24
            anchors.left: parent.left
            anchors.leftMargin: 13
            anchors.verticalCenter: parent.verticalCenter
            onStateChanged: {
                toggledChanged(btn_menu.state == "back")
            }
        }

        MouseArea {
            anchors.fill: btn_menu
            onClicked: {
                if (btn_menu.state == "back") {
                    btn_menu.state = "menu"
                } else {
                    btn_menu.state = "back"
                }
            }
        }

        TextField {
            id: txt_Search
            text: qsTr("")
            anchors.right: text1.left
            anchors.rightMargin: 6
            placeholderText: "Search..."
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: btn_menu.right
            anchors.leftMargin: 13
            onFocusChanged: {
                if(txt_Search.focus) {
                    btn_menu.state = "menu"
                }
            }
        }

        Text {
            id: text1
            x: 264
            y: 22
            text: qsTr("↓0B/s, ↑0B/s")
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 13
            font.pixelSize: 12
        }
    }
}
