#pragma once

#include <QString>
#include <QVector>

namespace entities {

struct LyricToken {
  quint64 startMs = 0;
  quint64 endMs = 0;
  QString text;
};

struct LyricLine {
  quint64 startMs = 0;
  quint64 endMs = 0;
  QVector<LyricToken> tokens;
  QString plainText;
};

}  // namespace entities