import QtQuick.Controls
import QtQuick
import QtQuick.Layouts

Item {
    id: root
    required property var model
    implicitWidth: 182
    implicitHeight: 234
    Rectangle {
        id: container
        anchors.fill: parent
        radius: 8
        ColumnLayout {
            anchors.fill:parent
            Image {
                id: image
                Layout.fillWidth: true
                Layout.fillHeight: true
                source: model.coverUrl
            }

            Rectangle {
                id: descRect
                Layout.fillWidth: true
                implicitHeight: 60
                Text {
                    anchors.centerIn:parent
                    text: model.name
                }
            }
        }
    }
}
