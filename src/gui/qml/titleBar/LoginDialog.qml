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
        console.log(`LoginDialog : ${this} has borned!!!`);
        LoginService.getQRCodeImage();
    }

    Connections {
        id: connections
        target: LoginService
        function onQrCodeImageStatus(status) {
            console.log(ErrorCode.NoError)
            console.log(ErrorCode)
            if (status != ErrorCode.NoError) {
                errorText.visible=true
                console.log("error")
            }
            else{
                console.log("noerror")
                qrcode.visible=true
            }
        }

        function onQrCodeImageData(data) {
            qrcode.source = data;
        }

        function onLoginSuccess(){
            root.destroy();
        }
    }
    Rectangle {
        id: container
        anchors.fill: parent
        anchors.margins: 10
        radius: 10
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
            id:errorText
            text:"二维码加载失败！"
            anchors.centerIn:parent
            visible:false
            font {
                bold: true
                pixelSize: 21
                weight: 2
            }
        }
        Image {
            id: qrcode
            visible:false
            anchors.top: title.bottom
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
            width: 210
            height: 210
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
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: qrcode.bottom
            anchors.topMargin: 20
            text: "使用 网易云音乐APP 扫码登陆"
            font {
                bold: true
                pixelSize: 14
            }
        }
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
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        property point pp: Qt.point(0, 0)// previous point

        onPressed: function (mouse) {
            let point = mapToGlobal(mouse.x, mouse.y);
            this.pp = point;
            console.log("Login dialog pressed!!!");
        }

        onPositionChanged: function (mouse) {
            if (mouse.buttons | Qt.LeftButton) {
                let point = mapToGlobal(mouse.x, mouse.y);
                root.x += point.x - this.pp.x;
                root.y += point.y - this.pp.y;
                this.pp = point;
            }
        }
    }
}
