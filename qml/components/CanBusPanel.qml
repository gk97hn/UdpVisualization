import QtQuick 2.15
import QtQuick.Controls 2.15

Frame {
    id: root
    padding: 10

    Column {
        anchors.fill: parent
        spacing: 10

        Label {
            text: "SocketCAN Configuration"
            font.bold: true
        }

        ComboBox {
            id: interfaceCombo
            width: parent.width
            model: backend.getCanInterfaces()
            onActivated: {
                baudRateCombo.enabled = index !== -1;
            }
        }

        ComboBox {
            id: baudRateCombo
            width: parent.width
            enabled: true
            model: ["125000", "250000", "500000", "1000000"]
        }

        Button {
            text: "Connect"
            width: parent.width
            onClicked: {
                backend.setupCanInterface(interfaceCombo.currentText, parseInt(baudRateCombo.currentText));
            }
        }

        TextArea {
            id: canMessageField
            width: parent.width
            height: 60
            placeholderText: "Enter CAN message (hex)..."
        }

        Button {
            text: "Send CAN Message"
            width: parent.width
            onClicked: {
                backend.sendCanMessage(canMessageField.text);
                canMessageField.clear();
            }
        }

        ScrollView {
            width: parent.width
            height: 100
            TextArea {
                id: receivedCanMessages
                readOnly: true
                textFormat: TextEdit.PlainText
            }
        }
    }
}
