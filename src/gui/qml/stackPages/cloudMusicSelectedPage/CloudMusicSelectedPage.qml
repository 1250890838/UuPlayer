import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import App.Enums 1.0

Page {
    id: root
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
