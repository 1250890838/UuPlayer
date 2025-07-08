import QtQuick
import QtQuick.Controls

Item {
    id: root
    property alias text: textId.text
    property alias additionText: additionTextId.text
    property alias textColor: textId.color
    property bool isCurrentItem: false
    signal clicked
    implicitWidth: textId.implicitWidth + 5
    implicitHeight: 35

    Text {
        id: additionTextId
        font.bold: isCurrentItem
        font.pointSize: textId.font.pointSize - 4
        anchors.left: column.right
        anchors.leftMargin: 2
    }

    Column {
        id: column
        spacing: 5
        Row {
            spacing: 3
            Text {
                id: textId
                font.bold: isCurrentItem
                font.pointSize: isCurrentItem ? 11 : 10.7
                color: isCurrentItem ? "black" : "gray"
            }
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
