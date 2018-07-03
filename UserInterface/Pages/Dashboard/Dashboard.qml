import QtQuick 2.11
import io.backend 1.0
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.4
import QtQuick.Window 2.3
import "../../Controls/Delegates/TorrentDelegate"
import "../../Controls/TopBar"
import "../../Controls/SideBar"
Item {
    id: dashboard

    TopBar {
        id: topbar
        height: 50
        z: 10
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        onToggledChanged: {
            if(topbar.toggled) drawer.open()
            else drawer.close()
        }
    }

    Drawer {
        clip: true
        id: drawer
        y: topbar.height
        z: 10
        dragMargin: 20
        implicitWidth: topbar.width * 0.6
        height: dashboard.height - topbar.height
        edge: Qt.LeftEdge
        onOpened: topbar.toggled = true
        onClosed: topbar.toggled = false
        SideBar{
            anchors.fill: parent
        }
    }
    Popup {
        id: popup
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        z:1000
        width: 300
        height: 200
        modal: true
        focus: true
        TextInput{
            width: parent.width
        }

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }
    ScrollView {
        z: 1
        id: scrollView
        anchors.top: topbar.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        ScrollBar.horizontal.interactive: true
        ScrollBar.vertical.interactive: true
        ListView {
            model: DownloadManager.torrents
            delegate: TorrentDelegate {
                width: parent.width
                name: model.name
                size: model.size
                state: model.state
                progress: model.progress
                onRenameRequested: {
                    popup.open()
                }
                onClicked: popup.open()
            }
        }
    }
}
