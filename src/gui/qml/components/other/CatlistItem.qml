import QtQuick

Item {
    id: root
    signal clicked
    required property string text
    property color backgroundColor: "#F7F9FC"
    property bool selected: false
    property real borderWidth: 1
    Rectangle {
        anchors.fill: parent
        color: root.backgroundColor
        radius: 15
        border {
            width: root.borderWidth
            color: root.selected == true ? "red" : "#D3D3D3"
        }
        Text {
            id: text
            anchors.centerIn: parent
            text: root.text
            color: root.selected == true ? "red" : "black"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: root.clicked()
            cursorShape: Qt.PointingHandCursor
        }
    }
}
