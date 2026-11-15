#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QWindow>

namespace ui {

class WindowHelper : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
 public:
  explicit WindowHelper(QObject* parent = nullptr);

  Q_INVOKABLE static bool setClickThrough(QWindow* window, bool enabled);
  Q_INVOKABLE static bool setAlwaysOnTop(QWindow* window, bool enabled);
};

}  // namespace ui