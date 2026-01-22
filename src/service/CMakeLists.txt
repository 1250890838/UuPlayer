qt_add_library(service SHARED
    login_service.h
    recommended_playlist_service.h
    login_service.cc
    recommended_playlist_service.cc
    song_service.h
    song_service.cc
    play_service.h play_service.cc
    local_song_service.h local_song_service.cc
    playlist_tracks_service.h playlist_tracks_service.cc
    comments_fetch_service.h comments_fetch_service.cc
    song_url_service.h song_url_service.cc
)

target_compile_definitions(service PRIVATE SERVICE_EXPORT_SYMBOLS)

target_compile_definitions(service
    PRIVATE
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
        $<$<CONFIG:RelWithDebInfo>:QT_NO_DEBUG_OUTPUT>
        $<$<CONFIG:MinSizeRel>:QT_NO_DEBUG_OUTPUT>
)

target_include_directories(service INTERFACE ".")

target_link_libraries(service PUBLIC entities network engine Qt6::Core Qt6::Gui Qt6::Concurrent Qt6::Qml)
