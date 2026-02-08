import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import controller
import assets 1.0
import components 1.0
import App.Enums 1.0

Flickable {
    id: root
    required property var playlistId

    contentHeight: columnLayout.implicitHeight
    contentWidth: width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true

    Component.onCompleted: {
        globalScrollBar.currentFlickable = this
        detailsController.fetchDetail(root.playlistId)
        detailsController.fetchComments(root.playlistId,
                                        detailsController.offset,
                                        detailsController.limit)
        detailsController.fetchSubscribers(root.playlistId)
    }

    PlaylistDetailsController {
        id: detailsController
        property int offset: 0
        readonly property int limit: 10
        onCommentsChanged: {
            offset += limit
        }
        onCoverUrlChanged: {
            ThemeManager.applyThemeFromUrl(detailsController.coverUrl)
        }
    }
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.margins: 20
        Row {
            spacing: 20
            RoundedImage {
                id: coverImage
                radius: 10
                imageUrl: detailsController.coverUrl
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
                    text: detailsController.name
                    font {
                        bold: true
                        pointSize: 16
                    }
                }
                Text {
                    id: desc
                    width: 548
                    text: detailsController.desc
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
                        imageUrl: detailsController.creatorCoverUrl
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
                        text: detailsController.creatorName
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        id: createdTime
                        color: "gray"
                        font.pointSize: 8.5
                        text: Utils.convertMillisecondsToDate(
                                  detailsController.createTime) + qsTr("创建")
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
                                    PlayController.play(
                                                mediaItemsRepeater.mediaIds[0])
                                }
                                for (var i = 1; i < mediaItemsRepeater.mediaIds.length; i++) {
                                    NetworkSongService.getSongUrl(
                                                mediaItemsRepeater.mediaIds[i])
                                }
                                NetworkSongService.songUrlStatus.disconnect(
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
                                NetworkSongService.getSongUrl(
                                            mediaItemsRepeater.mediaIds[0])
                                NetworkSongService.songUrlStatus.connect(
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
                            text: detailsController.subscribedCount
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
                }
            }
            CTab {
                id: subscribersTab
                text: "收藏者"
                additionText: subscriberRepeater.count
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
                        spacing: 10
                        Layout.leftMargin: 25
                        Layout.rightMargin: 25
                        Text {
                            id: headerDummyItem
                            text: "#"
                            Layout.preferredWidth: headerDummyItem.implicitWidth + 8
                            font.pointSize: 9
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
                        model: detailsController.medias
                        property var mediaIds: []
                        delegate: MediaItem {
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
                        model: detailsController.comments
                        delegate: CommentItem {
                            width: commentsPage.width
                        }
                    }
                }
                //                Connections {
                //                    id: commentsRequiredConnection
                //                    target: PlaylistsService
                //                    function onPlaylistCommentsStatus(code) {
                //                        if (code === ErrorCode.NoError) {
                //                            detail = PlaylistsService.getPlaylistItemForId(
                //                                        detail.id)
                //                            commentRepeater.model = detail.commentData
                //                        }
                //                    }
                //                }
            }
            Item {
                id: subscribersPage
                implicitWidth: parent.width
                implicitHeight: subscribersFlow.implicitHeight
                Flow {
                    id: subscribersFlow
                    width: parent.width
                    spacing: 20
                    Repeater {
                        id: subscriberRepeater
                        model: detailsController.subscribers
                        SubscriberItem {}
                    }
                }
                //                Connections {
                //                    id: subscribersRequiredConnection
                //                    target: PlaylistsService
                //                    function onPlaylistSubscribersStatus(code) {
                //                        if (code === ErrorCode.NoError) {
                //                            detail = PlaylistsService.getPlaylistItemForId(
                //                                        detail.id)
                //                            subscriberRepeater.model = detail.subscribers
                //                        }
                //                    }
                //                }
            }
        }
    }
}
