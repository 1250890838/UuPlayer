import QtQuick

Item {
    id: root
    required property list<string> sortOptions
    Rectangle {
        id: container
        anchors.fill: parent
        radius: 8
        color: hoverHandler.hovered ? Qt.rgba(230, 230, 230,
                                              0.8) : "transparent"
        HoverHandler {
            id: hoverHandler
            cursorShape: Qt.PointingHandCursor
        }
        TapHandler {
            id: tapHandler
        }
    }
}
