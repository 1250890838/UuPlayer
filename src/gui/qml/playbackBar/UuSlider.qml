import QtQuick
import QtQuick.Controls.Basic

Slider {
    id: control
    value: 0.5
    padding: 0
    topPadding: 0
    background: Rectangle {
        x: control.leftPadding + handle.width / 2
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: 4
        width: control.availableWidth - handle.width
        height: implicitHeight
        radius: 2
        color: "#dadcdf"

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: "#fc3d4f"
            radius: 2
        }
    }

    handle: Rectangle {
        id: hanele
        visible: control.hovered || control.pressed
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 12
        implicitHeight: 12
        radius: 6
        color: control.pressed ? "#f0f0f0" : "#f6f6f6"
        border.color: "#bdbebf"
    }
}
