import QtQuick 2.6
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

               model:   ListModel {
                   ListElement {
                       name: "All"
                   }
                   ListElement {
                       name: "Downloading"
                   }
                   ListElement {
                       name: "Seeding"
                   }
                   ListElement {
                       name: "Completed"
                   }
                   ListElement {
                       name: "Resumed"
                   }
                   ListElement {
                       name: "Paused"
                   }
                   ListElement {
                       name: "Active"
                   }
                   ListElement {
                       name: "Inactive"
                   }
                   ListElement {
                       name: "Errored"
                   }
               }

               delegate: ItemDelegate {
                   text: qsTr(name)
                   width: parent.width
               }

               ScrollIndicator.vertical: ScrollIndicator { }
           }
}
