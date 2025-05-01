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
            spacing: 10
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
            }
            Column {
                id: nameColumn
                width: 170
                Text {
                    id: songName
                    text: model.name
                    elide: Qt.ElideRight
                    width: parent.width
                }
                Text {
                    id: artistName
                    elide: Qt.ElideRight
                    width: parent.width
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
