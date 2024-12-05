import QtQuick.Controls
import QtQuick

Item {
    id: root
    required implicitWidth 
    required implicitHeight
    required property url icon
    property real margins: 5

    signal clicked

    Image {
        anchors.fill: parent
        anchors.margins: root.margins
        source: root.icon
    }
}
