import QtQuick
import QtQuick.Effects

Item {
    id: root
    required property real radius
    required property url imageUrl

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

        Rectangle {
            id: maskRect
            width: image.width
            height: image.height
            radius: root.radius
            color: "black"
        }
    }
}
