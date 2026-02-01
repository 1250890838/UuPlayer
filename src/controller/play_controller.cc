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
          &PlayController::positionChanged);
  connect(m_service, &PlayService::volumnChanged, this,
          &PlayController::volumnChanged);
  connect(m_service, &PlayService::durationChanged, this,
          &PlayController::durationChanged);
  connect(m_service, &PlayService::currentPlayItemChanged, this,
          &PlayController::currMediaItemChanged);
  connect(m_service, &PlayService::currentLyricChanged, this,
          &PlayController::lyricChanged);
}

PlayController* PlayController::create(QQmlEngine* qmlEngine,
                                       QJSEngine* jsEngine) {

  auto service = ServiceManager::instance().getInstance<PlayService>();
  auto controller = new PlayController(service);
  controller->m_mediasModel.setExternalData(service->mediasPtr());
  return controller;
}

void PlayController::play(qulonglong id) {
  m_service->play(id);
}

void PlayController::play() {
  m_service->play();
}

void PlayController::pause() {
  m_service->pause();
}

void PlayController::next() {
  m_service->next();
}

void PlayController::previous() {
  m_service->previous();
}

}  // namespace controller
