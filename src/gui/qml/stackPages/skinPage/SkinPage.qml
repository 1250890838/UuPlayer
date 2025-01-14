import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root
    ColumnLayout {
        anchors.fill: parent
        spacing: 25

        Text {
            id: title
            text: "个性皮肤"
            font.pointSize: 16
            Layout.alignment: Qt.AlignLeading
        }

        RowLayout {
            Layout.alignment: Qt.AlignTop
            spacing: 20
            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.5
                skinText: "默认"
                skinColor: "#FFFFFF"
            }

            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.5
                skinText: "经典红"
                skinColor: "#FF3A3A"
            }

            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.5
                skinText: "酷炫黑"
                skinColor: "#1A1A23"
            }

            SkinItem {
                Layout.fillWidth: true
                Layout.preferredHeight: this.width * 0.5
                skinText: "黄绿色"
                skinColor: "yellowgreen"
            }
        }
    }
}
