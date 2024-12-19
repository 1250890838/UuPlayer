import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import assets 1.0
import components 1.0
import gui 1.0

Window {
    id: root
    width: 377
    height: 521
    visible: true
    color: "transparent"
    flags: Qt.Window | Qt.FramelessWindowHint

    Component.onDestruction: console.log(`LoginDialog : ${this} has died!!!`)
    Component.onCompleted: function () {
        console.log(`LoginDialog : ${this} has borned!!!`);
    }

    Rectangle {
        id: container
        anchors.fill: parent
        anchors.margins: 10
        radius: 10

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
        propagateComposedEvents:true
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
                this.pp = point
            }
        }
    }
}
