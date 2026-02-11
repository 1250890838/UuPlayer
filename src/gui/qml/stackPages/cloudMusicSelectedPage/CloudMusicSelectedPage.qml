import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ui_base 1.0
import App.Enums 1.0

Page {
    id: root
    topPadding: 15
    bottomPadding: 15
    leftPadding: 10
    rightPadding: 10
    background: Rectangle {
        color: "transparent"
    }
    ColumnLayout {
        anchors.fill: parent
        TabsBar {
            id: tabbar
            Layout.fillWidth: true
        }

        StackView {
            id: stackView
            Layout.fillHeight: true
            Layout.fillWidth: true
            popEnter: null
            popExit: null
            pushEnter: null
            pushExit: null
            replaceEnter: null
            replaceExit: null
            initialItem: SelectiveSubpage {}
        }
    }

    // Component.onCompleted: {
    //   PlaylistsService.getHighqualityPlaylists();
    //}
}
