import QtQuick 2.15
import QtQuick.Controls

import service.api 1.0
import components 1.0
import assets 1.0


/*
      {IdRole, "id"},       {NameRole, "name"},      {DurationRole, "duration"},
      {AlbumRole, "album"}, {ArtistRole, "artists"}, {ReasonRole, "reason"}};
}
  */ //edeeef
Item {
    id: root
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
            height: parent.height
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
                    }
                }
            }
            Column {
                id: nameColumn
                anchors.verticalCenter: parent.verticalCenter
                width: 170
                Text {
                    id: songName
                    text: model.name
                    elide: Qt.ElideRight
                    width: parent.width
                    font.pointSize: 12
                }
                Text {
                    id: artistName
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

            Item {
                id: spacer
                anchors.verticalCenter: parent.verticalCenter
                width: 60
                height: 1
            }

            Text {
                id: duration
                anchors.verticalCenter: parent.verticalCenter
                text: Utils.millisecondsToTime(model.duration)
            }
        }
    }

    HoverHandler {
        id: hoverHandler
    }
}
