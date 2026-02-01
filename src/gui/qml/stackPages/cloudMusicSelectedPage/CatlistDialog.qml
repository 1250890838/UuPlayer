import QtQuick
import QtQuick.Effects
import QtQuick.Controls
import components 1.0
import skins 1.0
import controller

Popup {
    id: root
    background: Rectangle {
        id: rectBackground
        radius: 15
        color: "#ffffff"
    }
    width: 1150 / 2
    height: 520 / 2
    property var map: null
    enter: Transition {
        NumberAnimation {
            property: "width"
            from: 0
            to: 1150 / 2
            duration: 80
        }
        NumberAnimation {
            property: "height"
            from: 0
            to: 520 / 2
            duration: 80
        }
    }
    padding: 20
    onOpened: column.visible = true
    onClosed: column.visible = false
    property CTab currentItem

    Column {
        id: column
        visible: false
        anchors.fill: parent
        spacing: 10
        Row {
            id: row
            spacing: 20
            Repeater {
                id: repeater1
                model: {
                    if (root.map === null) {
                        return null
                    } else {
                        return Object.keys(root.map).length
                    }
                }
                CTab {
                    text: Object.keys(root.map)[modelData]
                    onClicked: {
                        if (root.currentItem !== null) {
                            root.currentItem.isCurrentItem = false
                        }
                        root.currentItem = this
                        root.currentItem.isCurrentItem = true

                        repeater2.model = root.map[(Object.keys(
                                                        root.map)[modelData])]
                        isCurrentItem = this === root.currentItem
                    }
                }
            }
        }

        Grid {
            id: grid
            spacing: 12
            columns: 6
            width: parent.width
            Repeater {
                id: repeater2
                model: {
                    if (root.map == null) {
                        return null
                    } else {
                        return root.map[(Object.keys(root.map)[0])]
                    }
                }
                CatlistItem {
                    required property string modelData
                    text: modelData
                    borderWidth: 0
                    width: 80
                    height: 30
                    onClicked: {
                        fetchAttributes.name = modelData
                        fetchAttributes.offset = 0
                        FeaturedPlaylistHubController.fetchPlaylistItems(
                                    fetchAttributes.name,
                                    fetchAttributes.offset,
                                    fetchAttributes.limit)
                    }
                }
            }
        }
    }
}
