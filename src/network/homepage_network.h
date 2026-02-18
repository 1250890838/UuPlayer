#ifndef HOMEPAGE_NETWORK_H
#define HOMEPAGE_NETWORK_H

#include "basic_network.h"

namespace network{
class HomepageNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  HomepageNetwork();
  void fetch(bool refresh);
 signals:
  void ready(error_code::ErrorCode code, const QByteArray& data);
};
}
#endif  // HOMEPAGE_NETWORK_H
