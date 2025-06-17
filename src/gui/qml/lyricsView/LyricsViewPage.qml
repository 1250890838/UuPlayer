import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import assets 1.0
import components 1.0

// Lyrics View Page show lyrics
Page {
    id: root
    background: Rectangle {
        gradient: Gradient {
            orientation: Gradient.Vertical
            GradientStop {
                position: 0.0
                color: "#14161e"
            }
            GradientStop {
                position: 1.0
                color: "#3a3e4c"
            }
        }
    }
    IconButton {
        icon: Icons.downIcon
        x: 40
        y: 25
        width: 40
        height: 40
        margins: 10
        hoveredIcon: Icons.downIcon
        radius: 5
        backgroundColor: "#2f3b3b"
        backgroundHoveredColor: "#354040"
        borderColor: "#404b4b"
        borderWidth: 1
        onClicked: function () {
            console.log("down button on lyrics view page clicked!")
            root.state = "closed"
        }
        Component.onCompleted: windowAgent.setHitTestVisible(this)
    }

    IconButton {
        icon: Icons.fullscreenIcon
        x: 95
        y: 25
        width: 40
        height: 40
        margins: 10
        radius: 5
        hoveredIcon: Icons.fullscreenIcon
        backgroundColor: "#2f3b3b"
        backgroundHoveredColor: "#354040"
        borderColor: "#404b4b"
        borderWidth: 1
        onClicked: function () {
            window.showMaximized()
        }
        Component.onCompleted: windowAgent.setHitTestVisible(this)
    }
}
