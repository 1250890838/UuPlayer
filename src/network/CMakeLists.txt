qt_add_library(network SHARED
    api_network.h
    basic_network.h login_network.h recommended_playlist_network.h
    basic_network.cc login_network.cc recommended_playlist_network.cc
    song_lyric_network.h song_lyric_network.cc
    local_song_network.h local_song_network.cc
    playlist_tracks_network.h playlist_tracks_network.cc
    comments_fetch_network.h comments_fetch_network.cc
    song_url_network.h song_url_network.cc)


target_compile_definitions(network PRIVATE NETWORK_EXPORT_SYMBOLS)

target_compile_definitions(network
    PRIVATE
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
        $<$<CONFIG:RelWithDebInfo>:QT_NO_DEBUG_OUTPUT>
        $<$<CONFIG:MinSizeRel>:QT_NO_DEBUG_OUTPUT>
)

target_include_directories(network INTERFACE ".")

target_link_libraries(network PUBLIC entities Qt6::Core Qt6::Network Qt6::Qml)
