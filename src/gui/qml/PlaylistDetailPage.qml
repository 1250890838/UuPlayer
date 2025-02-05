import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import service 1.0
import components 1.0

Pane {
    id: root
    required property var detail
    background: Rectangle {
        color: "transparent"
    }
    RoundedImage {
        id: coverImage
        radius: 10
        imageUrl: detail.coverUrl
        width: 170
        height: 170
        isTopLeftRounded: true
        isTopRightRounded: true
        isBottomLeftRounded: true
        isBottomRightRounded: true
    }
}
