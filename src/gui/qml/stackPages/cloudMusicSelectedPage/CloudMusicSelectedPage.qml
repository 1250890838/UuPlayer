import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import service 1.0

Page {
    id: root
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
            initialItem: SelectiveSubpage {
            }
        }
    }

    // Component.onCompleted: {
    //   PlaylistsService.getHighqualityPlaylists();
    //}
}
