import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    property color backgroundColor: "#f0f0f0"
    property color fontColor: "#333333"
    property color borderColor: "#aaaaaa"
    property color iconColor: "#666666"
    property color placeholderColor: "#999999"
    property string placeholderText: "搜索..."
    property int radius: 6
    property int collapsedWidth: 48
    property int expandedWidth: 260
    property int animationDuration: 300

    readonly property bool expanded: _expanded
    readonly property string text: inputField.text

    signal searchRequested(string query)

    property bool _expanded: false

    implicitWidth: collapsedWidth
    implicitHeight: 30

    Connections {
        target: typeof window !== "undefined" ? window : null
        enabled: false
    }

    Rectangle {
        id: frame
        anchors.right: parent.right
        height: parent.height
        width: root._expanded ? root.expandedWidth : root.collapsedWidth
        radius: root.radius
        color: root.backgroundColor
        border.color: root.borderColor
        border.width: 1.5
        clip: true

        Behavior on width {
            NumberAnimation {
                duration: root.animationDuration
                easing.type: Easing.InOutQuad
            }
        }

        Item {
            id: searchButton
            width: root.collapsedWidth
            height: parent.height
            anchors.left: parent.left

            Canvas {
                id: iconCanvas
                anchors.centerIn: parent
                width: 20
                height: 20
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.reset()
                    ctx.strokeStyle = root.iconColor
                    ctx.lineWidth = 2
                    ctx.lineCap = "round"
                    var cx = 8, cy = 8, r = 6
                    ctx.beginPath()
                    ctx.arc(cx, cy, r, 0, Math.PI * 2)
                    ctx.stroke()
                    var offset = r * Math.cos(Math.PI / 4)
                    ctx.beginPath()
                    ctx.moveTo(cx + offset, cy + offset)
                    ctx.lineTo(18, 18)
                    ctx.stroke()
                }
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if (!root._expanded) {
                        root._expanded = true
                        inputField.forceActiveFocus()
                    } else {
                        root.searchRequested(inputField.text)
                    }
                }
            }
        }

        TextField {
            id: inputField
            anchors.left: searchButton.right
            anchors.right: parent.right
            anchors.rightMargin: 12
            anchors.verticalCenter: parent.verticalCenter
            color: root.fontColor
            font.pixelSize: 14
            placeholderText: root.placeholderText
            placeholderTextColor: root.placeholderColor

            background: Item {}

            visible: root._expanded
            opacity: root._expanded ? 1.0 : 0.0
            Behavior on opacity {
                NumberAnimation {
                    duration: root.animationDuration
                }
            }

            Keys.onReturnPressed: root.searchRequested(inputField.text)
            Keys.onEnterPressed: root.searchRequested(inputField.text)

            onActiveFocusChanged: {
                if (!activeFocus && inputField.text.length === 0) {
                    root._expanded = false
                }
            }
        }
    }
}
