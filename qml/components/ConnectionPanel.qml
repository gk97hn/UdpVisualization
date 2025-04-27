import QtQuick 2.15
import QtQuick.Controls 2.15

Frame {
    id: root
    padding: 10

    Column {
        anchors.fill: parent
        spacing: 10

        Label {
            text: "UDP Connection"
            font.bold: true
        }

        Grid {
            width: parent.width
            columns: 2
            spacing: 10

            Label { text: "Address:" }
            TextField {
                id: addressField
                width: parent.width / 2 - parent.spacing
                text: "127.0.0.1"
            }

            Label { text: "Port:" }
            TextField {
                id: portField
                width: parent.width / 2 - parent.spacing
                text: "5566"
                validator: IntValidator { bottom: 1024; top: 65535 }
            }
        }

        Row {
            width: parent.width
            spacing: 10

            Button {
                text: "Connect as Listener"
                width: (parent.width - parent.spacing) / 2
                onClicked: {
                    backend.connectToUdp(addressField.text, parseInt(portField.text), false);
                }
            }

            Button {
                text: "Connect as Publisher"
                width: (parent.width - parent.spacing) / 2
                onClicked: {
                    backend.connectToUdp(addressField.text, parseInt(portField.text), true);
                }
            }
        }
        Row{
            width: parent.width
            spacing: 10
            StatusIndicator {
                id: connectionStatus
                width: parent.width/2
                label: "Connection Status"
                state: backend.connectionStatus ? "active" : "inactive"
            }

            StatusIndicator {
                id: publisherStatus
                width: parent.width/2
                label: "Publisher Status"
                state: backend.publisherStatus ? "active" : "inactive"
            }
        }


        TextArea {
            id: messageField
            width: parent.width
            height: 30
            placeholderText: "Enter message to send..."
        }

        Button {
            text: "Send Message"
            width: parent.width
            enabled: true
            onClicked: {
                backend.sendUdpMessage(messageField.text);
                messageField.clear();
            }
        }

        ScrollView {
            width: parent.width
            height: 100
            TextArea {
                id: receivedMessages
                height: parent.height
                readOnly: true
                textFormat: TextEdit.PlainText

            }
        }
    }

    Connections {
        target: backend
        function onUdpMessagesReceived(message) {
            receivedMessages.append(message + "\n");
        }
        function onConnectionStatusChanged(connected) {
            connectionStatus.state = connected ? "active" : "inactive";
        }
        function onPublisherStatusChanged(active) {
            publisherStatus.state = active ? "active" : "inactive";
        }
    }
}
