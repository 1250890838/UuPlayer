add_library(service SHARED 
    model/media_item_model.h
    model/playlist_item_model.h
    model/media_item_model.cc
    model/playlist_item_model.cc
)

qt6_add_qml_module(service URI service.api VERSION 1.0 SOURCES
    login_service.h
    playlist_service.h
    login_service.cc
    playlist_service.cc
    song_service.h
    song_service.cc
    model/comment_item_model.h model/comment_item_model.cc
    play_service.h play_service.cc
    entities/playlist_item.h
    entities/user_item.h
    entities/comment_data.h
    SOURCES model/mediaitem_filterproxy_model.h model/mediaitem_filterproxy_model.cc
    SOURCES entities/media_item.h
    SOURCES entities/album_data.h
    SOURCES entities/arist_data.h
    SOURCES entities/media_item.cc
    SOURCES entities/local_media_item.h
    SOURCES local_song_service.h local_song_service.cc
    SOURCES model/local_media_item_model.h model/local_media_item_model.cc
    SOURCES
)

target_compile_definitions(service PRIVATE SERVICE_EXPORT_SYMBOLS)

target_compile_definitions(service
    PRIVATE
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
        $<$<CONFIG:RelWithDebInfo>:QT_NO_DEBUG_OUTPUT>
        $<$<CONFIG:MinSizeRel>:QT_NO_DEBUG_OUTPUT>
)

target_include_directories(service INTERFACE ".")

target_link_libraries(service PUBLIC network engine Qt6::Core Qt6::Gui Qt6::Concurrent Qt6::Qml)
