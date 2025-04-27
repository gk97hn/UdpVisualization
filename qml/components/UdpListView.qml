import QtQuick 2.15
import QtQuick.Controls 2.15

Frame {
    id: root
    padding: 10

    property alias model: listView.model
    property alias currentIndex: listView.currentIndex

    Column {
        anchors.fill: parent
        spacing: 10

        Label {
            text: "Available UDP Sockets"
            font.bold: true
        }

        Button {
            id: refreshButton
            text: "View Available Sockets"
            width: parent.width
            onClicked: backend.refreshUdpSockets()
        }

        ListView {
            id: listView
            width: parent.width
            height: parent.height - refreshButton.height - parent.spacing
            clip: true
            spacing: 5

            delegate: Rectangle {
                width: listView.width
                height: 40
                color: ListView.isCurrentItem ? "#e0e0e0" : "white"
                border.color: "#cccccc"
                radius: 3

                Row {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 10

                    Label {
                        text:udpModel.address + ":" + model.port
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Label {
                        text: udpModel.protocol
                        anchors.verticalCenter: parent.verticalCenter
                        font.italic: true
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: listView.currentIndex = index
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }

    }

    Connections {
        target: backend
        function onUdpSocketsUpdated(socketsList) {
            listView.model = socketsList;
        }
    }
}
