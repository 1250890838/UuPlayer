#include "test_service.h"

#include <QSignalSpy>

#include "local_song_service.h"
namespace test {

void TestService::localSongService_SongsSearchDirs() {
  service::LocalSongService localSongService;
  auto dirs = localSongService.songsSearchDirs();
  QVERIFY(!dirs.empty());
  localSongService.clearSearchDirs();
  dirs = localSongService.songsSearchDirs();
  QVERIFY(dirs.empty());
}
}  // namespace test
QTEST_MAIN(test::TestService)
