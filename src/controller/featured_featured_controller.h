#ifndef FEATUREDFEATUREDCONTROLLER_H
#define FEATUREDFEATUREDCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
namespace controller {

class FeaturedFeaturedController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
 public:
  FeaturedFeaturedController();
};
}  // namespace controller
#endif // FEATUREDFEATUREDCONTROLLER_H
