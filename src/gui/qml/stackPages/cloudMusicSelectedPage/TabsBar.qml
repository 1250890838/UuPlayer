import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import "NavigateLogic.js" as NavigateLogic

Pane {
    id: tabsBar
    implicitHeight: 35
    property Item currentItem
    property var texts: ["精选", "歌单广场", "排行榜", "歌手", "VIP"]

    background: Rectangle {
        color: "transparent"
    }
    Component.onCompleted: {
        tabsBar.currentItem = repeater.itemAt(0);
    }

    Row {
        id: row
        anchors.fill: parent
        spacing:15
        Repeater {
            id: repeater
            model: 5
            Item {
                id: tabItem
                implicitWidth: column.implicitWidth + 5
                implicitHeight: column.implicitHeight + 2 + 5
                Column {
                    id: column
                    spacing: 5
                    Text {
                        id: text
                        text: tabsBar.texts[modelData]
                        font.pointSize:11
                    }
                    Rectangle {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 15
                        height: 3.5
                        color: "red"
                        visible: tabsBar.currentItem == tabItem
                    }
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if (modelData == 0) {
                            NavigateLogic.switchPage(tabItem, Qt.createComponent("SelectiveSubpage.qml"));
                        } else if (modelData == 1) {
                            NavigateLogic.switchPage(tabItem, Qt.createComponent("PlaylistSquareSubpage.qml"));
                        } else if (modelData == 2) {
                            NavigateLogic.switchPage(tabItem, Qt.createComponent("RankingSubpage.qml"));
                        } else if (modelData == 3) {
                            NavigateLogic.switchPage(tabItem, Qt.createComponent("SingerSubpage.qml"));
                        } else if (modelData == 4) {
                            NavigateLogic.switchPage(tabItem, Qt.createComponent("VipSubpage.qml"));
                        }
                    }
                }
            }
        }
    }
}
