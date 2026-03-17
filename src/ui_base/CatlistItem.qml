import QtQuick

Item {
    id: root

    required property string text
    property color backgroundColor: "#F7f9fc"
    property color borderColor: "#E0E0E0"
    property real borderWidth: 1

    signal clicked

    implicitWidth: textLabel.implicitWidth + 30
    implicitHeight: textLabel.implicitHeight + 15

    Rectangle {
        id: container
        anchors.fill: parent
        color: root.backgroundColor
        radius: 15
        border {
            width: root.borderWidth
            color: (playlistSquareSubpageColumnLayout.currentCatItem == this || mouseArea.containsMouse) ? "red" : root.borderColor
        }
        Text {
            id: textLabel
            anchors.centerIn: parent
            text: root.text
            font.pointSize: 9
            color: (playlistSquareSubpageColumnLayout.currentCatItem == this || mouseArea.containsMouse) ? "red" : "black"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onClicked: root.clicked()
        }
    }
}
