import QtQuick
import QtQuick.Controls

Item {
    id: root
    property alias text: textId.text
    property alias textColor: textId.color
    property bool isCurrentItem: false
    signal clicked
    implicitWidth: textId.implicitWidth + 5
    implicitHeight: 35
    Column {
        id: column
        spacing: 5
        Text {
            id: textId
            font.pointSize: 11
        }
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 15
            height: 3.5
            color: "red"
            visible: root.isCurrentItem
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            root.clicked()
        }
    }
}
