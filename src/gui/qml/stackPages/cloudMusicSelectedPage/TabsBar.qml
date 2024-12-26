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
        color: "blue"
    }

    Row {
        id: row
        anchors.fill: parent
        Repeater {
            model: 5
            Item {
                implicitWidth: column.implicitWidth + 20 + 5
                implicitHeight: column.implicitHeight + 2 + 5
                Column {
                    id: column
                    spacing: 5
                    Text {
                        id: text
                        text: tabsBar.texts[modelData]
                    }
                    Rectangle {
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: 20
                        height: 2
                        color: "red"
                    }
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill:parent
                    onClicked: {
                        console.log(`clicked modelData ${modelData} `)
                        if (modelData == 0) {
                            NavigateLogic.switchPage(this, Qt.createComponent("SelectiveSubpage.qml"));
                        } else if (modelData == 1) {
                            NavigateLogic.switchPage(this, Qt.createComponent("PlaylistSquareSubpage.qml"));
                        } else if (modelData == 2) {
                            NavigateLogic.switchPage(this, Qt.createComponent("RankingSubpage.qml"));
                        } else if (modelData == 3) {
                            NavigateLogic.switchPage(this, Qt.createComponent("SingerSubpage.qml"));
                        } else if (modelData == 4) {
                            NavigateLogic.switchPage(this, Qt.createComponent("VipSubpage.qml"));
                        }
                    }
                }
            }
        }
    }
}
