import QtQuick 	2.11
import io.backend 1.0;
import "../BurgerMenuButton"
import QtQuick.Controls 2.4

Item {
    width: 400
    height: 50
    id: topBar

    property bool toggled: false

    onToggledChanged: {
        if (toggled) {
            btn_menu.state = "back"
        } else {
            btn_menu.state = "menu"
        }
    }

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
        }

        MouseArea {
            id: mouseArea
            anchors.fill: btn_menu
            onClicked: toggled = !toggled
        }

        TextField {
            id: txt_Search
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: text1.left
            anchors.rightMargin: 6
            placeholderText: "Search..."
            anchors.left: btn_menu.right
            anchors.leftMargin: 13
            onFocusChanged: if (focus) toggled = false
        }

        Text {
            id: text1
            width: 70
            text: GlobalTransferInfo.transferSpeed
            horizontalAlignment: Text.AlignLeft
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 6
            font.pixelSize: 12
        }
    }
}
