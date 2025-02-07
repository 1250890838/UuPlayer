import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import components 1.0

Item {
    implicitHeight: 60
    Rectangle {
        anchors.fill: parent
        radius: 8
        RowLayout {
            id: rowLayout
            anchors.fill: parent
            Text {
                id: index
                text: model.index
            }
            RoundedImage {
                id: image
                implicitWidth: 36
                implicitHeight: 36
                radius: 5
                imageUrl: model.album.imageUrl
                isTopLeftRounded: true
                isTopRightRounded: true
                isBottomLeftRounded: true
                isBottomRightRounded: true
            }
        }
    }
}
