import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import assets 1.0
import components 1.0

Item {
    id: root
    Pane {
        anchors.fill: parent
        background: Rectangle {
            color: "transparent"
        }
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: forceActiveFocus()
        }
        Column {
            id: rootColumn
            anchors.fill: parent
            spacing: 20
            Row {
                spacing: 15
                Text {
                    id: localMusicText
                    text: qsTr("本地音乐")
                    font.bold: true
                    font.pointSize: 16
                    //       verticalAlignment: Text.AlignBottom
                }
                Text {
                    id: localMusicCountText
                    //height: localMusicText.height
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    text: qsTr("共") + qsTr("首")
                    font.pointSize: 8
                    color: "gray"
                }
            }
            Row {
                id: buttonGroupRow
                spacing: 12
                TextIconButton {
                    id: playAllButton
                    icon: Icons.playIcon
                    iconWidth: 10
                    iconHeight: 12
                    text: qsTr("播放全部")
                    textColor: "white"
                    textPointSize: 10
                    margins: 10
                    radius: 8
                    backgroundColor: "#fc3d49"
                    hoveredBackgroundColor: "#e33552"
                    onPressed: {
                        scale = 0.9
                    }
                    onReleased: {
                        scale = 1
                    }
                }
                IconButton {
                    backgroundColor: "#f0f3f6"
                    backgroundHoveredColor: "#f0f3f6"
                    icon: Icons.refreshIcon
                    hoveredIcon: Icons.refreshIcon
                    radius: 6
                    width: 35
                    height: 35
                    margins: 10
                    onPressed: {
                        scale = 0.9
                    }
                    onReleased: {
                        scale = 1
                    }
                }
                IconButton {
                    radius: 6
                    backgroundColor: "#f0f3f6"
                    backgroundHoveredColor: "#f0f3f6"
                    icon: Icons.moreIcon
                    hoveredIcon: Icons.moreIcon
                    width: 35
                    height: 35
                    margins: 10
                    onPressed: {
                        scale = 0.9
                    }
                    onReleased: {
                        scale = 1
                    }
                }
                SearchBox {
                    id: searchBox
                    focus: false
                    expandedWidth: 175
                    collapsedWidth: 75
                }
            }
        }
    }
}
