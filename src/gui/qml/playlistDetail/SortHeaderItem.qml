import QtQuick

Item {
    id: root
    implicitHeight: textTitle.implicitHeight + 12
    implicitWidth: row.implicitWidth
    required property var choiceMap
    required property color backgroundColor
    required property color backgroundHoveredColor
    required property string title
    property color color
    signal choiceChanged(int choice)

    Component.onCompleted: textSortMethod.text = Object.values(
                               root.choiceMap)[0]

    function resetChoice() {
        mouseArea.currChoice = 0
        textSortMethod.text = Object.values(
                    root.choiceMap)[mouseArea.currChoice]
    }

    Rectangle {
        id: container
        anchors.fill: parent
        radius: 4
        color: mouseArea.containsMouse ? root.backgroundHoveredColor : root.backgroundColor
        Row {
            id: row
            spacing: 10
            x: 6
            anchors.verticalCenter: parent.verticalCenter
            Text {
                id: textTitle
                text: root.title
                font.pointSize: 11
            }
            Text {
                id: textSortMethod
                text: Object?.values[0] ?? qsTr("默认")
                font.pointSize: 11
                visible: {
                    if (mouseArea.containsMouse || mouseArea.currChoice != 0)
                        return true
                    return false
                }
            }
        }
        MouseArea {
            id: mouseArea
            property int currChoice: 0
            hoverEnabled: true
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                currChoice += 1
                if (currChoice >= Object.keys(choiceMap).length)
                    currChoice = 0
                choiceChanged(currChoice)
                textSortMethod.text = Object.values(choiceMap)[currChoice]
            }
        }
    }
}
