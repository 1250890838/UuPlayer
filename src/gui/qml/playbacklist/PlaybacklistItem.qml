import QtQuick 2.15
import QtQuick.Controls

import components 1.0


/*
      {IdRole, "id"},       {NameRole, "name"},      {DurationRole, "duration"},
      {AlbumRole, "album"}, {ArtistRole, "artists"}, {ReasonRole, "reason"}};
}
  */ //edeeef
Item {
    id: root
    signal clicked
    Rectangle {
        id: container
        color: mouseArea.containsMouse ? "#edeeef" : "transparent"
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

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
