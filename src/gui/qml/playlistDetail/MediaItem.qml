import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import controller
import ui_base 1.0
import assets 1.0
import App.Enums 1.0

Item {
    id: root

    enum ShowType {
        ShowIndex,
        ShowIcon,
        ShowWave
    }

    readonly property bool isPlaying: PlayController.isPlaying
    readonly property bool isCurrMedia: PlayController.currMediaItem.id === model.id

    property int showType: {
        if (mouseArea.containsMouse || (isCurrMedia && !isPlaying))
            return MediaItem.ShowIcon
        else if (!mouseArea.containsMouse && (isCurrMedia && isPlaying))
            return MediaItem.ShowWave
        else
            return MediaItem.ShowIndex
    }

    Loader {
        id: effectLoader
        anchors.fill: container
        sourceComponent: effectComponenet
        active: (root.showType === MediaItem.ShowIcon
                 || root.showType === MediaItem.ShowWave)
    }

    Component {
        id: effectComponenet
        MultiEffect {
            id: effect
            visible: true
            source: container
            shadowBlur: 0.01
            shadowColor: "gray"
            shadowEnabled: true
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0
            shadowOpacity: 0.3
            shadowScale: 1.0
            Component.onDestruction: console.log("effect destroyed!!!")
        }
    }

    Rectangle {
        id: container
        anchors.fill: parent
        radius: 8
        color: (root.showType === MediaItem.ShowIcon
                || root.showType === MediaItem.ShowWave) ? "#ffffff" : "transparent"
    }

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        spacing: 10
        Text {
            id: index
            visible: root.showType === MediaItem.ShowIndex
            text: model.index.toString().padStart(2, '0') // 转换为两位数格式
            Layout.preferredWidth: headerDummyItem.width
        }
        Loader {
            id: waveLoader
            active: root.showType === MediaItem.ShowWave
            visible: this.active
            sourceComponent: waveComponent
            Layout.preferredHeight: index.implicitHeight
            Layout.preferredWidth: headerDummyItem.width
        }
        Component {
            id: waveComponent
            AnimatedImage {
                id: waveImage
                source: "qrc:/gui/images/audio_wave.gif"
            }
        }


        /*
        Component {
            id: connectFactory
            Connections {
                id: playSongConnection
                target: NetworkSongService
                property int count: 2
                function onSongUrlStatus(code) {
                    if (code === ErrorCode.NoError) {
                        PlayService.appendMediaId(model.id)
                        PlayService.play(model.id)
                    }
                    count--
                    if (count === 0)
                        playSongConnection.destroy()
                }
                function onSongLyricStatus(code) {
                    if (code === ErrorCode.NoError) {
                        PlayService.currentPlayItemChanged()
                    }
                    count--
                    if (count === 0)
                        playSongConnection.destroy()
                }
            }
        }
        */
        IconButton {
            id: playButton
            visible: root.showType === MediaItem.ShowIcon
            icon: root.isPlaying ? Icons.pauseGrayIcon : Icons.playGrayIcon
            hoveredIcon: Icons.playGrayIcon
            Layout.preferredHeight: index.implicitHeight
            Layout.preferredWidth: headerDummyItem.width
            onClicked: {
                if (PlayController.isPlaying
                        && PlayController.currMediaItem.id === model.id) {
                    PlayController.pause()
                } else {
                    detailsController.fetchMediaUrl(model.id,
                                                    SoundLevel.Standard)
                    detailsController.fetchLyric(model.id)
                }
            }
        }
        Row {
            Layout.preferredWidth: headerTitleItem.width
            spacing: 10
            RoundedImage {
                id: image
                sourceSize: Qt.size(36, 36)
                width: 36
                height: 36
                radius: 5
                imageUrl: model.album.picUrl
                isTopLeftRounded: true
                isTopRightRounded: true
                isBottomLeftRounded: true
                isBottomRightRounded: true
            }
            Column {
                spacing: 5
                width: 2 * (parent.width - image.width) / 3
                Text {
                    id: name
                    width: parent.width
                    elide: Text.ElideRight
                    text: model.name
                    font {
                        pointSize: 8
                    }
                }
                Text {
                    id: artists
                    width: parent.width
                    font {
                        pointSize: 7.5
                    }
                    color: "gray"
                    elide: Text.ElideRight
                    text: model.artists.map(a => a.name).join(' / ')
                }
            }
        }
        Text {
            id: albumName
            Layout.preferredWidth: headerAlbumItem.width
            elide: Text.ElideRight
            wrapMode: Text.NoWrap
            text: model.album.name
            font {
                pointSize: 8
            }
        }
        Text {
            id: duration
            text: Utils.millisecondsToTime(model.duration)
            Layout.preferredWidth: headerDurationItem.width
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        hoverEnabled: true
    }
}
