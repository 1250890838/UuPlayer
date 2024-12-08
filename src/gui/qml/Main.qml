import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import engine 1.0
import assets 1.0
import components 1.0
import "leftNavigationPanel"

Window {
    id:window
    minimumWidth: 1057
    minimumHeight: 752
    visible: true
    title: qsTr("Demo")
    RowLayout {
        anchors.fill:parent
        spacing:0
        LeftNavigationPanel {
            Layout.preferredWidth:205
            Layout.fillHeight:true
        }
        Rectangle{
            color:"red"
            Layout.fillWidth:true
            Layout.fillHeight:true      
        }
    }
}
