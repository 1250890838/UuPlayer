import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import controller
import ui_base 1.0

Flickable {
    id: root
    contentHeight: rootLayout.implicitHeight
    contentWidth: width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true
    Component.onCompleted: {
        globalScrollBar.currentFlickable = this;
        homepageController.fetch();
    }
    HomepageController {
        id: homepageController
    }
    ColumnLayout {
        id: rootLayout
        anchors.fill: parent
        spacing: 3
        Item {
            id: bannersConainter
            implicitWidth: parent.width
            implicitHeight: 200
            CarouselView {
                dataModel: homepageController.banners
                anchors.fill: parent
                delegate: Item {
                    id: delegateRoot
                    property var itemModel
                    RoundedImage {
                        imageUrl: itemModel.picUrl
                        anchors.fill: parent
                        isTopLeftRounded: true
                        isTopRightRounded: true
                        isBottomLeftRounded: true
                        isBottomRightRounded: true
                        radius: 12
                    }
                }
            }
        }
        Item {
            implicitHeight: 1
            implicitWidth: 1
        }

        Text {
            text: "推荐歌单 >"
            Layout.leftMargin: 6
            font {
                pointSize: 15
                bold: true
            }
        }

        Item {
            implicitHeight: 1
            implicitWidth: 1
        }

        Item {
            id: playlistsContainer
            implicitHeight: 272
            implicitWidth: parent.width
            CarouselView {
                anchors.fill: parent
                itemsPerPage: parent.width / 192
                dataModel: homepageController.recommendedPlaylists
                delegate: PlaylistItem {
                }
            }
        }

        Component {
            id: rcmdSongItemComponent
            Item {
                id: songItemConainter
                implicitHeight: containerRow.implicitHeight
                implicitWidth: containerRow.implicitWidth
                Row {
                    id: containerRow
                    spacing: 10
                    RoundedImage {
                        id: rcmdSongItemImage
                        imageUrl: modelData.picUrl
                        isTopLeftRounded: true
                        isBottomLeftRounded: true
                        isTopRightRounded: true
                        isBottomRightRounded: true
                        width: 90
                        height: 90
                        radius: 8
                    }
                    Column {
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 5
                        Text {
                            id: songNameText
                            text: modelData.mainTitle
                        }
                        Text {
                            id: artistNameText
                            text: modelData.artistNames?.join(',')
                        }
                    }
                }
            }
        }

        Text {
            text: "今日推荐歌曲 >"
            Layout.leftMargin: 6
            font {
                pointSize: 15
                bold: true
            }
        }

        GridLayout {
            columns: 2
            rows: 3
            columnSpacing: 15
            rowSpacing: 15
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.leftMargin: 6
            Repeater {
                model: homepageController.recommendedStyleSongs
                delegate: rcmdSongItemComponent
            }
        }
    }
}
