import QtQuick 2.15
import QtQuick.Shapes 1.15

Shape {
    property real modelCx: 0
    property real modelCy: 0
    property real modelRadius: 50
    property color modelColor: "black"

    ShapePath {
        fillColor: modelColor
        strokeWidth: 0

        PathAngleArc {
            centerX: modelCx
            centerY: modelCy
            radiusX: modelRadius
            radiusY: modelRadius
            startAngle: 0
            sweepAngle: 360
        }
    }
}
