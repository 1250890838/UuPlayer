import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    property color backgroundColor: "#f0f0f0"
    property color fontColor: "#333333"
    property color borderColor: "#aaaaaa"
    property color iconColor: "#666666"
    property color placeholderColor: "#999999"
    property string placeholderText: "搜索"
    property int radius: 6
    property int collapsedWidth: 48
    property int expandedWidth: 260
    property int animationDuration: 300
    readonly property bool expanded: _expanded
    readonly property string text: inputField.text
    signal searchRequested(string query)
    property bool _expanded: inputField.activeFocus
                             || inputField.text.length > 0
    width: _expanded ? expandedWidth : collapsedWidth
    height: 30

    Behavior on width {
        NumberAnimation {
            duration: root.animationDuration
            easing.type: Easing.InOutQuad
        }
    }
    implicitHeight: 30
    MouseArea {
        anchors.fill: parent
        enabled: !inputField.activeFocus
        onClicked: inputField.forceActiveFocus()
    }

    Rectangle {
        id: frame
        anchors.fill: parent
        radius: root.radius
        color: root.backgroundColor
        border.color: root.borderColor
        border.width: 1.5
        clip: true

        Item {
            id: searchButton
            width: 32
            height: parent.height
            anchors.left: parent.left
            Canvas {
                id: iconCanvas
                anchors.centerIn: parent
                width: 20
                height: 20
                onPaint: {
                    var ctx = getContext("2d") // [cite: 6]
                    ctx.reset()
                    ctx.strokeStyle = root.iconColor
                    ctx.lineWidth = 2
                    ctx.lineCap = "round"
                    var cx = 8, cy = 8, r = 6 // [cite: 7]
                    ctx.beginPath()
                    ctx.arc(cx, cy, r, 0, Math.PI * 2)
                    ctx.stroke()
                    var offset = r * Math.cos(Math.PI / 4) // [cite: 8]
                    ctx.beginPath()
                    ctx.moveTo(cx + offset, cy + offset)
                    ctx.lineTo(18, 18)
                    ctx.stroke() // [cite: 9]
                }
            }
        }

        TextField {
            id: inputField
            anchors.left: searchButton.right
            anchors.right: clearButton.left
            anchors.verticalCenter: parent.verticalCenter
            color: root.fontColor
            font.pixelSize: 14
            placeholderText: root.placeholderText
            placeholderTextColor: root.placeholderColor
            onTextChanged: {
                root.searchRequested(text)
            }
            Keys.onReturnPressed: root.searchRequested(text)
        }

        Rectangle {
            id: clearButton
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.verticalCenter: parent.verticalCenter
            width: 18
            height: 18
            radius: 9
            color: clearMouse.containsMouse ? "#dcdcdc" : "transparent"
            visible: root._expanded && inputField.text.length > 0
            Text {
                anchors.centerIn: parent
                text: "×"
                color: root.iconColor
                font.pixelSize: 16
                anchors.verticalCenterOffset: -1
            }
            MouseArea {
                id: clearMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    inputField.clear()
                    inputField.forceActiveFocus()
                }
            }
        }
    }
}
