import QtQuick 2.15

Item {
    id: root
    required property color skinColor
    required property string skinText
    signal clicked

    Rectangle {
        id: rect
        color: root.skinColor
        radius: 8
        width: parent.width
        height: parent.height - (text.implicitHeight + text.anchors.top)

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: root.clicked()
        }
    }

    Text {
        id: text
        text: root.skinText
        anchors.top: rect.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.Center
    }
}
