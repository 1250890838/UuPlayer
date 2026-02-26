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
        globalScrollBar.currentFlickable = this
        homepageController.fetch()
    }
    HomepageController {
        id: homepageController
    }
    ColumnLayout {
        id: rootLayout
        anchors.fill: parent
        anchors.margins: 8
        spacing: 5
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
            implicitHeight: 4
            implicitWidth: 1
        }

        Text {
            text: "推荐歌单 >"
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
                delegate: PlaylistItem {}
            }
        }
    }
}
