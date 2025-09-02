import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import service.api 1.0
import assets 1.0
import components 1.0
import network.errorcode 1.0

Flickable {
    id: root
    required property var detail
    contentHeight: columnLayout.implicitHeight
    contentWidth: parent.width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true
    Component.onCompleted: {
        globalScrollBar.currentFlickable = this
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        Row {
            spacing: 20
            RoundedImage {
                id: coverImage
                radius: 10
                imageUrl: detail.coverUrl
                width: 170
                height: 170
                isTopLeftRounded: true
                isTopRightRounded: true
                isBottomLeftRounded: true
                isBottomRightRounded: true
            }

            Column {
                spacing: 10
                Text {
                    id: name
                    text: detail.name
                    font {
                        bold: true
                        pointSize: 16
                    }
                }
                Text {
                    id: desc
                    width: 548
                    text: detail.desc
                    font.pointSize: 9
                    height: font.pointSize + 2
                    color: "#54534d"
                    wrapMode: Text.WordWrap
                    elide: Text.ElideRight
                }
                Row {
                    height: avatarImage.height
                    RoundedImage {
                        id: avatarImage
                        radius: 12.5
                        imageUrl: detail.creator.avatarUrl
                        width: 25
                        height: 25
                        isTopLeftRounded: true
                        isTopRightRounded: true
                        isBottomLeftRounded: true
                        isBottomRightRounded: true
                    }
                    spacing: 10
                    Text {
                        id: avatarName
                        text: detail.creator.name
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        id: createdTime
                        color: "gray"
                        font.pointSize: 8.5
                        text: Utils.convertMillisecondsToDate(
                                  detail.createTime) + qsTr("创建")
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 1
                    height: 25
                }
                Row {
                    spacing: 10
                    Item {
                        width: 95
                        height: 38
                        TextIconButton {
                            icon: Icons.playIcon
                            anchors.fill: parent
                            iconWidth: 10
                            iconHeight: 10
                            text: "播放全部"
                            textColor: "white"
                            textPointSize: 10
                            textBold: true
                            textWeight: Font.DemiBold
                            radius: 8
                            backgroundColor: "#FC3B5B"
                            hoveredBackgroundColor: "#E33552"

                            function processGetAllSongStatus(status) {
                                if (status === ErrorCode.NoError) {
                                    PlayService.play(
                                                mediaItemsRepeater.mediaIds[0])
                                }
                                for (var i = 1; i < mediaItemsRepeater.mediaIds.length; i++) {
                                    SongService.getSongUrl(
                                                mediaItemsRepeater.mediaIds[i])
                                }
                                SongService.songUrlStatus.disconnect(
                                            processGetAllSongStatus)
                            }

                            onPressed: {
                                scale = 0.9
                            }
                            onReleased: {
                                scale = 1
                                for (var i = 0; i < mediaItemsRepeater.mediaIds.length; i++) {
                                    PlayService.appendMediaId(
                                                mediaItemsRepeater.mediaIds[i])
                                }
                                SongService.getSongUrl(
                                            mediaItemsRepeater.mediaIds[0])
                                SongService.songUrlStatus.connect(
                                            processGetAllSongStatus)
                            }
                        }
                    }
                    Item {
                        width: 80
                        height: 38
                        TextIconButton {
                            icon: Icons.subscribedIcon
                            anchors.fill: parent
                            iconWidth: 16
                            iconHeight: 16
                            text: detail.subscribedCount
                            textColor: "black"
                            textPointSize: 8.5
                            textBold: true
                            textWeight: Font.DemiBold
                            radius: 8
                            backgroundColor: "#eae1e7"
                            hoveredBackgroundColor: "#e2d9df"
                            onPressed: {
                                scale = 0.9
                            }
                            onReleased: {
                                scale = 1
                            }
                        }
                    }
                    Item {
                        width: 80
                        height: 38
                        TextIconButton {
                            icon: Icons.downloadManagerIcon
                            anchors.fill: parent
                            iconWidth: 16
                            iconHeight: 16
                            text: "下载"
                            textColor: "black"
                            textPointSize: 10
                            textBold: true
                            textWeight: Font.DemiBold
                            radius: 8
                            backgroundColor: "#eae1e7"
                            hoveredBackgroundColor: "#e2d9df"
                            onPressed: {
                                scale = 0.9
                            }
                            onReleased: {
                                scale = 1
                            }
                        }
                    }
                }
            }
        }

        Item {
            id: spacerRow2Tabs
            Layout.fillWidth: true
            Layout.preferredHeight: 20
        }

        Row {
            id: tabsRow
            property CTab currentTab: mediasTab //mediasTab
            spacing: 20
            CTab {
                id: mediasTab
                text: "歌曲"
                additionText: mediaItemsRepeater.count
                isCurrentItem: tabsRow.currentTab === mediasTab
                onClicked: {
                    tabsRow.currentTab.isCurrentItem = false
                    tabsRow.currentTab = this
                    tabsRow.currentTab.isCurrentItem = true
                    stackLayout.currentIndex = 0
                }
            }
            CTab {
                id: commentsTab
                text: "评论"
                additionText: commentRepeater.count
                isCurrentItem: tabsRow.currentTab === commentsTab
                onClicked: {
                    tabsRow.currentTab.isCurrentItem = false
                    tabsRow.currentTab = this
                    tabsRow.currentTab.isCurrentItem = true
                    stackLayout.currentIndex = 1
                    PlaylistsService.getPlaylistComments(detail.id)
                }
            }
            CTab {
                id: subscribersTab
                text: "收藏者"
                isCurrentItem: tabsRow.currentTab === subscribersTab
                onClicked: {
                    tabsRow.currentTab.isCurrentItem = false
                    tabsRow.currentTab = this
                    tabsRow.currentTab.isCurrentItem = true
                    stackLayout.currentIndex = 2
                }
            }
        }
        StackLayout {
            id: stackLayout
            Layout.rightMargin: 5
            Layout.leftMargin: 5
            Layout.topMargin: 5
            currentIndex: 0
            Layout.fillWidth: true
            implicitHeight: stackLayout.children[stackLayout.currentIndex].implicitHeight

            Item {
                id: songsPage
                implicitHeight: songsPageColumnLayout.implicitHeight
                implicitWidth: songsPageColumnLayout.implicitWidth
                ColumnLayout {
                    id: songsPageColumnLayout
                    anchors.fill: parent
                    RowLayout {
                        id: headerLayout
                        Text {
                            id: headerDummyItem
                            text: "#"
                            Layout.preferredWidth: 20
                            font.pointSize: 9
                        }
                        Item {
                            id: spacer
                            Layout.preferredWidth: 20
                            Layout.fillHeight: true
                        }
                        Text {
                            id: headerTitleItem
                            text: "标题"
                            Layout.fillWidth: true
                            font.pointSize: 9
                        }
                        Text {
                            id: headerAlbumItem
                            text: "专辑"
                            Layout.fillWidth: true
                            font.pointSize: 9
                        }
                        Text {
                            id: headerDurationItem
                            text: "时长"
                            Layout.preferredWidth: headerDurationItem.implicitWidth + 20
                            font.pointSize: 9
                        }
                    }

                    Repeater {
                        id: mediaItemsRepeater
                        model: detail.mediaItemModel
                        property var mediaIds: []
                        MediaItem {
                            implicitHeight: 55
                            Layout.fillWidth: true
                            Component.onCompleted: {
                                mediaItemsRepeater.mediaIds.push(model.id)
                            }
                        }
                    }
                }
            }
            Item {
                id: commentsPage
                implicitHeight: commentsPageColumn.implicitHeight
                Column {
                    id: commentsPageColumn
                    anchors.fill: parent
                    spacing: 20
                    UTextEdit {
                        id: commentTextEdit
                        radius: 10
                        width: parent.width
                        backgroundColor: "#F0EAEA"
                        height: 85
                        focus: true
                        borderColor: "#efeef0"
                        borderWidth: 1
                        maxCharNum: 140
                    }

                    Row {
                        spacing: 1
                        Text {
                            id: newestCommentsCountText
                            text: "最新评论"
                            font.pointSize: 14
                            font.bold: true
                            anchors.leftMargin: 8
                        }
                        Text {
                            id: newstCommentsCountAdditionText
                            text: commentRepeater.count
                            font.pointSize: 7
                            font.bold: true
                            anchors.top: parent.top
                        }
                    }

                    Repeater {
                        id: commentRepeater
                        delegate: CommentItem {
                            width: commentsPage.width
                        }
                    }
                }
                Connections {
                    id: commentsRequiredConnection
                    target: PlaylistsService
                    function onPlaylistCommentsStatus(code) {
                        if (code === ErrorCode.NoError) {
                            detail = PlaylistsService.getPlaylistItemForId(
                                        detail.id)
                            commentRepeater.model = detail.commentData
                        }
                    }
                }
            }
        }
    }
}
