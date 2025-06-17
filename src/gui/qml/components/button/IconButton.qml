import QtQuick.Controls
import QtQuick

Item {
    id: root
    // required implicitWidth
    // required implicitHeight
    required property url icon
    required property url hoveredIcon
    property int cursorShape: Qt.PointingHandCursor

    property color backgroundColor: "transparent"
    property color borderColor: "transparent"
    property color backgroundHoveredColor: "transparent"
    property int borderWidth: 0
    property int radius: 0

    property real margins: 0

    signal clicked

    Rectangle {
        id: imageContainer
        radius: root.radius
        anchors.fill: parent
        color: mouseArea.containsMouse ? root.backgroundHoveredColor : root.backgroundColor
        border.color: root.borderColor
        border.width: root.borderWidth
        Image {
            id: image
            anchors.fill: parent
            anchors.margins: root.margins
            source: mouseArea.containsMouse ? root.hoveredIcon : root.icon
            fillMode: Image.PreserveAspectFit
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: root.cursorShape
        onClicked: {
            root.clicked()
        }
    }
}
