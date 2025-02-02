import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import skins 1.0
import "NavigateLogic.js" as NavigateLogic

Pane {
    id: tabsBar
    implicitHeight: 35
    property Item currentItem: selectivePageItem
    property var texts: ["精选", "歌单广场", "排行榜", "歌手", "VIP"]

    Component.onCompleted: currentItem.isCurrentItem = true
    background: Rectangle {
        color: "transparent"
    }

    function changeCurrentItem(item) {
        currentItem.isCurrentItem = false
        currentItem = item
        item.isCurrentItem = true
    }

    Row {
        id: row
        spacing: 15

        CTab {
            id: selectivePageItem
            onClicked: NavigateLogic.switchPage(this, Qt.createComponent(
                                                    "SelectiveSubpage.qml"))
            text: texts[0]
            textColor: Skins.strongFontColor
        }
        CTab {
            id: playlistSquarePageItem
            onClicked: NavigateLogic.switchPage(
                           this,
                           Qt.createComponent("PlaylistSquareSubpage.qml"))
            text: texts[1]
            textColor: Skins.strongFontColor
        }
        CTab {
            id: rankingPageItem
            onClicked: NavigateLogic.switchPage(this, Qt.createComponent(
                                                    "RankingSubpage.qml"))
            text: texts[2]
            textColor: Skins.strongFontColor
        }
        CTab {
            id: singerPageItem
            onClicked: NavigateLogic.switchPage(this, Qt.createComponent(
                                                    "SingerSubpage.qml"))
            text: texts[3]
            textColor: Skins.strongFontColor
        }
        CTab {
            id: vipPageItem
            onClicked: NavigateLogic.switchPage(this, Qt.createComponent(
                                                    "VipSubpage.qml"))
            text: texts[4]
            textColor: Skins.strongFontColor
        }
    }
}
