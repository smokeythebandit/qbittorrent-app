import QtQuick 	2.11
import io.backend 1.0
import QtQuick.Controls 2.4

Item {
    ListView {
               id: listView
               anchors.fill: parent
               headerPositioning: ListView.OverlayHeader
               header: Pane {
                   id: header
                   z: 2
                   width: parent.width
                   contentHeight: lbl_status.height

                   Text {
                       id: lbl_status
                       text: "Status"
                   }

                   MenuSeparator {
                       parent: header
                       width: parent.width
                       anchors.verticalCenter: parent.bottom
                   }
               }

               footer: ItemDelegate {
                   id: footer
                   text: qsTr("Footer")
                   width: parent.width

                   MenuSeparator {
                       parent: footer
                       width: parent.width
                       anchors.verticalCenter: parent.top
                   }
               }

               model: Torrents.categories

               delegate: Text {
                   text: display
                   width: parent.width
               }

               ScrollIndicator.vertical: ScrollIndicator { }
           }
}