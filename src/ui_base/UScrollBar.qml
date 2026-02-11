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
        color: dragArea.containsMouse
               || dragArea.pressed ? handleActiveColor : handleColor
        radius: vertical ? width / 2 : height / 2

        x: vertical ? handleMargin : calcHandlePosition()
        y: vertical ? calcHandlePosition() : handleMargin
        width: vertical ? parent.width - 2 * handleMargin : calcHandleSize()
        height: vertical ? calcHandleSize() : parent.height - 2 * handleMargin

        function scrollRange() {
            if (!currentFlickable)
                return 0
            return vertical ? Math.max(0, currentFlickable.contentHeight
                                       - currentFlickable.height) : Math.max(
                                  0,
                                  currentFlickable.contentWidth - currentFlickable.width)
        }

        function trackRange() {
            return vertical ? Math.max(
                                  0, groove.height - handle.height) : Math.max(
                                  0, groove.width - handle.width)
        }

        function calcHandlePosition() {
            if (!currentFlickable)
                return handleMargin
            const sr = scrollRange()
            const tr = trackRange()
            if (sr <= 0 || tr <= 0)
                return handleMargin

            const pos = vertical ? currentFlickable.contentY : currentFlickable.contentX
            return handleMargin + (pos / sr) * tr
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

            onPositionChanged: {
                if (!pressed || !currentFlickable)
                    return

                const sr = handle.scrollRange()
                const tr = handle.trackRange()
                if (sr <= 0 || tr <= 0)
                    return

                if (vertical) {
                    const handleY = Math.min(
                                      handleMargin + tr, Math.max(
                                          handleMargin,
                                          handle.y + mouseY - handle.height / 2))
                    const ratio = (handleY - handleMargin) / tr
                    currentFlickable.contentY = ratio * sr
                } else {
                    const handleX = Math.min(
                                      handleMargin + tr, Math.max(
                                          handleMargin,
                                          handle.x + mouseX - handle.width / 2))
                    const ratio = (handleX - handleMargin) / tr
                    currentFlickable.contentX = ratio * sr
                }
            }
        }
    }
}
