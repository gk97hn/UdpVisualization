import QtQuick 2.15

Text {
    property real modelX: 0
    property real modelY: 0
    property int modelSize: 12
    property color modelColor: "black"
    property string modelText: ""

    x: modelX
    y: modelY
    font.pixelSize: modelSize
    color: modelColor
    text: modelText
}
