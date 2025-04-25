import QtQuick

// 正方形显示为圆形
Item {
    id: root
    required property url imageUrl
    property bool isCircle: false
    property int radius

    Rectangle {
        id: container
        anchors.fill: parent
        radius: {
            if (root.isCircle) {
                return container.width / 2
            }
            return root.radius
        } // 圆角半径为边长一半
        clip: true // 裁剪超出区域

        Image {
            anchors.fill: parent
            source: root.imageUrl
            fillMode: Image.PreserveAspectCrop // 保持比例并裁剪填充
        }
    }
}
