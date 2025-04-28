import QtQuick
import QtQuick.Effects

Rectangle {
    id: root
    property real radius
    required property url imageUrl
    property alias isTopLeftRounded: maskRect.isTopLeftRounded
    property alias isTopRightRounded: maskRect.isTopRightRounded
    property alias isBottomLeftRounded: maskRect.isBottomLeftRounded
    property alias isBottomRightRounded: maskRect.isBottomRightRounded
    property bool isCircle: false
    color: "transparent"

    Image {
        id: image
        anchors.fill: parent
        source: root.imageUrl
        visible: false
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
