#include "UuWindow.h"
#include <qnamespace.h>
#include <qpoint.h>
#include <qquickwindow.h>
#include <qttypetraits.h>
#include <qtypes.h>
#include <qwindowdefs.h>
#include <QScreen>

UuWindow::UuWindow(QWindow* parent) : QQuickWindow(parent) {
  setFlags(Qt::Window | Qt::FramelessWindowHint);
}

void UuWindow::applyRadius(qint32 radius) {
  QRect r(QPoint(), this->geometry().size());
  QRect rb(0, 0, 2 * radius, 2 * radius);

  QRegion region(rb, QRegion::Ellipse);
  rb.moveRight(r.right());
  region += QRegion(rb, QRegion::Ellipse);
  rb.moveBottom(r.bottom());
  region += QRegion(rb, QRegion::Ellipse);
  rb.moveLeft(r.left());
  region += QRegion(rb, QRegion::Ellipse);
  region += QRegion(r.adjusted(radius, 0, -radius, 0), QRegion::Rectangle);
  region += QRegion(r.adjusted(0, radius, 0, -radius), QRegion::Rectangle);
  this->setMask(region);

  // TODO: extract this to a function named initPosition()
  auto screen = this->screen();
  QPoint point =
      screen->availableGeometry().center() - QPoint(width() / 2, height() / 2);
  setPosition(point);
}

void UuWindow::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    QPointF delta = event->globalPosition() - m_lastPos;
    setPosition(x() + delta.x(), y() + delta.y());
  }
  m_lastPos = event->globalPosition();
  QQuickWindow::mouseMoveEvent(event);
}

void UuWindow::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    m_lastPos = event->globalPosition();
  }
  QQuickWindow::mousePressEvent(event);
}

void UuWindow::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    m_lastPos = QPointF();
  }
  QQuickWindow::mouseReleaseEvent(event);
}