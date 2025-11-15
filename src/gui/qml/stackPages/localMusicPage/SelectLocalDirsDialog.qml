import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts

import components 1.0
import service.api 1.0

Popup {
    id: popup
    modal: true
    focus: true
    padding: 0
    dim: false
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    background: Rectangle {
        color: "transparent"
    }

    MultiEffect {
        id: effect
        source: container
        anchors.fill: container
        shadowBlur: 0.2
        shadowColor: "gray"
        shadowEnabled: true
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
        shadowOpacity: 1
        shadowScale: 1.0
    }
}
