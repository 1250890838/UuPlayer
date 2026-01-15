#include <QTest>

namespace test {
class TestService : public QObject {
  Q_OBJECT
 private slots:
  void localSongService_SongsSearchDirs();
};
}  // namespace test
