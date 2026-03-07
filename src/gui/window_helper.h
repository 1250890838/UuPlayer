#ifndef WINDOW_HELPER_H
#define WINDOW_HELPER_H

#include <QObject>
#include <QQmlEngine>
#include <QWindow>

namespace gui{
class WindowHelper : public QObject {
  Q_OBJECT
  QML_ELEMENT
 public:
  explicit WindowHelper(QObject* parent = nullptr);
 public:
  Q_INVOKABLE static bool setClickThrough(QWindow* window, bool enabled);
  Q_INVOKABLE static bool setAlwaysOnTop(QWindow* window, bool enabled);
 signals:
};
}
#endif  // WINDOW_HELPER_H
