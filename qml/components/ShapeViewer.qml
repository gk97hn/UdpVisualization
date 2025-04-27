import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 6.2
import QtQuick.Shapes 1.15

Rectangle {
    id: root
    color: "#f0f0f0"
    border.color: "#cccccc"
    border.width: 1

    property var shapes: []
    property string xmlFilePath: ""

    function urlToLocalPath(url) {
        var strUrl = String(url);
        if (strUrl.indexOf("file:///") === 0) {
            if (Qt.platform.os === "windows") {
                return strUrl.slice(8);
            } else {
                return "/" + strUrl.slice(7);
            }
        }
        return strUrl;
    }

    onShapesChanged: {

        for (var i = shapeContainer.children.length - 1; i >= 0; i--) {
            if (shapeContainer.children[i] !== fileSelector) {
                shapeContainer.children[i].destroy();
            }
        }


        for (var j = 0; j < shapes.length; j++) {
            var shape = shapes[j];
            var component;
            var properties = {};


            if (shape.type === "Text") {
                component = textComponent;
                properties = {
                    "modelX": Number(shape.properties.x || 0),
                    "modelY": Number(shape.properties.y || 0),
                    "modelSize": Number(shape.properties.size || 12),
                    "modelColor": shape.properties.color || "black",
                    "modelText": shape.properties.text || ""
                };
            }
            else if (shape.type === "Line") {
                component = lineComponent;
                properties = {
                    "modelX1": Number(shape.properties.x1 || 0),
                    "modelY1": Number(shape.properties.y1 || 0),
                    "modelX2": Number(shape.properties.x2 || 100),
                    "modelY2": Number(shape.properties.y2 || 0),
                    "modelColor": shape.properties.color || "black",
                    "modelThickness": Number(shape.properties.thickness || 1)
                };
            }
            else {

                var componentUrl = "qrc:/qml/components/shapes/" + shape.type + ".qml";
                component = Qt.createComponent(componentUrl);


                for (var prop in shape.properties) {
                    var value = shape.properties[prop];
                    switch(prop) {
                        case "id": break;
                        case "path": properties["modelSource"] = value; break;
                        case "color": properties["modelColor"] = value; break;
                        case "size": properties["modelSize"] = Number(value); break;
                        case "thickness": properties["modelThickness"] = Number(value); break;
                        default:
                            if (["x","y","width","height","cx","cy","radius","x1","y1","x2","y2"].includes(prop)) {
                                properties["model" + prop.charAt(0).toUpperCase() + prop.slice(1)] = Number(value);
                            }
                    }
                }
            }

            if (component.status === Component.Ready || shape.type === "Text" || shape.type === "Line") {
                var obj;
                if (shape.type === "Text" || shape.type === "Line") {
                    obj = component.createObject(shapeContainer, properties);
                } else {
                    obj = component.createObject(shapeContainer, properties);
                }

                if (!obj) {
                    console.error("Error creating shape object:", component.errorString());
                }
            } else if (component.status === Component.Error) {
                console.error("Error loading shape component:", component.errorString());
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 10

        // File selector
        Row {
            id: fileSelector
            width: parent.width
            spacing: 10

            Label {
                text: "XML File:"
                anchors.verticalCenter: parent.verticalCenter
            }

            TextField {
                id: filePathField
                width: parent.width - 150
                text: xmlFilePath
                placeholderText: "Select XML file..."
                readOnly: true
            }

            Button {
                text: "Browse..."
                onClicked: fileDialog.open()
            }
        }

        // Shape container
        Item {
            id: shapeContainer
            width: parent.width
            height: parent.height - fileSelector.height - parent.spacing - parent.padding * 2
            clip: true
        }
    }

    FileDialog {
        id: fileDialog
        title: "Select XML File"
        nameFilters: ["XML files (*.xml)"]
        onAccepted: {
            var selectedPath = fileDialog.selectedFile ? fileDialog.selectedFile :
                               (fileDialog.selectedFiles.length > 0 ? fileDialog.selectedFiles[0] : "");
            if (selectedPath !== "") {
                xmlFilePath = urlToLocalPath(selectedPath);
                backend.loadXmlFile(xmlFilePath);
            }
        }
    }

    Component {
        id: textComponent
        Text {
            property real modelX: x
            property real modelY: y
            property int modelSize: font.pixelSize
            property color modelColor: color
            property string modelText: text

            x: modelX
            y: modelY
            font.pixelSize: modelSize
            color: modelColor
            text: modelText
        }
    }

    Component {
        id: lineComponent
        Shape {
            property real modelX1: 0
            property real modelY1: 0
            property real modelX2: 100
            property real modelY2: 0
            property color modelColor: "black"
            property real modelThickness: 1

            ShapePath {
                strokeColor: modelColor
                strokeWidth: modelThickness
                startX: modelX1
                startY: modelY1
                PathLine { x: modelX2; y: modelY2 }
            }
        }
    }

    Connections {
        target: backend
        function onShapesUpdated(shapesList) {
            root.shapes = shapesList;
        }
    }
}
