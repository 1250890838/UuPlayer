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
        spacing: 5
        Item {
            id: bannersConainter
            implicitWidth: parent.width
            implicitHeight: 200
            CarouselView {
                model: homepageController.banners
                anchors.fill: parent
                delegate: Item {
                    id: delegateRoot
                    property var itemData
                    property int itemIndex
                    RoundedImage {
                        imageUrl: itemData.picUrl
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
            implicitHeight: 10
            implicitWidth: 1
        }
        Text {
            text: "推荐歌单 >"
            font {
                pointSize: 16
                bold: true
            }
        }
        Item {
            id: playlistsContainer
            implicitHeight: 350
            implicitWidth: parent.width
            // CarouselView {
            //     anchors.fill: parent
            //     model: homepageController.recommendedPlaylists
            //     delegate: Pl
            // }
        }
    }
}
