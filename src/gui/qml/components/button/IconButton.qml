import QtQuick.Controls
import QtQuick

Item {
    id: root
   // required implicitWidth
   // required implicitHeight
    required property url icon
    required property url hoveredIcon
    property int cursorShape:Qt.PointingHandCursor

    property real margins: 0

    signal clicked

    Image {
        id:image
        anchors.fill: parent
        anchors.margins: root.margins
        source: mouseArea.containsMouse ? root.hoveredIcon : root.icon
        fillMode:Image.PreserveAspectFit
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape:root.cursorShape
        onClicked: {
            root.clicked();
        }
    }
}
