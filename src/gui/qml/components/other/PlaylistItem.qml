import QtQuick.Controls
import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    id: root
    required property var model
    Rectangle {
        id: container
        anchors.fill: parent
        radius: 25
        Column {
            anchors.fill: parent
            spacing: 0
            RoundedImage {
                id: image
                radius: 10
                imageUrl: model.coverUrl
                width: parent.width
                height: parent.height - 55
            }

            Rectangle {
                id: descRect
                width: parent.width
                height: 55
                radius: 10
                color: "black"
                Text {
                    color: "white"
                    font.pointSize: 9
                    anchors.margins: 7
                    anchors.fill: parent
                    text: model.name
                    wrapMode: Text.WordWrap
                }
            }
        }
    }
}
