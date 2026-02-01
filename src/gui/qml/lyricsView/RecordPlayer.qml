import QtQuick 2.15
import QtQuick.Controls 2.15
import controller
import components 1.0

Item {
    id: root
    property url albumImagePath
    property bool playing: false

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            const gradient = ctx.createRadialGradient(canvas.width / 2,
                                                      canvas.height / 2, 0,
                                                      canvas.width / 2,
                                                      canvas.height / 2,
                                                      canvas.width / 2)
            gradient.addColorStop(0, '#1a1a1a')
            gradient.addColorStop(1, '#0a0a0a')

            ctx.beginPath()
            ctx.arc(canvas.width / 2, canvas.height / 2, canvas.width / 2, 0,
                    Math.PI * 2)
            ctx.fillStyle = gradient
            ctx.fill()
            ctx.beginPath()
            ctx.arc(canvas.width / 2, canvas.height / 2, 20, 0, Math.PI * 2)
            ctx.fillStyle = '#c0c0c0'
            ctx.fill()
            drawGrooves(ctx)
        }

        function drawGrooves(ctx) {
            ctx.strokeStyle = '#12121280'
            ctx.lineWidth = 1.5
            for (var r = 100; r <= canvas.width / 2; r += 5) {
                ctx.beginPath()
                ctx.arc(canvas.width / 2, canvas.height / 2, r, 0, Math.PI * 2)
                ctx.stroke()
            }
        }
    }

    RoundedImage {
        id: albumImage
        property int currentRotation: 0

        anchors.centerIn: parent
        imageUrl: root.albumImagePath
        width: parent.width / 3 * 2
        height: width
        radius: height / 2
        isTopLeftRounded: true
        isTopRightRounded: true
        isBottomLeftRounded: true
        isBottomRightRounded: true
        RotationAnimation on rotation {
            from: albumImage.rotation
            to: 360
            duration: 60000
            loops: Animation.Infinite
            running: root.playing
            onStopped: albumImage.currentRotation = albumImage.rotation
        }
    }
    onAlbumImagePathChanged: albumImage.currentRotation = 0
}
