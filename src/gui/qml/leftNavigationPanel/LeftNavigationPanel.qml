import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import "NavigateLogic.js" as Logic

Item {
    id: root
    property Item currentItem

    function switchPage(item){
        currentItem=item
    }

    Pane {
        id: container
        anchors.fill: parent
        background: Rectangle {
            color: Qt.rgba(240 / 255, 243 / 255, 246 / 255, 1.0) //"#F0F3F6"
        }
        contentItem: ColumnLayout {
            NavigationPanelItem {
                id:first
                Layout.fillWidth:true
                implicitHeight:50
            }
            NavigationPanelItem {
                id:second
                Layout.fillWidth:true
                implicitHeight:50
            }
            /*
            NavigationPanelItem {
            }
            NavigationPanelItem {
            }
            NavigationPanelItem {
            }
            */
        }
    }
}
