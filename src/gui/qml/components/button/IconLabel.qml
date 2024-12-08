import QtQuick.Controls
import QtQuick

Item {
    id: root
    required implicitHeight
    required implicitWidth
    required property url icon
    required property url selectedIcon
    
    property bool selected
    property real margins: 5

    Image{
        id:image
        anchors.fill:parent
        anchors.margins:root.margins
        source:root.icon
    }
}
