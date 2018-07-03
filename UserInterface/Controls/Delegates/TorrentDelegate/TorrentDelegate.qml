import QtQml 2.2
import QtQml 2.11
import QtQuick 2.9
import io.backend 1.0
import QtQuick.Controls 2.2

SwipeDelegate {
    id: delegate
    width: 300
    height: 125

    property int eta
    property var size
    property string state
    property string name
    property real progress
    property string timeLeft
    signal renameRequested()

    padding: 0

    swipe.left: Label {
                  id: renameLabel
                  text: qsTr("Rename")
                  color: "white"
                  verticalAlignment: Label.AlignVCenter
                  padding: 12
                  height: parent.height

                  SwipeDelegate.onClicked: renameRequested()

                  background: Rectangle {
                      color: renameLabel.SwipeDelegate.pressed ? Qt.darker("#1565C0", 1.1) : "#1565C0"
                  }
              }

    swipe.right: Label {
                  id: deleteLabel
                  text: qsTr("Delete")
                  color: "white"
                  verticalAlignment: Label.AlignVCenter
                  padding: 12
                  height: parent.height
                  anchors.right: parent.right

                  SwipeDelegate.onClicked: listView.model.remove(index)

                  background: Rectangle {
                      color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                  }
              }



    contentItem: Item {
    Text {
        id: txt_torrentName
        text: delegate.name
        clip: true
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        font.pixelSize: 12
        font.bold: true
    }

    ProgressBar {
        id: progressBar
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: txt_timeLeft.top
        anchors.bottomMargin: 8
        value: progress
    }

    Text {
        id: txt_timeLeft
        y: 102
        text: delegate.eta
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        font.pixelSize: 12
    }

    Text {
        id: txt_percentage
        x: 269
        y: 102
        text: (delegate.progress * 100.0).toFixed(1) + "%"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        font.pixelSize: 12
    }

    Text {
        id: txt_size
        x: 8
        y: 67
        text: DownloadManager.valueToDataSize(delegate.size)
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 8
        font.pixelSize: 12
    }

    Text {
        id: txt_sizeDownloaded
        y: 67
        text: delegate.state
        anchors.bottom: progressBar.top
        anchors.bottomMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        font.pixelSize: 12
    }

    Rectangle {
        id: rectangle
        height: 1
        color: "#000000"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }
}
}
