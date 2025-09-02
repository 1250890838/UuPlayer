import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import components 1.0
import assets 1.0


/*
  commentdata
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(UserData userData READ userData)
  Q_PROPERTY(PendantData pendant READ pendant)
  Q_PROPERTY(qulonglong time READ time)
  Q_PROPERTY(QString content READ content)
  Q_PROPERTY(qulonglong likedCount READ likedCount)

userdata
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QUrl avatarUrl READ avatarUrl WRITE setAvatarUrl)
  Q_PROPERTY(QUrl backgroundUrl READ backgroundUrl WRITE setBackgroundUrl)
  Q_PROPERTY(QStringList expertTags READ expertTags WRITE setExpertTags)
  Q_PROPERTY(qulonglong birthday READ birthday WRITE setBirthday)
  Q_PROPERTY(bool followed READ followed WRITE setFollowed)
  Q_PROPERTY(QString name READ name WRITE setName)
*/
Pane {
    id: root
    required property var modelData
    implicitHeight: Math.max(column.implicitHeight,
                             iconButton.implicitHeight) + root.padding * 4
    padding: 10
    background: Rectangle {
        color: "transparent"
    }
    RowLayout {
        width: parent.width
        spacing: 15
        IconButton {
            id: iconButton
            icon: modelData.userData.avatarUrl
            hoveredIcon: modelData.userData.avatarUrl
            implicitWidth: 40
            implicitHeight: 40
            Layout.alignment: Qt.AlignTop
            radius: this.implicitHeight / 2
        }

        Column {
            id: column
            Layout.preferredHeight: userName.implicitHeight + commentContent.implicitHeight
                                    + commentTime.implicitHeight + 2 * column.spacing
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 8
            Label {
                id: userName
                text: modelData.userData.name
            }

            Label {
                id: commentContent
                text: modelData.content
            }

            Item {
                id: spacer
                width: 1
                height: 1
            }

            Label {
                id: commentTime
                text: Utils.convertMillisecondsToDate(modelData.time)
                font.pointSize: 7
                color: "gray"
            }
        }

        Row {
            id: buttonGroupRow
            spacing: 25
            Layout.alignment: Qt.AlignBottom
            IconButton {
                icon: Icons.commentItemLikeIcon
                hoveredIcon: Icons.commentItemLikeIcon
                width: 18
                height: 18
            }
            IconButton {
                icon: Icons.commentItemShareIcon
                hoveredIcon: Icons.commentItemShareIcon
                width: 16
                height: 16
            }
            IconButton {
                icon: Icons.commentItemCommentIcon
                hoveredIcon: Icons.commentItemCommentIcon
                width: 16
                height: 16
            }
        }
    }

    Rectangle {
        id: fancyDivider
        width: parent.width
        height: 1
        anchors {
            bottom: parent.bottom
            leftMargin: 5
            rightMargin: 5
        }
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "transparent"
            }
            GradientStop {
                position: 0.4
                color: "#e0e0e0"
            }
            GradientStop {
                position: 0.6
                color: "#e0e0e0"
            }
            GradientStop {
                position: 1.0
                color: "transparent"
            }
        }
    }
}
