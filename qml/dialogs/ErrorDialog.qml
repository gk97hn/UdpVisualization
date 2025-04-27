import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Dialog {
    id: root
    title: "Error"
    modal: true
    standardButtons: Dialog.Ok
    width: 400
    height: 150

    property string errorMessage: ""

    function showError(message) {
        errorMessage = message;
        open();
    }

    Label {
        anchors.fill: parent
        text: errorMessage
        wrapMode: Text.Wrap
    }
}