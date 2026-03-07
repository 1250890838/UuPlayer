#include "window_helper.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace gui {

WindowHelper::WindowHelper(QObject* parent) {}

bool WindowHelper::setClickThrough(QWindow* window, bool enabled) {
#ifdef _WIN32
  if (!window)
    return false;
  HWND hwnd = reinterpret_cast<HWND>(window->winId());
  if (!hwnd)
    return false;
  LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
  if (enabled) {
    exStyle |= WS_EX_TRANSPARENT;
    exStyle |= WS_EX_LAYERED;
  } else {
    exStyle &= ~WS_EX_TRANSPARENT;
  }
  SetWindowLongPtr(hwnd, GWL_EXSTYLE, exStyle);
  SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
  return true;
#else
  Q_UNUSED(window);
  Q_UNUSED(enabled);
  return false;
#endif
}

bool WindowHelper::setAlwaysOnTop(QWindow* window, bool enabled) {
#ifdef _WIN32
  if (!window)
    return false;
  HWND hwnd = reinterpret_cast<HWND>(window->winId());
  if (!hwnd)
    return false;
  SetWindowPos(hwnd, enabled ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0,
               SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
  return true;
#else
  Q_UNUSED(window);
  Q_UNUSED(enabled);
  return false;
#endif
}
}  // namespace gui