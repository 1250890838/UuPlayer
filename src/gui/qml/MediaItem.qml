import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import components 1.0

Item {
    implicitHeight: 60
    Rectangle {
        anchors.fill: parent
        radius: 8
        color: "transparent"
        RowLayout {
            id: rowLayout
            anchors.fill: parent
            Text {
                id: index
                text: model.index
                Layout.preferredWidth: headerDummyItem.width
            }
            Item {
                id: spacer
                Layout.preferredWidth: 20
                Layout.fillHeight: true
            }
            Row {
                Layout.preferredWidth: headerTitleItem.width
                spacing: 10
                RoundedImage {
                    id: image
                    width: 36
                    height: 36
                    radius: 5
                    imageUrl: model.album.picUrl
                    isTopLeftRounded: true
                    isTopRightRounded: true
                    isBottomLeftRounded: true
                    isBottomRightRounded: true
                }
                Column {
                    Text {
                        id: name
                        text: model.name
                        font {
                            pointSize: 8
                        }
                    }
                    Text {
                        id: artists
                        font {
                            pointSize: 7.5
                        }
                        color: "gray"
                        text: {
                            let result = ""
                            let ars = model.artists
                            let test = model.album
                            for (let t of ars) {
                                result += t.name
                                result += ' / '
                            }
                            return result.substring(0, result.length - 3)
                        }
                    }
                }
            }
            Text {
                id: albumName
                Layout.preferredWidth: headerAlbumItem.width
                text: model.album.name
                font {
                    pointSize: 8
                }
            }
            Text {
                id: duration
                text: Utils.millisecondsToTime(model.duration)
                Layout.preferredWidth: headerDurationItem.width
            }
        }
    }
}
