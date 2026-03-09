#ifndef LYRIC_TYPES_H
#define LYRIC_TYPES_H
#include <qtypes.h>
#include <QString>
#include <QVector>

namespace entities{
struct LyricToken {
  quint64 startMs{};
  quint64 endMs{};
  QString text;
};

struct LyricLine {
  quint64 startMs{};
  quint64 endMs{};
  QVector<LyricToken> tokens;
  QString plainText;
};
}
#endif  // LYRIC_TYPES_H
