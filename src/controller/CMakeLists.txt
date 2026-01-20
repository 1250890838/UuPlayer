qt_add_library(controller SHARED
    model/comment_item_model.h model/comment_item_model.cc
    model/mediaitem_filterproxy_model.h model/mediaitem_filterproxy_model.cc
    model/local_media_item_model.h model/local_media_item_model.cc
    model/media_item_model.h model/media_item_model.cc
    model/playlist_item_model.h model/playlist_item_model.cc
)

target_compile_definitions(controller PRIVATE CONTROLLER_EXPORT_SYMBOLS)

target_link_libraries(controller PUBLIC entities Qt6::Core Qt6::Gui Qt6::Qml)
