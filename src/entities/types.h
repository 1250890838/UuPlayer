#ifndef TYPES_H
#define TYPES_H
#include <QObject>

namespace play_mode {
Q_NAMESPACE
enum PlayMode { Sequentially, ListLoop, SingleLoop, Shuffle };
Q_ENUM_NS(PlayMode)
}  // namespace play_mode

namespace error_code {
Q_NAMESPACE
enum ErrorCode {
  NoError = 0,
  ConnectionRefusedError,
  TimeoutError,
  JsonContentError,
  OtherError
};
Q_ENUM_NS(ErrorCode)
}  // namespace error_code

namespace sound_level {
Q_NAMESPACE
enum SoundQualityLevel {
  Standard,
  Higher,
  Exhigh,
  Lossless,
  Hires,
  Jyeffect,
  Sky,
  Jymaster
};
Q_ENUM_NS(SoundQualityLevel)
}  // namespace sound_level
#endif  // TYPES_H
