import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import assets 1.0
import service.api 1.0
import components 1.0

// Lyrics View Page show lyrics
Page {
    id: root
    property var media

    function updateMedia() {
        media = PlayService.currentPlayItem
    }
    background: Rectangle {
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop {
                position: 0.0
                color: "#14161e"
            }
            GradientStop {
                position: 1.0
                color: "#3a3e4c"
            }
        }
    }
    IconButton {
        icon: Icons.downIcon
        x: 40
        y: 25
        width: 40
        height: 40
        margins: 10
        hoveredIcon: Icons.downIcon
        radius: 5
        backgroundColor: "#2f3b3b"
        backgroundHoveredColor: "#354040"
        borderColor: "#404b4b"
        borderWidth: 1
        onClicked: function () {
            console.log("down button on lyrics view page clicked!")
            root.state = "closed"
        }
        Component.onCompleted: windowAgent.setHitTestVisible(this)
    }

    IconButton {
        icon: Icons.fullscreenIcon
        x: 95
        y: 25
        width: 40
        height: 40
        margins: 10
        radius: 5
        hoveredIcon: Icons.fullscreenIcon
        backgroundColor: "#2f3b3b"
        backgroundHoveredColor: "#354040"
        borderColor: "#404b4b"
        borderWidth: 1
        Component.onCompleted: windowAgent.setHitTestVisible(this)
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 100
        spacing: 100
        Rectangle {
            id: testRect
            Layout.preferredWidth: root.width / 3.5
            Layout.preferredHeight: testRect.width
            radius: testRect.width / 2
        }

        Item {
            id: rightContainer
            Layout.fillHeight: true
            Layout.fillWidth: true
            ColumnLayout {
                anchors.fill: parent
                spacing: 40
                Text {
                    id: titleText
                    text: media.name
                    font.pointSize: 18
                    color: "white"
                }
                Row {
                    Layout.fillWidth: true
                    Layout.preferredHeight: albumText.implicitHeight + 10
                    spacing: 20
                    Text {
                        id: albumText
                        text: "专辑:" + media.album.name
                        color: "white"
                        elide: Text.ElideRight
                        width: Math.min(albumText.implicitWidth,
                                        parent.width / 2)
                    }
                    Text {
                        id: singerText
                        color: "white"
                        elide: Text.ElideRight
                        text: {
                            let result = ""
                            for (var i = 0; i < media.artists.length; i++) {
                                let delimiter = i == 0 ? '' : '/'
                                let artist = media.artists[i].name
                                result += delimiter + artist
                            }
                            return "歌手:" + result
                        }
                        width: Math.min(singerText.implicitWidth,
                                        parent.width / 2)
                    }
                }
                Item {
                    id: spacer
                    Layout.fillWidth: true
                    Layout.preferredHeight: 1
                }
                ListView {
                    id: lyricsListView
                    property bool autoUpdateIndex: true
                    onMovementStarted: autoUpdateIndex = false
                    onMovementEnded: {
                        restoreAutoUpdateTimer.restart()
                    }
                    onContentYChanged: {
                        if (!autoUpdateIndex) {
                            // 计算当前可视区域的中间项
                            var middleY = contentY + height / 2
                            var middleIndex = indexAt(width / 2, middleY)
                            if (middleIndex >= 0
                                    && middleIndex !== currentIndex) {
                                currentIndex = middleIndex
                            }
                        }
                    }
                    Timer {
                        id: restoreAutoUpdateTimer
                        interval: 5000
                        repeat: false
                        onTriggered: lyricsListView.autoUpdateIndex = true
                    }
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model: media.lyrics
                    spacing: 20
                    delegate: LyricItem {
                        onClicked: {
                            lyricsListView.autoUpdateIndex = true
                            restoreAutoUpdateTimer.stop()
                            PlayService.position = this.modelData.end
                        }
                    }

                    Connections {
                        // ms
                        target: PlayService
                        function onPositionChanged(position) {
                            if (lyricsListView.currentIndex === root.media.lyrics.length - 1)
                                return

                            if (lyricsListView.autoUpdateIndex) {
                                lyricsListView.currentIndex
                                        = Utils.findClosestLowerIndexBinarySearch(
                                            root.media.lyrics, position)
                                lyricsListView.positionViewAtIndex(
                                            lyricsListView.currentIndex,
                                            ListView.Center)
                            }
                        }
                    }
                }
            }
        }
    }
}
