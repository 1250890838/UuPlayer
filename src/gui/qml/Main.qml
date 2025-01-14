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
import "stackPages/cloudMusicSelectedPage"
import "titleBar"

Window {
    id: window
    minimumWidth: 1057
    minimumHeight: 752
    visible: false
    color: "#F7F9FC"
    property var commands: []

    Component.onCompleted: {
        windowAgent.setup(window)
        window.visible = true
    }
    WindowAgent {
        id: windowAgent
    }
    title: qsTr("Demo")

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        TitleBar {
            id: titleBar
            Layout.fillWidth: true
        }

        RowLayout {
            spacing: 0
            LeftNavigationPanel {
                id: navigationPanel
                Layout.preferredWidth: 205
                Layout.fillHeight: true
            }

            ColumnLayout {
                id: columnLayout
                Layout.preferredWidth: Rectangle {
                    id: test
                    color: "blue"
                    Layout.preferredWidth: (0.9 * (window.width - navigationPanel.width))
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignRight
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log(test.width)
                            console.log(columnLayout.width)
                        }
                    }
                }
            }


            /*
            ColumnLayout {
                StackView {
                    id: stackView
                    Layout.margins: 25
                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredWidth: (0.9 * (window.width - navigationPanel.width))
                    Layout.fillHeight: true
                    background: Rectangle {
                        color: "#f7f9fc"
                    }
                    popEnter: null
                    popExit: null
                    pushEnter: null
                    pushExit: null
                    replaceEnter: null
                    replaceExit: null
                    initialItem: CloudMusicSelectedPage {}
                }
            }
            */
        }
    }
}
