import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import components 1.0
import assets 1.0
import QWindowKit 1.0

Item {
    id: root
    implicitHeight: 70
    Pane {
        id: container
        anchors.fill: parent
        RowLayout {
            anchors.fill: parent
            spacing: 10
            IconButton {
                id: minButton
                implicitHeight: 30
                implicitWidth: 50
                icon: Icons.test
                hoveredIcon: Icons.test
                onClicked: window.showMinimized()
                Component.onCompleted: windowAgent.setSystemButton(WindowAgent.Minimize, minButton)
            }
            IconButton {
                id: maxButton
                implicitHeight: 30
                implicitWidth: 50
                icon: Icons.test
                hoveredIcon: Icons.test
                Component.onCompleted: windowAgent.setSystemButton(WindowAgent.Maximize, maxButton)
                onClicked: {
                    if (window.visibility === Window.Maximized) {
                        window.showNormal();
                    } else {
                        window.showMaximized();
                    }
                }
            }
            IconButton {
                id: closeButton
                implicitHeight: 30
                implicitWidth: 50
                icon: Icons.test
                hoveredIcon: Icons.test
                Component.onCompleted: windowAgent.setSystemButton(WindowAgent.Close, closeButton)
                onClicked: window.close()
            }
        }
    }
    Component.onCompleted: windowAgent.setTitleBar(this)
}
