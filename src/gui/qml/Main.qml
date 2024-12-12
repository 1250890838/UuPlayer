import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import engine 1.0
import assets 1.0
import components 1.0
import QWindowKit 1.0
import "leftNavigationPanel"
import "stackPages"
import "titleBar"

Window {
    id: window
    minimumWidth: 1057
    minimumHeight: 752
    visible: false
    Component.onCompleted: {
        windowAgent.setup(window);
        window.visible = true;
    }
    WindowAgent {
        id: windowAgent
    }
    title: qsTr("Demo")

    function switchPage(item: Item, page: var) {
        if (item === navigationPanel.currentItem) {
            console.log("same page!");
            return;
        }
        navigationPanel.currentItem = item;
        stackView.push(page);
    }
    ColumnLayout {
        anchors.fill:parent
        spacing:0
        TitleBar{
            id: titleBar
            Layout.fillWidth:true
        }

        RowLayout {
            spacing: 0
            LeftNavigationPanel {
                id: navigationPanel
                Layout.preferredWidth: 205
                Layout.fillHeight: true
            }
            StackView {
                id: stackView
                Layout.fillWidth: true
                Layout.fillHeight: true
                background: Rectangle {
                    color: "#f7f9fc"
                }
                popEnter: null
                popExit: null
                pushEnter: null
                pushExit: null
                initialItem: CloudMusicSelectedPage {
                }
            }
        }
    }
}
