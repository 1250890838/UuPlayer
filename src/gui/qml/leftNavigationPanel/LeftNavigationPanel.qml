import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import "NavigateLogic.js" as Logic
import "../stackPages"

Item {
    id: root
    property Item currentItem

    Pane {
        id: container
        anchors.fill: parent
        background: Rectangle {
            color: Qt.rgba(240 / 255, 243 / 255, 246 / 255, 1.0) //"#F0F3F6"
        }
        contentItem: ColumnLayout {
            NavigationPanelItem {
                id: personalizedRecommendItem // 为我推荐
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
            }
            NavigationPanelItem {
                id: cloudMusicSelectedItem // 云音乐精选
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: switchPage(this, Qt.createComponent("../stackPages/CloudMusicSelectedPage.qml"))
            }
            NavigationPanelItem {
                id: podcastItem // 播客
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: switchPage(this, Qt.createComponent("../stackPages/PodcastPage.qml"))
            }
            NavigationPanelItem {
                id: privateRoamItem // 私人FM
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //      onClicked: switchPage(this,Qt.createComponent("../stackPages/.qml"))
            }
            NavigationPanelItem {
                id: communityItem // 社区
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: switchPage(this, Qt.createComponent("../stackPages/CommunityPage.qml"))
            }

            NavigationPanelItem {
                id: favorItem // 我喜欢的音乐
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: switchPage(this, Qt.createComponent("../stackPages/FavorMusicPage.qml"))
            }

            NavigationPanelItem {
                id: recentPlayItem // 最近播放
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: switchPage(this, Qt.createComponent("../stackPages/RecentPlayPage.qml"))
            }
            NavigationPanelItem {
                id: myPodcast // 我的播客
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //         onClicked: switchPage(this,Qt.createComponent("../stackPages/PodcastPage.qml"))
            }
            NavigationPanelItem {
                id: myCollection // 我的收藏
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //   onClicked: switchPage(this,Qt.createComponent("../stackPages/PodcastPage.qml"))
            }
            NavigationPanelItem {
                id: download // 下载管理
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: switchPage(this, Qt.createComponent("../stackPages/DownloadManagePage.qml"))
            }
            NavigationPanelItem {
                id: localMusic // 本地音乐
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: switchPage(this, Qt.createComponent("../stackPages/LocalMusicPage.qml"))
            }
            NavigationPanelItem {
                id: musicCloudDisk // 音乐云盘
                Layout.fillWidth: true
                implicitHeight: 50
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //                  onClicked: switchPage(this,Qt.createComponent("../stackPages/PodcastPage.qml"))
            }
        }
    }
}
