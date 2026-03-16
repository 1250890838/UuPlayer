import QtQuick

Item {
    id: root
    signal clicked
    required property string text
    property color backgroundColor: "#F7f9fc"
    property real borderWidth: 1
    Rectangle {
        anchors.fill: parent
        color: root.backgroundColor
        radius: 15
        border {
            width: root.borderWidth
            color: columnLayout.currentCatItem == this ? "red" : "#D3D3D3"
        }
        Text {
            id: text
            anchors.centerIn: parent
            text: root.text
            color: repeater2.currentCatItem == this ? "red" : "black"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: root.clicked()
            cursorShape: Qt.PointingHandCursor
        }
    }
}
