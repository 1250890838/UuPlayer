import QtQuick
import QtQuick.Controls

Popup {
    id: toast
    modal: false
    focus: false
    closePolicy: Popup.NoAutoClose

    property int durationMs: 1800
    property string message: ""

    x: (parent ? (parent.width - width) / 2 : 0)
    y: 16

    background: Rectangle {
        radius: 10
        color: Qt.rgba(0, 0, 0, 0.72)
        border.color: Qt.rgba(1, 1, 1, 0.18)
        border.width: 1
    }

    contentItem: Text {
        text: toast.message
        color: "white"
        font.pixelSize: 14
        padding: 10
    }

    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0
            to: 1
            duration: 120
        }
        NumberAnimation {
            property: "y"
            from: toast.y - 6
            to: toast.y
            duration: 120
        }
    }
    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1
            to: 0
            duration: 120
        }
    }

    Timer {
        id: hideTimer
        interval: toast.durationMs
        repeat: false
        onTriggered: toast.close()
    }

    function show(msg, ms) {
        toast.message = msg;
        if (ms !== undefined)
            toast.durationMs = ms;
        toast.open();
        hideTimer.restart();
    }
}
