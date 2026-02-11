import QtQuick
import QtQuick.Controls
import QtQuick.Effects

Rectangle {
    id: root
    property real radius
    required property url imageUrl
    property alias isTopLeftRounded: maskRect.isTopLeftRounded
    property alias isTopRightRounded: maskRect.isTopRightRounded
    property alias isBottomLeftRounded: maskRect.isBottomLeftRounded
    property alias isBottomRightRounded: maskRect.isBottomRightRounded
    property alias sourceSize: image.sourceSize
    property bool isCircle: false
    color: "transparent"

    BusyIndicator {
        id: busyIndicator
        anchors.fill: parent
        visible: image.status == Image.Loading
        running: image.status == Image.Loading
    }

    Image {
        id: image
        anchors.fill: parent
        source: root.imageUrl
        visible: false
        fillMode: Image.PreserveAspectFit
        smooth: true
    }

    MultiEffect {
        source: image
        anchors.fill: image
        maskEnabled: true
        maskSource: mask
    }

    Item {
        id: mask
        width: image.width
        height: image.height
        layer.enabled: true
        visible: false
        layer.smooth: true
        RoundedRectangle {
            id: maskRect
            width: image.width
            height: image.height
            radius: {
                if (root.isCircle) {
                    return maskRect.width / 2
                } else {
                    return root.radius
                }
            }
            color: "black"
        }
    }
}
