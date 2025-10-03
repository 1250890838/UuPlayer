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
        Column {
            id: rootColumn
            anchors.fill: parent
            Row {
                spacing: 15
                Text {
                    id: localMusicText
                    text: qsTr("本地音乐")
                    font.bold: true
                    font.pointSize: 10
                }
                Text {
                    id: localMusicCountText
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("共") + qsTr("首")
                    font.pointSize: 8
                    color: "gray"
                }
            }
            Row {
                id: buttonGroupRow
                TextIconButton {
                    id: playAllButton
                    icon: Icons.playIcon
                    iconWidth: 20
                    iconHeight: 30
                    text: qsTr("播放全部")
                    textColor: "white"
                    textPointSize: 10
                    margins: 4
                    backgroundColor: "#fc3d49"
                }
                IconButton {
                    backgroundColor: "#f0f3f6"
                    icon: Icons.refreshIcon
                    hoveredIcon: Icons.refreshIcon
                }
                IconButton {
                    backgroundColor: "#f0f3f6"
                    icon: Icons.moreIcon
                    hoveredIcon: Icons.moreIcon
                }
            }
        }
    }
}
