import QtQuick 2.15
import components 1.0
import assets 1.0

Item {
    id: root
    implicitWidth: lyricsListView.width
    implicitHeight: Math.max(lyricText.implicitHeight, resumeButton.height)
    required property var modelData
    required property int index
    signal clicked
    Text {
        id: lyricText
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: lyricsListView.currentIndex === index ? 16 : 15
        font.bold: lyricsListView.currentIndex === index ? true : false
        width: lyricsListView.width
        height: parent.height
        color: "white"
        text: modelData.lyric
        elide: Text.ElideRight
        property int distance: Math.abs(index - lyricsListView.currentIndex)
        opacity: 1.0 - Math.min(distance * 0.35, 0.9)
    }

    TextIconButton {
        id: resumeButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: Utils.millisecondsToTime(modelData.end)
        icon: Icons.playGrayIcon
        iconWidth: 8
        iconHeight: 8
        implicitWidth: 60
        implicitHeight: 20
        textColor: "white"
        borderColor: "gray"
        radius: 4
        borderWidth: 1
        visible: !lyricsListView.autoUpdateIndex
                 && lyricsListView.currentIndex === index
        onClicked: {
            root.clicked()
        }
    }
}
