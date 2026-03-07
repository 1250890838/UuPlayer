import QtQuick
import QtQuick.Window
import QtQuick.Controls
import controller
import ui_base 1.0
import assets 1.0

Window {
    id: root
    minimumWidth: 420
    minimumHeight: 120
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool
    color: "transparent"
    readonly property int compact: 0
    readonly property int panel: 1
    readonly property int locked: 2
    property int uiMode: root.compact
    property int resizeMargin: 8
    property int hoverToShowMs: 600
    property int leaveToHideMs: 1500
    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        radius: 8
        color: Qt.rgba(0, 0, 0, 0.35)
        visible: root.uiMode == root.panel
    }
    Row {
        id: toolbar
        spacing: 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 14
        opacity: root.uiMode == panel ? 1 : 0
        IconButton {
            icon: Icons.desktoplyricPreviousIcon
            hoveredIcon: Icons.desktoplyricPreviousIcon
            width: 14
            height: 14
            onClicked: PlayController.previous()
            anchors.verticalCenter: parent.verticalCenter
        }
        IconButton {
            icon: Icons.desktoplyricPlayIcon
            hoveredIcon: Icons.desktoplyricPlayIcon
            width: 20
            height: 20
            onClicked: PlayController.play()
            anchors.verticalCenter: parent.verticalCenter
        }
        IconButton {
            icon: Icons.desktoplyricNextIcon
            hoveredIcon: Icons.desktoplyricNextIcon
            width: 14
            height: 14
            onClicked: PlayController.next()
            anchors.verticalCenter: parent.verticalCenter
        }
        IconButton {
            icon: Icons.desktoplyricSettingIcon
            hoveredIcon: Icons.desktoplyricSettingIcon
            width: 21
            height: 21
            anchors.verticalCenter: parent.verticalCenter
        }
        IconButton {
            icon: Icons.desktoplyricLockedIcon
            hoveredIcon: Icons.desktoplyricLockedIcon
            width: 20
            height: 20
            anchors.verticalCenter: parent.verticalCenter
        }
        IconButton {
            icon: Icons.desktoplyricCloseIcon
            hoveredIcon: Icons.desktoplyricCloseIcon
            width: 20
            height: 20
            anchors.verticalCenter: parent.verticalCenter
            onClicked: root.visible = false
        }
    }
    Item {
        id: lyricArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolbar.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12
        Text {
            text: {
                if (lyricsViewPage.currentLyricText.length === 0)
                    return "歌词正在加载中 ~~~";
                else
                    return lyricsViewPage.currentLyricText;
            }
            font.pointSize: (parent.height - 6) / 2
            color: "pink"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        MouseArea {
            anchors.fill: parent
            enabled: true
            acceptedButtons: Qt.LeftButton
            onDoubleClicked: m => root.startSystemMove()
            cursorShape: Qt.PointingHandCursor
        }
        HoverHandler {
            id: hoverHandler
        }
        TapHandler {
            acceptedButtons: Qt.LeftButton
            onTapped: {
                root.uiMode = root.panel;
            }
        }
        Timer {
            id: hoverShowTimer
            interval: root.hoverToShowMs
            repeat: false
            onTriggered: {
                root.uiMode = root.panel;
            }
        }
        Timer {
            id: leaveHideTimer
            interval: root.leaveToHideMs
            repeat: false
            onTriggered: root.uiMode = root.compact
        }
        Connections {
            target: hoverHandler
            function onHoveredChanged() {
                if (hoverHandler.hovered) {
                    leaveHideTimer.stop();
                    if (root.uiMode === root.compact) {
                        hoverShowTimer.restart();
                    }
                } else {
                    hoverShowTimer.stop();
                    if (root.uiMode === root.panel) {
                        leaveHideTimer.restart();
                    }
                }
            }
        }
    }
    Item {
        id: resizeLayer
        anchors.fill: parent
        enabled: root.uiMode == root.panel
        MouseArea {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: root.resizeMargin
            cursorShape: Qt.SizeHorCursor
            onPressed: m => root.startSystemResize(Qt.LeftEdge)
        }
        MouseArea {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: root.resizeMargin
            cursorShape: Qt.SizeHorCursor
            onPressed: m => root.startSystemResize(Qt.RightEdge)
        }
        MouseArea {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: root.resizeMargin
            cursorShape: Qt.SizeVerCursor
            onPressed: m => root.startSystemResize(Qt.TopEdge)
        }
        MouseArea {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: root.resizeMargin
            cursorShape: Qt.SizeVerCursor
            onPressed: m => root.startSystemResize(Qt.BottomEdge)
        }
        MouseArea {
            anchors.left: parent.left
            anchors.top: parent.top
            width: root.resizeMargin
            height: root.resizeMargin
            cursorShape: Qt.SizeFDiagCursor
            onPressed: m => root.startSystemResize(Qt.LeftEdge | Qt.TopEdge)
        }
        MouseArea {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: root.resizeMargin
            height: root.resizeMargin
            cursorShape: Qt.SizeFDiagCursor
            onPressed: m => root.startSystemResize(Qt.RightEdge | Qt.BottomEdge)
        }
        MouseArea {
            anchors.right: parent.right
            anchors.top: parent.top
            width: root.resizeMargin
            height: root.resizeMargin
            cursorShape: Qt.SizeBDiagCursor
            onPressed: m => root.startSystemResize(Qt.RightEdge | Qt.TopEdge)
        }
        MouseArea {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: root.resizeMargin
            height: root.resizeMargin
            cursorShape: Qt.SizeBDiagCursor
            onPressed: m => root.startSystemResize(Qt.LeftEdge | Qt.BottomEdge)
        }
    }
}
