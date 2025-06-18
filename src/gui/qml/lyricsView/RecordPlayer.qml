import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 400
    height: 400

    // 光盘
    Rectangle {
        id: disc
        width: 200
        height: 200
        radius: width / 2
        color: "transparent"
        border.color: "gray"
        anchors.centerIn: parent

        // 光盘纹理（模拟唱片纹路）
        Repeater {
            model: 20
            Rectangle {
                width: disc.width - 20
                height: 1
                color: "black"
                anchors.centerIn: disc
                rotation: index * 18 // 每18度画一条线
            }
        }

        // 光盘旋转动画
        RotationAnimation {
            id: discRotation
            target: disc
            from: 0
            to: 360
            duration: 2000 // 旋转速度
            loops: Animation.Infinite
            running: false // 默认不旋转
        }
    }

    // 播放杆（模拟唱臂）
    Rectangle {
        id: tonearm
        width: 120
        height: 4
        color: "black"
        transformOrigin: Item.Left // 以左端为旋转中心
        x: disc.x + disc.width / 2
        y: disc.y - 50
        rotation: -30 // 初始抬起角度

        // 杆的底座（固定点）
        Rectangle {
            width: 10
            height: 10
            radius: 5
            color: "silver"
            anchors.right: parent.left
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // 播放/停止按钮
    Button {
        text: player.playing ? "Stop" : "Play"
        onClicked: player.playing ? player.stop() : player.play()
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    // 播放器逻辑
    property bool playing: false

    function play() {
        playing = true
        discRotation.start() // 开始旋转光盘
        tonearmAnim.to = 0 // 杆子落下到0度（水平）
        tonearmAnim.start()
    }

    function stop() {
        playing = false
        discRotation.stop() // 停止旋转光盘
        tonearmAnim.to = -30 // 杆子抬起
        tonearmAnim.start()
    }

    // 杆子动画
    NumberAnimation {
        id: tonearmAnim
        target: tonearm
        property: "rotation"
        duration: 500 // 动画时长
        easing.type: Easing.InOutQuad // 平滑缓动
    }
}
