import QtQuick

Rectangle {
    id: root
    property bool isTopLeftRounded: false
    property bool isTopRightRounded: false
    property bool isBottomLeftRounded: false
    property bool isBottomRightRounded: false

    Rectangle {
        id: topLeftRect
        color: root.color
        height: root.radius
        width: root.radius
        anchors.top: root.top
        anchors.left: root.left
        visible: !root.isTopLeftRounded
    }

    Rectangle {
        id: topRightRect
        color: root.color
        height: root.radius
        width: root.radius
        anchors.top: root.top
        anchors.right: root.right
        visible: !root.isTopRightRounded
    }

    Rectangle {
        id: bottomLeftRect
        color: root.color
        height: root.radius
        width: root.radius
        anchors.bottom: root.bottom
        anchors.left: root.left
        visible: !root.isBottomLeftRounded
    }

    Rectangle {
        id: bottomRightRect
        color: root.color
        height: root.radius
        width: root.radius
        anchors.bottom: root.bottom
        anchors.right: root.right
        visible: !root.isBottomRightRounded
    }
}
