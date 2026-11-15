import QtQuick

// TextEdit with a background
Item {
    id: root
    property alias radius: container.radius
    property alias backgroundColor: container.color
    required property color borderColor
    required property real borderWidth
    required property int maxCharNum
    property string placeholderText
    property alias textColor: textEdit.color

    Rectangle {
        id: container
        anchors.fill: parent
        border.color: root.borderColor
        border.width: root.borderWidth
        TextEdit {
            id: textEdit
            anchors.margins: 15
            anchors.fill: parent
            wrapMode: TextEdit.WrapAnywhere
            Text {
                id: placeholderText
                text: "写点什么吧"
                font: textEdit.font
                color: "#888888"
                anchors.top: parent.top
                anchors.left: parent.left
                visible: textEdit.text.trim() === ""
            }

            onTextChanged: {
                // querying textEdit.length faster than textEdit.text.length
                // as it doesn't require any copying or conversion of the TextEdit's internal string data
                if (textEdit.length > root.maxCharNum) {
                    text = text.substring(0, root.maxCharNum) // truncate
                }
            }
            Text {
                id: remainNumOfCharText
                text: root.maxCharNum - textEdit.length
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                font.pointSize: textEdit.font.pointSize - 2
                color: "gray"
            }
        }
    }
}
