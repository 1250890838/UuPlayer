import QtQuick
import QtQuick.Controls
import assets 1.0

FocusScope {
    id: root
    required property int expandedWidth
    required property int collapsedWidth
    property string expandedPlaceholderText: qsTr("搜索本地音乐")
    property string collapsedPlaceholderText: qsTr("搜索")
    implicitWidth: 72
    implicitHeight: 30
    transitions: [
        Transition {
            SequentialAnimation {
                NumberAnimation {
                    properties: "width"
                    easing.type: Easing.InOutQuad
                    duration: 300
                }
                ScriptAction {
                    script: root.changePlaceHolderTextInTextInput()
                }
            }
        }
    ]
    states: [
        State {
            name: "collapsed"
            when: !textInput.activeFocus
            PropertyChanges {
                root.width: root.collapsedWidth
            }
        },
        State {
            name: "expanded"
            when: textInput.activeFocus
            PropertyChanges {
                root.width: root.expandedWidth
            }
        }
    ]
    function changePlaceHolderTextInTextInput() {
        textInput.placeholderText = root.state
                === "expanded" ? root.expandedPlaceholderText : root.collapsedPlaceholderText
    }

    Rectangle {
        id: container
        anchors.fill: parent
        border.width: 1
        border.color: "lightgray"
        radius: height / 2
        color: "white"
        Row {
            id: row
            anchors.fill: parent
            anchors.leftMargin: 15
            Image {
                id: searchImage
                anchors.verticalCenter: parent.verticalCenter
                source: Icons.searchIcon
                width: 15
                height: 15
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: textInput.forceActiveFocus()
                }
            }
            TextField {
                id: textInput
                anchors.verticalCenter: parent.verticalCenter
                focus: true
                placeholderText: root.state === "expanded" ? root.expandedPlaceholderText : root.collapsedPlaceholderText
                background: Rectangle {
                    color: "transparent"
                    border.width: 0
                }
            }
        }
    }
}
