import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import components 1.0


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
Item {
    id: root
    required property var modelData
    implicitHeight: column.implicitHeight
    RowLayout {
        anchors.fill: parent
        IconButton {
            icon: modelData.userData.avatarUrl
            hoveredIcon: modelData.userData.avatarUrl
            width: 40
            height: 40
        }

        Column {
            id: column
            Layout.preferredHeight: userName.implicitHeight + commentContent.implicitHeight
                                    + commentTime.implicitHeight + 2 * column.spacing
            Layout.fillWidth: true
            Layout.fillHeight: true
            Label {
                id: userName
                text: modelData.userData.name
            }

            Label {
                id: commentContent
                text: modelData.content
            }

            Label {
                id: commentTime
                text: Utils.convertMillisecondsToDate(modelData.time)
            }
        }
    }
}
