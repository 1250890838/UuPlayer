import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0

Item {
    id: root
    Pane {
        anchors.fill: parent
                background: Rectangle {
            color: "transparent"
        }
        Text {
            id: title
            anchors.centerIn: parent
            text: "歌手"
            font.pixelSize: 40
            font.bold: true
            color: "black"
        }
    }
}
