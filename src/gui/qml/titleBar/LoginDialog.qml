import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import assets 1.0
import components 1.0
import gui 1.0
import service 1.0
import network.errorcode 1.0

Window {
    id: root
    width: 387
    height: 535
    visible: true
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint

    Component.onDestruction: console.log(`LoginDialog : ${this} has died!!!`)
    Component.onCompleted: function () {
        console.log(`LoginDialog : ${this} has borned!!!`)
        LoginService.getQRCodeImage()
    }

    QtObject {
        id: settingGroup
        property int velocity: 300
        property int duration: 2000
    }

    Connections {
        id: connections
        target: LoginService
        function onQrCodeImageStatus(status) {
            if (status !== ErrorCode.NoError) {
                errorText.visible = true
                imageMouseArea.enabled = false
                console.log("error")
                desc.text = "使用 网易云音乐APP 扫码登陆"
                desc.x = 100
                desc.y = 350
            } else {
                console.log("noerror")
                imageMouseArea.enabled = true
                qrcodeImage.visible = true
                scanSampleImage.visible = true
                scanSampleImage.x = 45
                zeroToOneOpacityAnimation.start()
                scanSampleImage.y = 150
                qrcodeImage.x = 190
                qrcodeImage.y = 140
                qrcodeImage.width = 150
                qrcodeImage.height = 150
                desc.text = "使用 网易云音乐APP \n        扫码登陆      "
                desc.x = 190
                desc.y = 300
            }
        }

        function onQrCodeImageData(data) {
            qrcodeImage.source = data
        }

        function onLoginSuccess() {
            root.destroy()
        }
    }
    Rectangle {
        id: container
        anchors.fill: parent
        anchors.margins: 10
        radius: 10

        MouseArea {
            id: mouseArea
            z: 99
            anchors.top: parent.top
            width: parent.width
            height: 50
            propagateComposedEvents: true
            property point pp: Qt.point(0, 0) // previous point

            onPressed: function (mouse) {
                let point = mapToGlobal(mouse.x, mouse.y)
                this.pp = point
                console.log("Login dialog pressed!!!")
            }

            onPositionChanged: function (mouse) {
                if (mouse.buttons | Qt.LeftButton) {
                    let point = mapToGlobal(mouse.x, mouse.y)
                    root.x += point.x - this.pp.x
                    root.y += point.y - this.pp.y
                    this.pp = point
                }
            }
        }

        Text {
            id: title
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 85
            text: "扫码登陆"
            font {
                bold: true
                pixelSize: 21
                weight: 2
            }
        }

        Text {
            id: errorText
            text: "二维码加载失败！"
            anchors.centerIn: parent
            visible: false
            font {
                bold: true
                pixelSize: 21
                weight: 2
            }
        }

        Image {
            id: scanSampleImage
            visible: false
            x: 188
            y: 150
            opacity: 0
            width: 140
            height: 240
            OpacityAnimator on opacity {
                from: 0
                to: 1
                duration: 1000
            }
            fillMode: Image.PreserveAspectFit
            source: Icons.qrcodeScanSampleIcon
            Behavior on x {
                SmoothedAnimation {
                    velocity: settingGroup.velocity
                }
            }
            Behavior on y {
                SmoothedAnimation {
                    velocity: settingGroup.velocity
                }
            }
        }

        Image {
            id: qrcodeImage
            visible: false
            x: 100
            y: 153
            fillMode: Image.PreserveAspectFit
            width: 200
            height: 200
            smooth: true
            mipmap: true

            Behavior on x {
                SmoothedAnimation {
                    velocity: settingGroup.velocity
                }
            }
            Behavior on y {
                SmoothedAnimation {
                    velocity: settingGroup.velocity
                }
            }
            Behavior on width {
                SmoothedAnimation {
                    velocity: settingGroup.velocity
                }
            }
            Behavior on height {
                SmoothedAnimation {
                    velocity: settingGroup.velocity
                }
            }
        }

        IconButton {
            width: 28
            height: 28
            margins: 0
            icon: Icons.closeIcon
            hoveredIcon: Icons.closeIcon
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 20
            anchors.topMargin: 20
            onClicked: root.destroy()
        }

        Text {
            id: desc
            x: 100
            y: 350
            text: "使用 网易云音乐APP 扫码登陆"
            font {
                bold: true
                pixelSize: 14
            }
        }

        MouseArea {
            id: imageMouseArea
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents: true
            onContainsMouseChanged: function () {
                console.log(`contains mouse changed now :${contains}`)
                if (this.containsMouse) {
                    scanSampleImage.x = 45
                    scanSampleImage.y = 150
                    scanSampleImage.opacity = 1
                    qrcodeImage.x = 190
                    qrcodeImage.y = 140
                    qrcodeImage.width = 150
                    qrcodeImage.height = 150
                    desc.text = "使用 网易云音乐APP \n        扫码登陆      "
                    desc.x = 190
                    desc.y = 300
                    zeroToOneOpacityAnimation.start()
                } else {
                    scanSampleImage.x = 155
                    scanSampleImage.y = 150
                    scanSampleImage.opacity = 0
                    qrcodeImage.x = 100
                    qrcodeImage.y = 153
                    qrcodeImage.width = 200
                    qrcodeImage.height = 200
                    desc.text = "使用 网易云音乐APP 扫码登陆"
                    desc.x = 100
                    desc.y = 350
                    oneToZeroOpacityAnimation.start()
                }
            }
        }
    }

    NumberAnimation {
        id: zeroToOneOpacityAnimation
        target: scanSampleImage
        from: 0
        to: 1
        property: "opacity"
        duration: 1000
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: oneToZeroOpacityAnimation
        target: scanSampleImage
        from: 1
        to: 0
        property: "opacity"
        duration: 1000
        easing.type: Easing.InOutQuad
    }

    MultiEffect {
        id: effect
        source: container
        anchors.fill: container
        shadowBlur: 0.2
        shadowColor: "black"
        shadowEnabled: true
        shadowVerticalOffset: 0
    }
}
