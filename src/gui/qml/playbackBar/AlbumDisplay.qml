import QtQuick
import components 1.0

Item {
    required property url imageUrl
    Rectangle {
        id: albumContainer
        anchors.fill: parent
        color: "#060606"
        radius: albumContainer.width / 2

        RoundedImage {
            id: albumImage
            anchors.fill: parent
        }
    }
}
