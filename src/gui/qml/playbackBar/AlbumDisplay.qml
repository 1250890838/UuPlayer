import QtQuick
import ui_base 1.0

Item {
    id: root
    required property url imageUrl
    property bool running: false
    Rectangle {
        id: albumContainer
        anchors.fill: parent
        color: "#060606"
        radius: albumContainer.width / 2

        RoundedImage {
            id: albumImage

            RotationAnimation on rotation {
                from: 0 // 起始角度
                to: 360 // 终止角度
                duration: 60000 // 动画时长（毫秒）
                loops: Animation.Infinite // 无限循环
                running: root.running // 自动启动
            }

            // 设置旋转中心点（默认是图像左上角 (0,0)）
            transform: Rotation {
                origin.x: albumImage.width / 2 // 中心点 X
                origin.y: albumImage.height / 2 // 中心点 Y
            }

            anchors.centerIn: parent
            width: parent.width / 4 * 2.7
            height: parent.height / 4 * 2.7
            isCircle: true
            imageUrl: root.imageUrl
            isTopLeftRounded: true
            isTopRightRounded: true
            isBottomLeftRounded: true
            isBottomRightRounded: true
        }
    }
}
