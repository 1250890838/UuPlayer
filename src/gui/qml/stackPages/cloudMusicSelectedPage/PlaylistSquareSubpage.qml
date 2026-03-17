import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ui_base 1.0
import controller

Flickable {
    id: root

    property var catMap
    property bool loading: false

    contentHeight: playlistSquareSubpageColumnLayout.implicitHeight + 20
    contentWidth: this.width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true

    onContentYChanged: {
        const threshold = 5;
        if (!loading && root.contentY + root.height >= root.contentHeight - threshold) {
            fetchAttributes.offset += fetchAttributes.limit;
            hubController.fetchPlaylistItems(fetchAttributes.name, fetchAttributes.offset, fetchAttributes.limit);
        }
    }

    QtObject {
        id: fetchAttributes
        property string name
        property int offset: 0
        property int limit: 12
    }

    FeaturedPlaylistHubController {
        id: hubController
    }

    Connections {
        target: hubController
        function onCategoriesChanged() {
            fetchAttributes.name = Object.values(hubController.categories ?? {})[0][0] ?? "清晨";
            hubController.fetchPlaylistItems(fetchAttributes.name, fetchAttributes.offset, fetchAttributes.limit);
        }
    }

    ColumnLayout {
        id: playlistSquareSubpageColumnLayout
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 25
        property Item currentCatItem
        Row {
            id: row
            spacing: 10
            Layout.fillWidth: true
            Repeater {
                id: repeater
                model: Object.values(hubController.categories)[0]?.slice(0, 6)
                delegate: CatlistItem {
                    required property string modelData
                    text: modelData
                    onClicked: {
                        playlistSquareSubpageColumnLayout.currentCatItem = this;
                        fetchAttributes.name = modelData;
                        fetchAttributes.offset = 0;
                        hubController.clearPlaylistItems();
                        hubController.fetchPlaylistItems(fetchAttributes.name, fetchAttributes.offset, fetchAttributes.limit);
                    }
                }
            }
            CatlistItem {
                id: moreCatItem
                text: catlistDialog.opened ? "更多分类 ^" : "更多分类 ˇ"
                onClicked: {
                    catlistDialog.open();
                }
            }
        }

        GridLayout {
            id: gridLayout
            columns: width >= 908 ? 5 : 4
            onWidthChanged: console.log(width)
            columnSpacing: 20
            rowSpacing: 20
            Repeater {
                id: repeater2
                model: hubController.currPlaylistItems
                delegate: PlaylistItem {
                    Layout.fillWidth: true
                    Layout.preferredHeight: width / 0.77
                    Layout.maximumWidth: 212
                    onClicked: {
                        window.mainSwitchPage(playlistDetailPage, {
                                "playlistId": model.id
                            });
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
    }
    Component.onCompleted: {
        globalScrollBar.currentFlickable = this;
        hubController.fetchCategories();
    }
}
