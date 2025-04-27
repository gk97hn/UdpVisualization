import QtQuick 2.15
import QtQuick.Shapes 1.15

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

        PathLine {
            x: modelX2
            y: modelY2
        }
    }
}
