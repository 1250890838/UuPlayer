import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import controller

Flickable {
    id: root
    property var catMap

    QtObject {
        id: fetchAttributes
        property string name
        property int offset: 0
        property int limit: 8
    }

    Connections {
        target: FeaturedPlaylistHubController
        function onCategoriesChanged() {
            fetchAttributes.name = FeaturedPlaylistHubController.categories[(Object.keys(
                                                                                 map)[0])][0]
            FeaturedPlaylistHubController.fetchPlaylistItems(
                        fetchAttributes.name, fetchAttributes.offset,
                        fetchAttributes.limit)
        }
    }

    contentHeight: columnLayout.implicitHeight
    contentWidth: this.width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true

    onContentYChanged: {
        if (root.contentY + root.height >= root.contentHeight) {
            fetchAttributes.offset += fetchAttributes.limit
            FeaturedPlaylistHubController.fetchPlaylistItems(
                        fetchAttributes.name, fetchAttributes.offset,
                        fetchAttributes.limit)
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 25
        anchors.margins: 10
        property Item currentCatItem
        Row {
            id: row
            spacing: 10
            Repeater {
                id: repeater
                model: FeaturedPlaylistHubController.categories[(Object.keys(
                                                                     FeaturedPlaylistHubController.categories)[0])].slice(
                           0, 6)
                delegate: CatlistItem {
                    required property string modelData
                    text: modelData
                    selected: columnLayout.currentCatItem === this
                    width: 65
                    height: 30
                    onClicked: {
                        columnLayout.currentCatItem = this
                        fetchAttributes.name = modelData
                        FeaturedPlaylistHubController.fetchPlaylistItems(
                                    fetchAttributes.name,
                                    fetchAttributes.offset,
                                    fetchAttributes.limit)
                    }
                }
            }
            CatlistItem {
                id: moreCatItem
                text: catlistDialog.opened ? "更多分类 ^" : "更多分类 ˇ"
                width: 60
                height: 30
                onClicked: {
                    catlistDialog.open()
                }
            }
        }

        GridLayout {
            id: gridLayout
            columns: columnLayout.width / (182 + 20)
            columnSpacing: 20
            rowSpacing: 20
            Repeater {
                id: repeater2
                model: FeaturedPlaylistHubController.currPlaylistItems
                delegate: PlaylistItem {
                    implicitWidth: 182
                    implicitHeight: 234
                    onClicked: {
                        let item = PlaylistsService.currPlaylists.itemAt(
                                model.index)
                        window.mainSwitchPage(playlistDetailPage, {
                                                  "playlistId": model.id
                                              })
                    }
                }
            }
        }
    }

    CatlistDialog {
        id: catlistDialog
        map: FeaturedPlaylistHubController.categories
        y: moreCatItem.y + moreCatItem.height + 25
        x: 45
    }
    Component.onCompleted: {
        globalScrollBar.currentFlickable = this
        FeaturedPlaylistHubController.fetchCategories()
    }
}
