import QtQuick
import QtQuick.Layouts
import QtQuick.Controls


/*
class AristData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)
 public:
  AristData() = default;
  ~AristData() = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }

 private:
  qulonglong m_id;
  QString m_name;
};

struct MediaItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(qulonglong duration MEMBER duration)
  Q_PROPERTY(AlbumData album MEMBER album)
  Q_PROPERTY(QVariantList artists MEMBER artists)
  Q_PROPERTY(QString reason MEMBER reason)
  Q_PROPERTY(QUrl url MEMBER url)

 public:
  qulonglong id;
  QString name;
  qulonglong duration;
  AlbumData album;
  QVariantList artists; // QList<AristData> artists
  QString reason;
  QUrl url;
};
  */
Item {
    id: root
    implicitWidth: 200

    property var mediaData
    Rectangle {
        id: container
        anchors.fill: parent
        color: "#fafafa"

        Rectangle {
            width: parent.width
            height: 1
            color: "#e8e6e5"
            anchors.top: parent.top
        }

        RowLayout {
            id: containerRowLayout
        }
    }
}
