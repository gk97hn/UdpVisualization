import QtQuick 2.15

Image {
    property real modelX: 0
    property real modelY: 0
    property real modelWidth: 100
    property real modelHeight: 100
    property string modelSource: ""

    x: modelX
    y: modelY
    width: modelWidth
    height: modelHeight
    source: modelSource
    fillMode: Image.PreserveAspectFit
}
