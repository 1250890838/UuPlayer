import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import app

Flickable {
    id: root

    readonly property var hubController: PlaylistHubController

    contentHeight: columnLayout.implicitHeight
    contentWidth: this.width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true

    onContentYChanged: {
        if (root.contentY + root.height >= root.contentHeight) {
            hubController.fetchNextPage()
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
                model: {
                    const groups = Object.keys(hubController.categories)
                    return groups.length > 0 ? hubController.categories[groups[0]].slice(
                                                   0, 6) : []
                }
                delegate: CatlistItem {
                    required property string modelData
                    text: modelData
                    selected: columnLayout.currentCatItem === this
                    width: 65
                    height: 30
                    onClicked: {
                        if (selected)
                            return
                        columnLayout.currentCatItem = this
                        hubController.selectCategory(modelData)
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
                id: playlistRepeater
                model: hubController.items
                delegate: PlaylistItem {
                    implicitWidth: 182
                    implicitHeight: 234
                    onClicked: {
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
        map: hubController.categories
        y: moreCatItem.y + moreCatItem.height + 25
        x: 45
        onCategorySelected: function (name) {
            hubController.selectCategory(name)
        }
    }

    Component.onCompleted: {
        globalScrollBar.currentFlickable = this
        hubController.fetchCategories()
    }
}