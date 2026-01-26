import QtQuick 2.15
import QtQuick.Controls

import controller
import components 1.0
import assets 1.0


/*
      {IdRole, "id"},       {NameRole, "name"},      {DurationRole, "duration"},
      {AlbumRole, "album"}, {ArtistRole, "artists"}, {ReasonRole, "reason"}};
}
  */ //edeeef
Item {
    id: root
    property alias isDragging: dragArea.drag.active
    signal dragPointChanged(point p)

    Rectangle {
        id: dragItem
        anchors.fill: parent
        visible: dragArea.drag.active
        Drag.active: dragArea.drag.active
        Drag.hotSpot.x: 80
        Drag.hotSpot.y: 20
        z: 9

        Row {
            anchors.fill: parent
            RoundedImage {
                id: dragItemcoverImage
                isTopLeftRounded: true
                isTopRightRounded: true
                isBottomLeftRounded: true
                isBottomRightRounded: true
                radius: 2
                width: 25
                height: 25
                imageUrl: model.album.picUrl
                anchors.verticalCenter: parent.verticalCenter
            }

            Column {
                width: parent.width - dragItemcoverImage.width
                Text {
                    text: model.name
                    elide: Qt.ElideRight
                    width: parent.width
                    font.pointSize: 12
                }
                Text {
                    elide: Qt.ElideRight
                    width: parent.width
                    font.pointSize: 9
                    color: "gray"
                    text: {
                        let result = ""
                        let ars = model.artists
                        for (let t of ars) {
                            result += t.name
                            result += ' / '
                        }
                        return result.substring(0, result.length - 3)
                    }
                }
            }
        }
    }

    Rectangle {
        id: container
        color: {
            let curColor = (hoverHandler.hovered
                            || PlayService.currentPlayItem.id
                            === model.id) ? "#edeeef" : "transparent"
            return curColor
        }
        anchors.fill: parent
        Row {
            id: row
            width: parent.width
            height: parent.height - 5
            spacing: 10

            Item {
                id: spacer1
                height: 1
                width: 10
            }

            RoundedImage {
                id: coverImage
                isTopLeftRounded: true
                isTopRightRounded: true
                isBottomLeftRounded: true
                isBottomRightRounded: true
                radius: 5
                width: 50
                height: 50
                imageUrl: model.album.picUrl
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    id: overlay
                    radius: coverImage.radius
                    anchors.fill: parent
                    color: "#80000011"
                    visible: onCoverImage.visible
                }

                Image {
                    id: onCoverImage
                    source: (PlayService.currentPlayItem.id === model.id
                             && PlayService.playing) ? Icons.pauseIcon : Icons.playIcon
                    width: 15
                    height: 15
                    anchors.centerIn: parent
                    visible: {
                        if (PlayService.currentPlayItem.id === model.id)
                            return true
                        if (hoverHandler.hovered)
                            return true
                        return false
                    }
                }

                MouseArea {
                    id: imageMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if (PlayService.playing
                                && PlayService.currentPlayItem.id === model.id) {
                            PlayService.pause()
                        } else {
                            PlayService.play(model.id)
                        }
                        console.log(dragItem)
                        console.log(dragItem.parent)
                    }
                }
            }
            Column {
                id: nameColumn
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - spacer1.width - coverImage.width
                       - duration.width - 3 * row.spacing
                Text {
                    id: songName
                    text: model.name
                    elide: Qt.ElideRight
                    width: parent.width
                    font.pointSize: 12
                    anchors.left: parent.left
                }
                Text {
                    id: artistName
                    elide: Qt.ElideRight
                    width: parent.width
                    font.pointSize: 9
                    color: "gray"
                    anchors.left: parent.left
                    text: {
                        let result = ""
                        let ars = model.artists
                        for (let t of ars) {
                            result += t.name
                            result += ' / '
                        }
                        return result.substring(0, result.length - 3)
                    }
                }
            }

            Text {
                id: duration
                anchors.verticalCenter: parent.verticalCenter
                text: Utils.millisecondsToTime(model.duration)
                width: implicitWidth + 8
                horizontalAlignment: Qt.AlignLeft
            }
        }

        Rectangle {
            id: dropIndicator
            color: "#3498db"
            DropArea {
                height: 2
                width: parent.width - 20
                anchors.horizontalCenter: parent.horizontalCenter
                visible: repeater.isOneDragging
                y: 0
                z: 3 // Above list items
            }
        }
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: dragItem
        propagateComposedEvents: true

        onPositionChanged: mouse => {
                               root.dragPointChanged(Qt.point(mouse.x, mouse.y))
                           }

        onReleased: {
            dragItem.x = 0
            dragItem.y = 0
        }
    }

    HoverHandler {
        id: hoverHandler
    }
}
