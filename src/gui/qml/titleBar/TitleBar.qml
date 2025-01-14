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
        padding: 0
        background: Rectangle {
            id: background
            color: "#F7F9FC"
        }
        RowLayout {
            anchors.fill: parent
            spacing: 15
            Rectangle {
                Layout.preferredWidth: 205
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignLeft
                color: Qt.rgba(240 / 255, 243 / 255, 246 / 255, 1.0) //"#F0F3F6"
                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 10
                    Item {
                        id: spacing
                        width: 20
                        height: 1
                    }
                    IconLabel {
                        width: 32
                        height: 32
                        icon: Icons.appIcon
                    }
                    Text {
                        id: title
                        text: "奶龙云音乐"
                        anchors.verticalCenter: parent.verticalCenter
                        font.pointSize: 13.5
                        font.letterSpacing: 2
                    }
                }
            }
            Item {
                id: spring
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            TextIconButton {
                id: loginButton
                icon: Icons.defaultUserProfileIcon
                iconWidth: 32
                iconHeight: 32
                text: "未登录"
                onClicked: {
                    let loginDialog = Qt.createComponent("LoginDialog.qml")
                    let incubator = loginDialog.incubateObject(
                            null, {//    "dim": false
                            }, Qt.Asynchronous)
                    incubator.onStatusChanged = function (status) {
                        if (status == Component.Ready) {
                            let dialog = incubator.object
                        }
                    }
                    console.log("login button clicked!")
                }
                Component.onCompleted: windowAgent.setHitTestVisible(this)
            }

            IconButton {
                id: skinButton
                Layout.alignment: Qt.AlignRight
                icon: Icons.skinIcon
                implicitHeight: 16
                implicitWidth: 16
                hoveredIcon: Icons.skinIcon
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    stackView.replace(
                                Qt.createComponent(
                                    "../stackPages/skinPage/SkinPage.qml"))
                }
                Component.onCompleted: windowAgent.setHitTestVisible(this)
            }

            IconButton {
                id: minButton
                Layout.alignment: Qt.AlignRight
                implicitHeight: 16
                implicitWidth: 16
                icon: Icons.minimizeIcon
                hoveredIcon: Icons.minimizeIcon
                onClicked: window.showMinimized()
                Component.onCompleted: windowAgent.setSystemButton(
                                           WindowAgent.Minimize, minButton)
            }
            IconButton {
                id: maxButton
                property bool checked: false
                Layout.alignment: Qt.AlignRight
                implicitHeight: 16
                implicitWidth: 16
                icon: this.checked ? Icons.normalizeIcon : Icons.maximizeIcon
                hoveredIcon: this.checked ? Icons.normalizeIcon : Icons.maximizeIcon
                Component.onCompleted: windowAgent.setSystemButton(
                                           WindowAgent.Maximize, maxButton)
                onClicked: {
                    if (window.visibility === Window.Maximized) {
                        window.showNormal()
                        this.checked = true
                    } else {
                        window.showMaximized()
                        this.checked = false
                    }
                }
            }
            IconButton {
                id: closeButton
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 42
                implicitHeight: 16
                implicitWidth: 16
                icon: Icons.closeIcon
                hoveredIcon: Icons.closeIcon
                Component.onCompleted: windowAgent.setSystemButton(
                                           WindowAgent.Close, closeButton)
                onClicked: window.close()
            }
        }
    }
    Component.onCompleted: windowAgent.setTitleBar(this)
}
