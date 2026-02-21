import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root

    required property var model
    required property Component delegate

    property color backgroundColor: "transparent"
    property int itemsPerPage: 2              // 每页显示的项数
    property int itemSpacing: 30              // 项与项之间的间距
    property int bottomPadding: 40            // 底部留给分页器的空间

    property bool autoPlay: true              // 是否自动轮播
    property int interval: 3000               // 自动轮播间隔 (毫秒)
    property int animationDuration: 500       // 滑动动画时长
    property int easingType: Easing.OutCubic  // 滑动动画曲线

    property bool showNavigationArrows: true  // 是否显示左右箭头
    property bool showPaginationDots: true    // 是否显示底部圆点
    property color dotColor: "#cccccc"
    property color dotActiveColor: "#333333"
    property color arrowBackgroundColor: "#66000000"
    property color arrowColor: "white"

    readonly property int count: listView.count
    readonly property int pageCount: Math.ceil(count / itemsPerPage)
    property int currentPage: 0

    signal pageChanged(int pageIndex)

    color: backgroundColor
    clip: true

    HoverHandler {
        id: hoverHandler
    }

    // 自动轮播定时器
    Timer {
        id: autoPlayTimer
        interval: root.interval
        running: root.autoPlay && !hoverHandler.hovered && root.pageCount > 1
        repeat: true
        onTriggered: next()
    }

    ListView {
        id: listView
        anchors.fill: parent
        anchors.bottomMargin: root.bottomPadding
        orientation: ListView.Horizontal
        interactive: false
        reuseItems: true
        model: root.model
        contentX: root.currentPage * listView.width
        Behavior on contentX {
            // XAnimator {
            //     duration: root.animationDuration
            //     easing.type: root.easingType
            // }
            NumberAnimation {
                duration: root.animationDuration
                easing.type: root.easingType
            }
        }
        delegate: Item {
            id: delegateWrapper
            width: listView.width / root.itemsPerPage
            height: listView.height
            Item {
                anchors.fill: parent
                anchors.leftMargin: root.itemSpacing / 2
                anchors.rightMargin: root.itemSpacing / 2
                Loader {
                    id: myLoader
                    anchors.fill: parent
                    sourceComponent: root.delegate
                    onLoaded: {
                        if (item) {
                            item.itemData = modelData;
                            item.itemIndex = index;
                        }
                    }
                }
            }
        }
    }

    // control method
    function next() {
        if (root.pageCount <= 1)
            return;
        root.currentPage = (root.currentPage < root.pageCount - 1) ? root.currentPage + 1 : 0;
        root.pageChanged(root.currentPage);
    }

    function prev() {
        if (root.pageCount <= 1)
            return;
        root.currentPage = (root.currentPage > 0) ? root.currentPage - 1 : root.pageCount - 1;
        root.pageChanged(root.currentPage);
    }

    function jumpToPage(pageIndex) {
        if (pageIndex >= 0 && pageIndex < root.pageCount) {
            root.currentPage = pageIndex;
            root.pageChanged(pageIndex);
        }
    }

    // left
    Rectangle {
        visible: root.showNavigationArrows && root.pageCount > 1
        width: 40
        height: 40
        radius: width / 2
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -root.bottomPadding / 2
        color: root.arrowBackgroundColor
        opacity: hoverHandler.hovered ? 1 : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 250
            }
        }

        Text {
            text: "❮"
            color: root.arrowColor
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 18
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: prev()
        }
    }

    // right
    Rectangle {
        visible: root.showNavigationArrows && root.pageCount > 1
        width: 40
        height: 40
        radius: width / 2
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -root.bottomPadding / 2
        color: root.arrowBackgroundColor
        opacity: hoverHandler.hovered ? 1 : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 250
            }
        }

        Text {
            text: "❯"
            color: root.arrowColor
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 18
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: next()
        }
    }

    // bottom dots
    Row {
        visible: root.showPaginationDots && root.pageCount > 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (root.bottomPadding - 10) / 2
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 8

        Repeater {
            model: root.pageCount
            Rectangle {
                width: root.currentPage === index ? 24 : 10
                height: 10
                radius: 5
                color: root.currentPage === index ? root.dotActiveColor : root.dotColor
                Behavior on width {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.OutQuad
                    }
                }
                Behavior on color {
                    ColorAnimation {
                        duration: 200
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    anchors.margins: -5
                    cursorShape: Qt.PointingHandCursor
                    onClicked: jumpToPage(index)
                }
            }
        }
    }
}
