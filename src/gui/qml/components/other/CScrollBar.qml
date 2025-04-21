import QtQuick
import QtQuick.Controls

Item {
    width: 300
    height: 400

    Flickable {
        // ... (Flickable code from above)
    }

    Rectangle {
        id: scrollTrack
        width: 10
        height: flickArea.height
        anchors.right: parent.right
        color: "lightgray"
    }

    Rectangle {
        id: scrollHandle
        width: scrollTrack.width
        height: 50 // Initial handle height
        anchors.right: scrollTrack.right
        color: "gray"
        y: 0 // Initial handle position

        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.YAxis
            drag.minimumY: 0
            drag.maximumY: scrollTrack.height - scrollHandle.height
        }
    }
}
