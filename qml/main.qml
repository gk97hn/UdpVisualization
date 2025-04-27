import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "components"
import "dialogs"
ApplicationWindow {
    id: root
    width: 1200
    height: 800
    visible: true
    title: qsTr("UDP Data Visualization")


    ErrorDialog { id: errorDialog }
    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        ShapeViewer {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.6
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.4

            UdpListView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1
            }

            ConnectionPanel {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1
            }

            CanBusPanel {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 1
            }
        }
    }
    Connections {
        target: backend
        function onErrorOccurred(error) {
            errorDialog.showError(error);
        }
    }
}
