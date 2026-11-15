#pragma once

#include <QObject>

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
}

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
}
