import QtQuick
import QtQuick.Effects

Rectangle {
    id: root
    required property real radius
    required property url imageUrl
    property alias isTopLeftRounded: maskRect.isTopLeftRounded
    property alias isTopRightRounded: maskRect.isTopRightRounded
    property alias isBottomLeftRounded: maskRect.isBottomLeftRounded
    property alias isBottomRightRounded: maskRect.isBottomRightRounded

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
            radius: root.radius
            color: "black"
            Text {
                color: "white"
                font.pointSize: 9
                anchors.margins: 7
                anchors.fill: parent
                text: model.name
                wrapMode: Text.WordWrap
            }
        }
    }
}
