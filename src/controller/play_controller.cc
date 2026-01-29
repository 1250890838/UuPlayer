#include "play_controller.h"

#include "service_manager.h"
namespace controller {

PlayController::PlayController(PlayService* service) : m_service(service) {
  connect(m_service, &PlayService::beginInsertItems, &m_mediasModel,
          &MediaItemModel::itemsBeginArrived);
  connect(m_service, &PlayService::endInsertItems, &m_mediasModel,
          &MediaItemModel::itemsEndArrived);
  connect(m_service, &PlayService::beginRemoveItems, &m_mediasModel,
          &MediaItemModel::itemsBeginArrived);
  connect(m_service, &PlayService::endRemoveItems, &m_mediasModel,
          &MediaItemModel::itemsEndArrived);
  connect(m_service, &PlayService::playingChanged, this,
          &PlayController::isPlayingChanged);
  connect(m_service, &PlayService::playbackModeChanged, this,
          &PlayController::playmodeChanged);
  connect(m_service, &PlayService::positionChanged, this,
          &PlayController::positionChnaged);
  connect(m_service, &PlayService::volumnChanged, this,
          &PlayController::volumnChanged);
  connect(m_service, &PlayService::durationChanged, this,
          &PlayController::durationChanged);
}

PlayController* PlayController::create(QQmlEngine* qmlEngine,
                                       QJSEngine* jsEngine) {

  auto service = ServiceManager::instance().getInstance<PlayService>();
  auto controller = new PlayController(service);
  controller->m_mediasModel.setExternalData(service->mediasPtr());
}

}  // namespace controller
