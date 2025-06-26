import QtQuick 2.15
import QtQuick.Controls 2.15
import service.api 1.0
import components 1.0

Item {
    id: root
    property url albumImagePath
    property bool playing:false

    Rectangle{
        color:"red"
        opacity: 0.5
        anchors.fill: parent
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            //
        }

    }

    RoundedImage{
        id:albumImage
        property int currentRotation:0

        anchors.centerIn:parent
        imageUrl:root.albumImagePath
        width:parent.width/3*2
        height:width
        radius:height/2
        isTopLeftRounded: true
        isTopRightRounded: true
        isBottomLeftRounded: true
        isBottomRightRounded: true
        RotationAnimation on rotation {
            from:albumImage.rotation
            to:360
            duration: 60000
            loops: Animation.Infinite
            running: root.playing
            onStopped:albumImage.currentRotation=albumImage.rotation
        }
    }
    onAlbumImagePathChanged:albumImage.currentRotation=0

}
