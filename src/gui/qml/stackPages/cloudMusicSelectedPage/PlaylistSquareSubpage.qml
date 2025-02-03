import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import service 1.0

Flickable {
    id: root
    property var catMap
    contentHeight: columnLayout.implicitHeight
    contentWidth: this.width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AsNeeded
    }

    onContentYChanged: {
        if (root.contentY + root.height >= root.contentHeight) {
            PlaylistsService.getSelectivePlaylists()
        }
    }

    Connections {
        target: PlaylistsService
        ignoreUnknownSignals: true
        function onPlaylistsCatlist(map) {
            root.catMap = map
            repeater.model = map[(Object.keys(map)[0])].slice(0, 6)
            PlaylistsService.setCurrCat(map[(Object.keys(map)[0])][0])
            PlaylistsService.setCurrLimit(12)
            PlaylistsService.setCurrOffset(0)
            PlaylistsService.getSelectivePlaylists()
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
                delegate: CatlistItem {
                    required property string modelData
                    text: modelData
                    selected: columnLayout.currentCatItem === this
                    width: 65
                    height: 30
                    onClicked: {
                        columnLayout.currentCatItem = this
                        PlaylistsService.setCurrOffset(0)
                        PlaylistsService.setCurrCat(this.text)
                        PlaylistsService.getSelectivePlaylists()
                    }
                }
            }
            CatlistItem {
                id: moreCatItem
                text: "更多分类 ˇ"
                width: 60
                height: 30
                onClicked: {
                    catlistDialog.map = root.catMap
                    catlistDialog.open()
                    moreCatItem.text = "更多分类 ^"
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
                model: PlaylistsService.selectivePlaylists
                delegate: PlaylistItem {
                    implicitWidth: 182
                    implicitHeight: 234
                }
            }
        }
    }

    CatlistDialog {
        id: catlistDialog
        y: moreCatItem.y + moreCatItem.height + 25
        x: 45
        onClosed: moreCatItem.text = "更多分类 ˇ"
    }
    Component.onCompleted: {
        PlaylistsService.getPlaylistsCatlist()
        console.log(root.width)
    }
}
