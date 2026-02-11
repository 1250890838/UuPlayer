import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ui_base 1.0

Item {
    id: root
    Pane {
        anchors.fill: parent
        background: Rectangle {
            color: "gray"
        }
        Text {
            id: title
            anchors.centerIn: parent
            text: "精选"
            font.pixelSize: 40
            font.bold: true
            color: "black"
        }
    }
}
