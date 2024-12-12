import QtQuick.Controls
import QtQuick

Item {
    id: root
    implicitHeight:20
    implicitWidth:20
    required property url icon    
    property real margins:0

    Image{
        id:image
        anchors.fill:parent
        anchors.margins:root.margins
        source:root.icon
        fillMode: Image.PreserveAspectFit
        mipmap:true
        smooth:true
    }
}
