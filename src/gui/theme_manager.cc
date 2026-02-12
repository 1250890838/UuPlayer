#include "theme_manager.h"

#include <QDebug>
#include <QtConcurrent>

namespace gui {

ThemeManager::ThemeManager(ImageStore* store, QObject* parent)
    : QObject(parent), m_store(store) {
  m_primaryTextColor.fromString("black");
  m_selectedBackColor.fromString("#fc3d49");
  m_primaryTextColor.fromString("gray");
  m_sidebarItemHoveredBackColor.setNamedColor("#e4e8ec");
  m_sidebarItemSelectedBackColor.setNamedColor("#fc3d49");
  m_sidebarGradientStops << QColor(QStringLiteral("#f0f3f6"))
                         << QColor(QStringLiteral("#f0f3f6"));
  m_titlebarLeftGradientStops << QColor(QStringLiteral("#f0f3f6"))
                              << QColor(QStringLiteral("#f0f3f6"));
  m_titlebarRightGradientStops << QColor(QStringLiteral("#f7f9fc"))
                               << QColor(QStringLiteral("#f7f9fc"));
  m_contentAreaGradientStops << QColor(QStringLiteral("#f7f9fc"))
                             << QColor(QStringLiteral("#f7f9fc"));

  QObject::connect(m_store, &ImageStore::imageReady, this,
                   &ThemeManager::onImageReady);
  QObject::connect(m_store, &ImageStore::imageFailed, this,
                   &ThemeManager::onImageFailed);
}

void ThemeManager::applyThemeFromUrl(const QString& url) {
  m_pendingUrl = url;
  m_store->request(url, m_analysisSize);
}

QVariantList ThemeManager::titlebarLeftGradientStops() {
  return m_titlebarLeftGradientStops;
}

QVariantList ThemeManager::titlebarRightGradientStops() {
  return m_titlebarRightGradientStops;
}

QVariantList ThemeManager::sidebarGradientStops() {
  return m_sidebarGradientStops;
}

QColor ThemeManager::sidebarItemHoveredBackColor() {
  return m_sidebarItemHoveredBackColor;
}

QColor ThemeManager::sidebarItemSelectedBackColor() {
  return m_sidebarItemSelectedBackColor;
}

QVariantList ThemeManager::contentAreaGradientStops() {
  return m_contentAreaGradientStops;
}

QColor ThemeManager::primaryTextColor() {
  return m_primaryTextColor;
}

QColor ThemeManager::accentTextColor() {
  return m_accentTextColor;
}

void ThemeManager::onImageFailed(const QString& url, const QSize& size,
                                 const QString& reason) {
  if (url != m_pendingUrl || size != m_analysisSize)
    return;
  qDebug() << "ThemeManager image failed:" << reason << "url=" << url;
}

QColor ThemeManager::averageColor(const QImage& img, const QRect& rect) {
  if (img.isNull())
    return QColor();
  const QRect r = rect.intersected(img.rect());
  if (r.isEmpty())
    return QColor();
  quint64 sr = 0, sg = 0, sb = 0, sa = 0;
  quint64 count = 0;
  const int step = 2;
  for (int y = r.top(); y <= r.bottom(); y += step) {
    const QRgb* line = reinterpret_cast<const QRgb*>(img.constScanLine(y));
    for (int x = r.left(); x <= r.right(); x += step) {
      const QColor c = QColor::fromRgba(line[x]);
      if (c.alpha() < 20)
        continue;
      sr += c.red();
      sg += c.green();
      sb += c.blue();
      sa += c.alpha();
      ++count;
    }
  }
  if (count == 0)
    return QColor();
  QColor out;
  out.setRgb(int(sr / count), int(sg / count), int(sb / count));
  out.setAlpha(int(sa / count));
  return out;
}

void ThemeManager::onImageReady(const QString& url, const QSize& size) {
  auto th = thread();
  if (url != m_pendingUrl || size != m_analysisSize)
    return;
  const QImage img = m_store->get(url, size);
  if (img.isNull())
    return;
  auto future = QtConcurrent::task([img]() {
                  const int h = img.height();
                  const QRect topRect(0, 0, img.width(), h / 2);
                  const QRect bottomRect(0, h / 2, img.width(), h - h / 2);

                  const QColor c1 = averageColor(img, topRect);
                  const QColor c2 = averageColor(img, bottomRect);
                  return qMakePair(c1, c2);
                }).spawn();
  future.then(this, [this](const QPair<QColor, QColor>& colors) {
    m_titlebarLeftGradientStops.clear();
    m_contentAreaGradientStops.clear();
    m_sidebarGradientStops.clear();
    m_titlebarRightGradientStops.clear();
    m_titlebarLeftGradientStops << colors.first << colors.second;
    m_contentAreaGradientStops = m_sidebarGradientStops =
        m_titlebarRightGradientStops = m_titlebarLeftGradientStops;
    emit themeChanged();
  });
}

}  // namespace gui
