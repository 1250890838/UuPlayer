#pragma once

#include <QColor>
#include <QObject>
#include <QSize>
#include <QVariantList>

#include "imagestore.h"

namespace ui {

class ThemeManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(QVariantList titlebarLeftGradientStops READ titlebarLeftGradientStops NOTIFY themeChanged)
  Q_PROPERTY(QVariantList titlebarRightGradientStops READ titlebarRightGradientStops NOTIFY themeChanged)
  Q_PROPERTY(QVariantList sidebarGradientStops READ sidebarGradientStops NOTIFY themeChanged)
  Q_PROPERTY(QColor sidebarItemHoveredBackColor READ sidebarItemHoveredBackColor NOTIFY themeChanged)
  Q_PROPERTY(QColor sidebarItemSelectedBackColor READ sidebarItemSelectedBackColor NOTIFY themeChanged)
  Q_PROPERTY(QVariantList contentAreaGradientStops READ contentAreaGradientStops NOTIFY themeChanged)
  Q_PROPERTY(QColor primaryTextColor READ primaryTextColor NOTIFY themeChanged)
  Q_PROPERTY(QColor accentTextColor READ accentTextColor NOTIFY themeChanged)
  Q_PROPERTY(bool hasTheme READ hasTheme NOTIFY themeChanged)

 public:
  explicit ThemeManager(ImageStore* store, QObject* parent = nullptr);

  Q_INVOKABLE void applyThemeFromUrl(const QString& url);

  QVariantList titlebarLeftGradientStops() {
    return m_titlebarLeftGradientStops;
  }
  QVariantList titlebarRightGradientStops() {
    return m_titlebarRightGradientStops;
  }
  QVariantList sidebarGradientStops() { return m_sidebarGradientStops; }
  QColor sidebarItemHoveredBackColor() {
    return m_sidebarItemHoveredBackColor;
  }
  QColor sidebarItemSelectedBackColor() {
    return m_sidebarItemSelectedBackColor;
  }
  QVariantList contentAreaGradientStops() {
    return m_contentAreaGradientStops;
  }
  QColor primaryTextColor() { return m_primaryTextColor; }
  QColor accentTextColor() { return m_accentTextColor; }
  bool hasTheme() const { return m_hasTheme; }

 signals:
  void themeChanged();

 private slots:
  void onImageReady(const QString& url, const QSize& size);
  void onImageFailed(const QString& url, const QSize& size,
                     const QString& reason);

 private:
  static QColor averageColor(const QImage& image, const QRect& rect);
  static QColor adjustColorForUI(const QColor& color);

  ImageStore* m_store = nullptr;
  QString m_pendingUrl;
  QSize m_analysisSize = QSize(128, 128);
  QVariantList m_titlebarLeftGradientStops;
  QVariantList m_titlebarRightGradientStops;
  QVariantList m_sidebarGradientStops;
  QColor m_sidebarItemHoveredBackColor;
  QColor m_sidebarItemSelectedBackColor;
  QVariantList m_contentAreaGradientStops;
  QColor m_selectedBackColor;
  QColor m_primaryTextColor;
  QColor m_accentTextColor;
  bool m_hasTheme = false;
};

}  // namespace ui