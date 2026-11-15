#include "thememanager.h"

#include <QtConcurrent>

namespace ui {

ThemeManager::ThemeManager(ImageStore* store, QObject* parent)
    : QObject(parent), m_store(store) {
  m_primaryTextColor.fromString(QStringLiteral("gray"));
  m_selectedBackColor.fromString(QStringLiteral("#fc3d49"));
  m_sidebarItemHoveredBackColor.setNamedColor(QStringLiteral("#e4e8ec"));
  m_sidebarItemSelectedBackColor.setNamedColor(QStringLiteral("#fc3d49"));
  m_sidebarGradientStops << QColor(QStringLiteral("#f0f3f6"))
                         << QColor(QStringLiteral("#f0f3f6"));
  m_titlebarLeftGradientStops << QColor(QStringLiteral("#f0f3f6"))
                              << QColor(QStringLiteral("#f0f3f6"));
  m_titlebarRightGradientStops << QColor(QStringLiteral("#f7f9fc"))
                               << QColor(QStringLiteral("#f7f9fc"));
  m_contentAreaGradientStops << QColor(QStringLiteral("#f7f9fc"))
                             << QColor(QStringLiteral("#f7f9fc"));

  connect(m_store, &ImageStore::imageReady, this,
          &ThemeManager::onImageReady);
  connect(m_store, &ImageStore::imageFailed, this,
          &ThemeManager::onImageFailed);
}

void ThemeManager::applyThemeFromUrl(const QString& url) {
  m_pendingUrl = url;
  m_store->request(url, m_analysisSize);
}

void ThemeManager::onImageFailed(const QString& url, const QSize& size,
                                 const QString&) {
  if (url != m_pendingUrl || size != m_analysisSize) {
    return;
  }
}

QColor ThemeManager::adjustColorForUI(const QColor& color) {
  if (!color.isValid()) {
    return QColor(QStringLiteral("#f7f9fc"));
  }
  float h = 0;
  float s = 0;
  float l = 0;
  float a = 0;
  color.getHslF(&h, &s, &l, &a);
  s = qBound(0.20f, s, 0.35f);
  l = qBound(0.84f, l, 0.90f);
  return QColor::fromHslF(h, s, l, a);
}

QColor ThemeManager::averageColor(const QImage& image, const QRect& rect) {
  if (image.isNull()) {
    return QColor();
  }
  const QRect area = rect.intersected(image.rect());
  if (area.isEmpty()) {
    return QColor();
  }
  quint64 sr = 0;
  quint64 sg = 0;
  quint64 sb = 0;
  quint64 count = 0;
  const int step = 2;
  for (int y = area.top(); y <= area.bottom(); y += step) {
    const QRgb* line = reinterpret_cast<const QRgb*>(image.constScanLine(y));
    for (int x = area.left(); x <= area.right(); x += step) {
      const QColor color = QColor::fromRgba(line[x]);
      if (color.alpha() < 20) {
        continue;
      }
      sr += color.red();
      sg += color.green();
      sb += color.blue();
      ++count;
    }
  }
  if (count == 0) {
    return QColor();
  }
  return QColor(int(sr / count), int(sg / count), int(sb / count));
}

void ThemeManager::onImageReady(const QString& url, const QSize& size) {
  if (url != m_pendingUrl || size != m_analysisSize) {
    return;
  }
  const QImage image = m_store->get(url, size);
  if (image.isNull()) {
    return;
  }

  auto future = QtConcurrent::task([image]() {
                  const int h = image.height();
                  const QRect topRect(0, 0, image.width(), h / 2);
                  const QRect bottomRect(0, h / 2, image.width(), h - h / 2);
                  const QColor top =
                      adjustColorForUI(averageColor(image, topRect));
                  const QColor bottom =
                      adjustColorForUI(averageColor(image, bottomRect));
                  return qMakePair(top, bottom);
                }).spawn();

  future.then(this, [this](const QPair<QColor, QColor>& colors) {
    QVariantList stops;
    stops << colors.first << colors.second;
    m_titlebarLeftGradientStops = stops;
    m_titlebarRightGradientStops = stops;
    m_sidebarGradientStops = stops;
    m_contentAreaGradientStops = stops;
    m_hasTheme = true;
    emit themeChanged();
  });
}

}  // namespace ui