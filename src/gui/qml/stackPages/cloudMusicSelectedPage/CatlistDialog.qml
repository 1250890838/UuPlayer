import QtQuick
import QtQuick.Effects
import QtQuick.Controls
import ui_base 1.0
import skins 1.0
import controller

Popup {
    id: root

    property CTab currentItem
    property var map: null

    background: Rectangle {
        id: rectBackground
        color: "transparent"
    }
    width: 1150 / 2
    height: 520 / 2
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
    padding: 0
    onOpened: column.visible = true
    onClosed: column.visible = false

    MultiEffect {
        id: effect
        source: container
        anchors.fill: container
        shadowBlur: 0.1
        shadowColor: "gray"
        shadowEnabled: true
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
        shadowOpacity: 0.75
        shadowScale: 1.0
    }
    Rectangle {
        id: container
        anchors.fill: parent
        radius: 15
        Column {
            id: column
            visible: false
            anchors.fill: parent
            anchors.margins: 20
            spacing: 10
            Row {
                id: row
                spacing: 20
                Repeater {
                    id: repeater1
                    model: {
                        if (root.map === null) {
                            return null;
                        } else {
                            return Object.keys(root.map).length;
                        }
                    }
                    CTab {
                        text: Object.keys(root.map)[modelData]
                        onClicked: {
                            if (root.currentItem !== null) {
                                root.currentItem.isCurrentItem = false;
                            }
                            root.currentItem = this;
                            root.currentItem.isCurrentItem = true;
                            repeater2.model = root.map[(Object.keys(root.map)[modelData])];
                            isCurrentItem = this === root.currentItem;
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
                            return null;
                        } else {
                            return root.map[(Object.keys(root.map)[0])];
                        }
                    }
                    property Item currentItem: null
                    CatlistItem {
                        required property string modelData
                        text: modelData
                        borderWidth: 1
                        width: 80
                        height: 30
                        backgroundColor: "#e7e9eb"
                        borderColor: "#f2f3f4"
                        onClicked: {
                            fetchAttributes.name = modelData;
                            fetchAttributes.offset = 0;
                            hubController.clearPlaylistItems();
                            hubController.fetchPlaylistItems(fetchAttributes.name, fetchAttributes.offset, fetchAttributes.limit);
                            playlistSquareSubpageColumnLayout.currentCatItem = this;
                        }
                    }
                }
            }
        }
    }
}
