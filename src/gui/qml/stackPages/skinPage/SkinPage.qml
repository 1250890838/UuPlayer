import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import skins 1.0

Page {
    id: root
    background: Rectangle {
        color: "transparent"
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 25

        Text {
            id: title
            text: "个性皮肤"
            font.pointSize: 16
            font.bold: true
            Layout.alignment: Qt.AlignLeading
        }

        RowLayout {
            Layout.alignment: Qt.AlignTop
            spacing: 20
            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.72
                skinText: "默认"
                skinColor: "#FFFFFF"
                onClicked: Skins.state = "default"
            }

            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.72
                skinText: "经典红"
                skinColor: "#FF3A3A"
                onClicked: Skins.state = "classic_red"
            }

            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.72
                skinText: "酷炫黑"
                skinColor: "#1A1A23"
                onClicked: Skins.state = "cool_black"
            }

            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.72
                skinText: "黄绿色"
                skinColor: "yellowgreen"
                onClicked: Skins.state = "yellow_green"
            }
        }
    }
}
