import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import assets 1.0

Item {
    id: root
    implicitHeight: 35
    property var colors: [] // default | hovered | selected
    property alias radius: container.radius
    property alias text: label.text
    property url icon
    property url selectedIcon

    signal clicked

    Rectangle {
        id: container
        anchors.fill: parent
        color: {
            if (currentItem == root) {
                return root.colors[2]
            } else if (mouseArea.containsMouse)
                return root.colors[1]
            else
                return root.colors[0]
        }

        Row {
            spacing: 10
            padding: 0
            leftPadding: 10
            anchors.fill: parent
            IconLabel {
                id: iconLabel
                width: 20
                height: 20
                margins: 0.2
                icon: currentItem === root ? root.selectedIcon : root.icon
                anchors.verticalCenter: parent.verticalCenter
            }
            Label {
                id: label
                font.pointSize: 10.2
                color: currentItem === root ? "#FFFFFF" : "gray"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            root.clicked()
        }
    }
}
