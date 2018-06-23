import QtQuick 2.0
import QtQuick.Controls 2.2
import "../../Controls/TopBar"

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
            if(toggled) drawer.open()
            else drawer.close()
        }
    }

    Drawer {
        id: drawer
        interactive: false
        y: topbar.height
        z: 10
        width: 360
        height: dashboard.height - topbar.height
        edge: Qt.LeftEdge

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
                  model: 200
                  delegate: ItemDelegate {
                      text: "Item " + index
                  }
              }
    }
}
