import QtQuick
import QtQuick.Controls.Basic

Slider {
    id: control
    value: 0.5
    padding: 0
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    orientation: Qt.Horizontal
    property bool showOnHover: true
    property bool reverse: false

    background: Rectangle {
        x: {
            if (control.orientation == Qt.Horizontal)
                return control.leftPadding + handle.width / 2
            else
                return control.leftPadding + control.availableWidth / 2 - width / 2
        }
        y: {
            if (control.orientation == Qt.Horizontal)
                return control.topPadding + control.availableHeight / 2 - height / 2
            else
                return control.topPadding + handle.height / 2
        }
        width: {
            if (control.orientation == Qt.Horizontal) {
                return control.availableWidth - handle.width
            } else
                return 4
        }
        height: {
            if (control.orientation == Qt.Horizontal)
                return 4
            else
                return control.availableHeight - handle.height
        }
        radius: 2
        color: control.reverse ? "#fc3d4f" : "#dadcdf"

        Rectangle {
            width: {
                if (control.orientation == Qt.Horizontal)
                    control.visualPosition * parent.width
                else
                    return parent.width
            }
            height: {
                if (control.orientation == Qt.Horizontal)
                    return parent.height
                else
                    return control.visualPosition * parent.height
            }
            color: control.reverse ? "#dadcdf" : "#fc3d4f"
            radius: 2
        }
    }

    handle: Rectangle {
        id: handle
        visible: {
            if (control.showOnHover)
                return control.hovered || control.pressed
            else
                return true
        }
        x: {
            if (control.orientation == Qt.Horizontal)
                return control.leftPadding + control.visualPosition
                        * (control.availableWidth - width)
            else
                return control.leftPadding + control.availableWidth / 2 - width / 2
        }
        y: {
            if (control.orientation == Qt.Horizontal)
                return control.topPadding + control.availableHeight / 2 - height / 2
            else
                return control.topPadding + control.visualPosition
                        * (control.availableHeight - height)
        }
        implicitWidth: 12
        implicitHeight: 12
        radius: 6
        color: control.pressed ? "#f0f0f0" : "#f6f6f6"
        border.color: "#bdbebf"
    }
}
