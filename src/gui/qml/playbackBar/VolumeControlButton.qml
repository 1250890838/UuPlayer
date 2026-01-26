import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import assets 1.0
import controller
import components 1.0

Item {
    id: root
    property size buttonSize: "20x20"
    property size popupSize: Qt.size(20, 133)
    property real previousVolumn: 0
    IconButton {
        id: iconButton
        icon: Boolean(
                  volumnSlider.value) ? Icons.playbackBarVolumnOpenIcon : Icons.playbackBarVolumnCloseIcon
        hoveredIcon: Boolean(
                         volumnSlider.value) ? Icons.playbackBarVolumnOpenIcon : Icons.playbackBarVolumnCloseIcon
        width: buttonSize.width
        height: buttonSize.height
        onContainsMouseChanged: {
            if (iconButton.containsMouse)
                popup.open()
        }
        onClicked: {
            if (PlayService.volumn !== 0) {
                root.previousVolumn = PlayService.volumn
                PlayService.volumn = 0
            } else {
                PlayService.volumn = root.previousVolumn
            }
        }
    }

    Popup {
        id: popup
        y: -popupSize.height - 5
        width: popupSize.width
        height: popupSize.height
        background: Rectangle {
            id: backgroundRect
            color: "transparent"
        }

        contentItem: MultiEffect {
            source: contentRectangle
            shadowEnabled: true
            shadowColor: "#80000000"
            shadowBlur: 0.1
            shadowVerticalOffset: 0
            shadowHorizontalOffset: 0

            Rectangle {
                id: contentRectangle
                visible: true
                color: "white"
                radius: 4
                anchors.fill: parent
                UuSlider {
                    id: volumnSlider
                    anchors.centerIn: parent
                    width: 6
                    height: 85
                    reverse: true
                    showOnHover: false
                    orientation: Qt.Vertical
                    value: PlayService.volumn
                    onMoved: PlayService.volumn = this.value
                }
                Text {
                    id: currVolumnText
                    anchors.top: volumnSlider.bottom
                    anchors.topMargin: 5
                    anchors.horizontalCenter: volumnSlider.horizontalCenter
                    text: Math.round(volumnSlider.value * 100) + "%"
                    font {
                        pointSize: 6
                    }
                }
            }
        }
    }
}
