import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import components 1.0

Rectangle {
    id: root
    required property var modelData
    implicitWidth: 175
    implicitHeight: 235
    signal clicked
    radius: 8
    color: mouseArea.containsMouse ? "#ffffff" : "transparent"

    MultiEffect {
        id: effect
        visible: mouseArea.containsMouse
        source: root
        anchors.fill: root
        shadowBlur: 0.1
        shadowColor: "pink"
        shadowEnabled: true
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
        shadowOpacity: 0.3
        shadowScale: 1.0
    }

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10
        RoundedImage {
            id: coverImage
            width: parent.width
            height: width
            radius: width / 2
            imageUrl: modelData.avatarUrl
            isTopLeftRounded: true
            isTopRightRounded: true
            isBottomLeftRounded: true
            isBottomRightRounded: true
        }
        Text {
            id: nameText
            text: modelData.name
            width: parent.width
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: descText
            elide: Text.ElideRight
            width: parent.width
            text: modelData.desc.length === 0 ? "这个人很懒，什么也没留下" : modelData.desc
            horizontalAlignment: Text.AlignHCenter
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            root.clicked()
        }
    }
}
