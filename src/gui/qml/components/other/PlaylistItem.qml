import QtQuick.Controls
import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    id: root
    signal clicked
    required property var model
    function formatCount(count) {
        if (count >= 1000 && count <= 9999) {
            return (count / 1000).toFixed(1) + "千"
        } else if (count >= 10000) {
            return (count / 10000).toFixed(1) + "万"
        } else {
            return count
        }
    }
    Rectangle {
        id: container
        anchors.fill: parent
        radius: 25
        color: "transparent"

        RoundedImage {
            id: image
            radius: 10
            isTopLeftRounded: true
            isTopRightRounded: true
            imageUrl: model.coverUrl
            width: parent.width
            height: parent.height - 55
            Text {
                id: imageText
                color: "white"
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 10
                anchors.topMargin: 10
                text: root.formatCount(model.playCount)
                font.bold: true
                font.pointSize: 10
            }
        }

        RoundedRectangle {
            id: descRect
            width: parent.width
            height: mouseArea.containsMouse ? parent.height * 0.4 + 55 : 55
            radius: 10
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#f97794"
                }
                GradientStop {
                    position: 1.0
                    color: "#623aa2"
                }
            }
            x: 0
            y: mouseArea.containsMouse ? image.height - parent.height * 0.4 : image.height
            isBottomLeftRounded: true
            isBottomRightRounded: true
            Label {
                id: desc
                color: "white"
                font.pointSize: 10.5
                height: 55
                width: parent.width
                padding: 7
                text: root.model.name
                wrapMode: Text.WordWrap
                elide: Qt.ElideRight
                maximumLineCount: 2
            }

            Column {
                spacing: 10
                anchors.top: desc.bottom
                anchors.topMargin: 10
                visible: mouseArea.containsMouse
                Repeater {
                    id: repeater
                    model: root.model.tracks.count >= 3 ? 3 : root.model.tracks.count
                    Label {
                        leftPadding: 7
                        rightPadding: 7
                        elide: Qt.ElideRight
                        text: {
                            console.log(root.model.tracks.itemAt(
                                            modelData).name)
                            let a = (modelData + 1) + " " + root.model.tracks.itemAt(
                                    modelData).name
                            return a
                        }
                        width: desc.width
                        color: "white"
                        font.pointSize: 8.5
                    }
                }
            }

            Behavior on y {
                NumberAnimation {
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
            Behavior on height {
                NumberAnimation {
                    duration: 200
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.clicked()
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
    }
}
