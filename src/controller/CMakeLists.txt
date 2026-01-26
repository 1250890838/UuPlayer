add_library(controller SHARED
    model/comment_item_model.h model/comment_item_model.cc
    model/mediaitem_filterproxy_model.h model/mediaitem_filterproxy_model.cc
    model/local_media_item_model.h model/local_media_item_model.cc
    model/media_item_model.h model/media_item_model.cc
    model/playlist_item_model.h model/playlist_item_model.cc
)

qt6_add_qml_module(
   controller
   URI controller
   SOURCES featured_featured_controller.h featured_featured_controller.cc
   SOURCES featured_playlisthub_controller.h featured_playlisthub_controller.cc
   SOURCES playlistdetails_controller.h playlistdetails_controller.cc
)


target_compile_definitions(controller PRIVATE CONTROLLER_EXPORT_SYMBOLS)

target_link_libraries(controller PUBLIC entities service Qt6::Core Qt6::Gui Qt6::Qml)
