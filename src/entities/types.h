#ifndef TYPES_H
#define TYPES_H
#include <QObject>
namespace entities {
Q_NAMESPACE
enum PlayMode { Sequentially, ListLoop, SingleLoop, Shuffle };
Q_ENUM_NS(PlayMode)
// namespace entities

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
}  // namespace entities
#endif  // TYPES_H
