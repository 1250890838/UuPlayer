import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import assets 1.0
import skins 1.0
import "NavigateLogic.js" as Logic
import "../stackPages"

Item {
    id: navigationPanel
    property Item currentItem: cloudMusicSelectedItem
    Pane {
        id: container
        anchors.fill: parent
        padding: 25
        background: Rectangle {
            color: Skins.leftNavPaneBackColor
        }
        contentItem: Column {
            spacing: 5
            NavigationPanelItem {
                id: personalizedRecommendItem // 为我推荐
                height: 33.5
                width: parent.width
                radius: 8
                visible: false //TODO: user mode
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
            }
            NavigationPanelItem {
                id: cloudMusicSelectedItem // 云音乐精选
                height: 33.5
                width: parent.width
                radius: 8
                text: "精选"
                icon: Icons.choiceMusicIcon
                selectedIcon: Icons.choiceMusicSelectedIcon
                colors: ["transparent", Skins.leftNavPanelItemBackColor, "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/cloudMusicSelectedPage/CloudMusicSelectedPage.qml"))
            }
            NavigationPanelItem {
                id: podcastItem // 播客
                radius: 8
                height: 33.5
                width: parent.width
                text: "播客"
                icon: Icons.podcastIcon
                selectedIcon: Icons.podcastSelectedIcon
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/PodcastPage.qml"))
            }
            NavigationPanelItem {
                id: movementItem // 动态
                radius: 8
                text: "动态"
                height: 33.5
                width: parent.width
                icon: Icons.movementIcon
                selectedIcon: Icons.movementSelectedIcon
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/PodcastPage.qml"))
            }
            NavigationPanelItem {
                id: privateRoamItem // 私人FM
                radius: 8
                visible: false
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //      onClicked: switchPage(this,Qt.createComponent("../stackPages/.qml"))
            }
            NavigationPanelItem {
                id: communityItem // 社区
                radius: 8
                visible: false
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/CommunityPage.qml"))
            }

            Rectangle {
                id: spliter
                color: "#E0E0E0"
                width: parent.width - 10 * 2
                height: 1
                anchors.horizontalCenter: parent.horizontalCenter
            }

            NavigationPanelItem {
                id: favorItem // 我喜欢的音乐
                height: 33.5
                width: parent.width
                radius: 8
                text: "我喜欢的音乐"
                icon: Icons.favorMusicIcon
                selectedIcon: Icons.favorMusicSelectedIcon
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/FavorMusicPage.qml"))
            }

            NavigationPanelItem {
                id: recentPlayItem // 最近播放
                height: 33.5
                width: parent.width
                radius: 8
                text: "最近播放"
                icon: Icons.recentPlayIcon
                selectedIcon: Icons.recentPlaySelectedIcon
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/RecentPlayPage.qml"))
            }
            NavigationPanelItem {
                id: myPodcast // 我的播客
                radius: 8
                visible: false
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //         onClicked: switchPage(this,Qt.createComponent("../stackPages/PodcastPage.qml"))
            }
            NavigationPanelItem {
                id: myCollection // 我的收藏
                radius: 8
                visible: false
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //   onClicked: switchPage(this,Qt.createComponent("../stackPages/PodcastPage.qml"))
            }
            NavigationPanelItem {
                id: download // 下载管理
                height: 33.5
                width: parent.width
                radius: 8
                text: "下载管理"
                icon: Icons.downloadManagerIcon
                selectedIcon: Icons.downloadManagerSelectedIcon
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/DownloadManagePage.qml"))
            }
            NavigationPanelItem {
                id: localMusic // 本地音乐
                height: 33.5
                width: parent.width
                radius: 8
                text: "本地音乐"
                icon: Icons.localMusicIcon
                selectedIcon: Icons.localMusicSelectedIcon
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                onClicked: Logic.switchPage(
                               this, Qt.createComponent(
                                   "../stackPages/LocalMusicPage.qml"))
            }
            NavigationPanelItem {
                id: musicCloudDisk // 音乐云盘
                radius: 8
                colors: ["transparent", "#E4E8EC", "#fc3d4a"]
                //                  onClicked: switchPage(this,Qt.createComponent("../stackPages/PodcastPage.qml"))
            }
        }
    }
}
