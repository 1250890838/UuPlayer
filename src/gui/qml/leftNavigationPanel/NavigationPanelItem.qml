import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import assets 1.0

Item {
    id: root
    required implicitHeight
    required implicitWidth
    required property var colors:[] // default | hovered | selected
    property alias radius: container.radius
    property alias text: label.text
    //property bool selected:false

    Rectangle {
        id: container
        anchors.fill:parent
        color: {
            if(currentItem===this)
                return colors[2]
            else if(mouseArea.containsMouse)
                return colors[1]
            else
                return colors[0]
        }
        Row{
            padding:8
            IconLabel{
                icon:Icons.test
                selectedIcon:Icons.test
                implicitWidth:30
                implicitHeight:parent.height - 8 * 2
            }
            Label{
                id:label
                text:"example"
            }
        }
    }

    MouseArea{
        id:mouseArea
        anchors.fill:parent
        hoverEnabled:true
        onClicked:{
            switchPage(this)
        }
    }
}
