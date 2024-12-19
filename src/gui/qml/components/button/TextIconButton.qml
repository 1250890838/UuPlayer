import QtQuick.Controls
import QtQuick

Item {
    id: root
    implicitWidth: row.implicitWidth
    implicitHeight: row.implicitHeight
    required property real iconWidth
    required property real iconHeight
    required property url icon
    required property string text

    property real margins: 0

    signal clicked

    Row {
        id: row
        spacing: 5
        Image {
            id: image
            source: root.icon
            width: root.iconWidth
            height: root.iconHeight
        }
        Text {
            id: text
            anchors.verticalCenter: parent.verticalCenter
            text: root.text
            color: mouseArea.containsMouse ? "black" : "gray"
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill:parent
        hoverEnabled: true
        cursorShape:Qt.ArrowCursor
        onClicked: {
            root.clicked();
        }
    }
}
