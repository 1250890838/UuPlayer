import QtQuick.Controls
import QtQuick

Item {
    id: root
    implicitWidth: row.implicitWidth + 2 * margins
    implicitHeight: row.implicitHeight + 2 * margins
    required property real iconWidth
    required property real iconHeight
    required property url icon
    required property string text

    property color textColor: "black"
    property bool textBold: false
    property real textPointSize: 8
    property int textWeight: Font.Normal
    property color backgroundColor: "transparent"
    property color hoveredBackgroundColor: "transparent"
    property real radius
    property real margins: 0
    property int borderWidth: 0
    property color borderColor: "white"

    signal clicked
    signal pressed
    signal released

    Rectangle {
        id: container
        anchors.fill: parent
        color: mouseArea.containsMouse ? root.hoveredBackgroundColor : root.backgroundColor
        radius: root.radius

        border.width: root.borderWidth
        border.color: root.borderColor
        Row {
            id: row
            spacing: 5
            anchors.centerIn: parent
            Image {
                id: image
                source: root.icon
                width: root.iconWidth
                height: root.iconHeight
                anchors.verticalCenter: parent.verticalCenter
            }
            Text {
                id: text
                anchors.verticalCenter: parent.verticalCenter
                text: root.text
                color: root.textColor
                font {
                    bold: root.textBold
                    pointSize: root.textPointSize
                    weight: root.textWeight
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            root.clicked()
        }
        onPressed: {
            root.pressed()
        }
        onReleased: {
            root.released()
        }
    }
}
