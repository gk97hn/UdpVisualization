import QtQuick 2.15
import QtQuick.Controls 2.15

Row {
    id: root
    spacing: 10
    property string label: ""
    property string state: "inactive" // "active" or "inactive"

    Label {
        text: root.label + ":"
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        width: 20
        height: 20
        radius: 10
        color: root.state === "active" ? "green" : "red"
        border.color: "#cccccc"
        border.width: 1
        anchors.verticalCenter: parent.verticalCenter
    }

    Label {
        text: root.state === "active" ? "Active" : "Inactive"
        anchors.verticalCenter: parent.verticalCenter
    }
}