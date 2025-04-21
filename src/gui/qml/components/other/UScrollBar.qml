import QtQuick

Item {
    id: root

    property Flickable currentFlickable: null
    property color handleColor: "#e2e5e9"
    property color handleActiveColor: "#c3c8cf"
    property color grooveColor: "transparent"
    property real handleMargin: 2
    property bool vertical: true

    visible: currentFlickable
             && (vertical ? currentFlickable.contentHeight
                            > currentFlickable.height : currentFlickable.contentWidth
                            > currentFlickable.width)

    Rectangle {
        id: groove
        anchors.fill: parent
        color: grooveColor
        radius: vertical ? width / 2 : height / 2
    }

    Rectangle {
        id: handle
        color: dragArea.containsMouse ? handleActiveColor : handleColor
        radius: vertical ? width / 2 : height / 2

        x: vertical ? handleMargin : calcHandlePosition()
        y: vertical ? calcHandlePosition() : handleMargin
        width: vertical ? parent.width - 2 * handleMargin : calcHandleSize()
        height: vertical ? calcHandleSize() : parent.height - 2 * handleMargin

        function calcHandlePosition() {
            if (!currentFlickable)
                return 0
            if (vertical) {
                return (currentFlickable.contentY / (currentFlickable.contentHeight
                                                     - currentFlickable.height))
                        * (groove.height - handle.height)
            }
            return (currentFlickable.contentX / (currentFlickable.contentWidth
                                                 - currentFlickable.width))
                    * (groove.width - handle.width)
        }

        function calcHandleSize() {
            if (!currentFlickable)
                return 0
            if (vertical) {
                return Math.max(
                            20,
                            (currentFlickable.height
                             / currentFlickable.contentHeight) * groove.height)
            }
            return Math.max(
                        20,
                        (currentFlickable.width / currentFlickable.contentWidth) * groove.width)
        }

        MouseArea {
            id: dragArea
            anchors.fill: parent
            hoverEnabled: true
            preventStealing: true
            drag.target: parent
            drag.axis: vertical ? Drag.YAxis : Drag.XAxis
            drag.minimumX: vertical ? handle.x : handleMargin
            drag.maximumX: vertical ? handle.x : groove.width - handle.width - handleMargin
            drag.minimumY: vertical ? handleMargin : handle.y
            drag.maximumY: vertical ? groove.height - handle.height - handleMargin : handle.y

            onPositionChanged: {
                if (vertical) {
                    currentFlickable.contentY = (handle.y / (groove.height - handle.height))
                            * (currentFlickable.contentHeight - currentFlickable.height)
                } else {
                    currentFlickable.contentX = (handle.x / (groove.width - handle.width))
                            * (currentFlickable.contentWidth - currentFlickable.width)
                }
            }
        }
    }

    Connections {
        target: currentFlickable
        function onContentYChanged() {
            if (vertical)
                handle.y = Qt.binding(() => handle.calcHandlePosition())
        }
        function onContentXChanged() {
            if (!vertical)
                handle.x = Qt.binding(() => handle.calcHandlePosition())
        }
    }
}
