pragma Singleton

import QtQuick

Item {
    id: root
    // font color
    property color normalFontColor
    property color strongFontColor

    // left panel
    property color leftNavPaneBackColor
    property color leftNavPanelItemBackColor
    property color leftNavPanelItemBackHoveredColor
    property color leftNavPanelItemBackCheckedColor

    // title bar
    property color titlebarLeftBackColor
    property color titlebarRightBackColor

    // body
    property color bodyBackColor
    state: "default"

    states: [
        State {
            name: "default"
            PropertyChanges {
                target: root
                normalFontColor: "gray"
                strongFontColor: "black"
                leftNavPaneBackColor: "#f0f3f6"
                leftNavPanelItemBackColor: "#f0f3f6"
                leftNavPanelItemBackHoveredColor: "#e4e8ec"
                leftNavPanelItemBackCheckedColor: "#fc3d49"
                titlebarLeftBackColor: "#f0f3f6"
                titlebarRightBackColor: "#f7f9fc"
                bodyBackColor: "#f7f9fc"
            }
        },
        State {
            name: "classic_red"
            PropertyChanges {
                target: root
                normalFontColor: "gray"
                strongFontColor: "black"
                leftNavPaneBackColor: "#f0f3f6"
                leftNavPanelItemBackColor: "#f0f3f6"
                leftNavPanelItemBackHoveredColor: "#e4e8ec"
                leftNavPanelItemBackCheckedColor: "#fc3d49"
                titlebarLeftBackColor: "#ea3e3e"
                titlebarRightBackColor: "#ea3e3e"
                bodyBackColor: "#f7f9fc"
            }
        },
        State {
            name: "cool_black"
            PropertyChanges {
                target: root
                normalFontColor: "gray"
                strongFontColor: "white"
                leftNavPaneBackColor: "#1a1a21"
                leftNavPanelItemBackColor: "#1a1a21"
                leftNavPanelItemBackHoveredColor: "#27272e"
                leftNavPanelItemBackCheckedColor: "#fc3d4c"
                titlebarLeftBackColor: "#1a1a21"
                titlebarRightBackColor: "#13131a"
                bodyBackColor: "#13131a"
            }
        },
        State {
            name: "yellow_green"
            PropertyChanges {
                target: root
                normalFontColor: "gray"
                strongFontColor: "black"
                leftNavPaneBackColor: "#f0f3f6"
                leftNavPanelItemBackColor: "#f0f3f6"
                leftNavPanelItemBackHoveredColor: "#e4e8ec"
                leftNavPanelItemBackCheckedColor: "yellowgreen"
                titlebarLeftBackColor: "yellowgreen"
                titlebarRightBackColor: "yellowgreen"
                bodyBackColor: "#f7f9fc"
            }
        }
    ]
}
