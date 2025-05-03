import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import assets 1.0
import skins 1.0
import components 1.0
import QWindowKit 1.0
import service.api 1.0
import "leftNavigationPanel"
import "stackPages"
import "stackPages/cloudMusicSelectedPage"
import "titleBar"
import "playlistDetail"
import "playbackBar"
import "playbacklist"

Window {
    id: window
    minimumWidth: 1057
    minimumHeight: 752
    visible: false
    color: Skins.bodyBackColor
    property var commands: []

    Component.onCompleted: {
        windowAgent.setup(window)
        window.visible = true
    }
    WindowAgent {
        id: windowAgent
    }
    title: qsTr("Demo")
    Component {
        id: playlistDetailPage
        PlaylistDetailPage {}
    }

    function mainSwitchPage(page, properties) {
        stackView.replace(page, properties)
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        TitleBar {
            id: titleBar
            Layout.fillWidth: true
        }

        RowLayout {
            spacing: 0
            LeftNavigationPanel {
                id: navigationPanel
                Layout.preferredWidth: 205
                Layout.fillHeight: true
            }

            ColumnLayout {
                id: columnLayout
                StackView {
                    id: stackView
                    Layout.margins: 25
                    padding: (window.width - navigationPanel.width - this.width) / 2
                    Layout.alignment: Qt.AlignCenter
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    background: Rectangle {
                        color: Skins.bodyBackColor
                    }
                    popEnter: null
                    popExit: null
                    pushEnter: null
                    pushExit: null
                    replaceEnter: null
                    replaceExit: null
                    initialItem: CloudMusicSelectedPage {}
                }
            }
        }

        PlaybackBar {
            id: playbackBar
            visible: PlayService.num !== 0
            Layout.fillWidth: true
            implicitHeight: 80
            mediaData: PlayService.currentPlayItem
            Layout.bottomMargin: 30
        }
    }

    UScrollBar {
        id: globalScrollBar
        width: 10
        height: stackView.height
        x: parent.width - 15
        y: parent.height / 10
        z: 99
    }

    PlaybacklistPage {
        id: playbacklistPage
        x: window.width - this.width
        y: 85
        width: 383
        height: stackView.height
        enter: Transition {
            NumberAnimation {
                property: "x"
                from: window.width + 8
                to: window.width - playbacklistPage.width + 8
                duration: 300 // 动画时长 300ms
                easing.type: Easing.OutCubic // 缓动曲线
            }
        }
        exit: Transition {
            NumberAnimation {
                property: "x"
                to: window.width + 8
                from: window.width - playbacklistPage.width + 8
                duration: 300 // 动画时长 300ms
                easing.type: Easing.OutCubic // 缓动曲线
            }
        }
    }
}
