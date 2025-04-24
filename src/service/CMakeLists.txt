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
    SOURCES model/comment_data.h model/comment_data.cc
    SOURCES model/comment_item_model.h model/comment_item_model.cc
    SOURCES play_service.h play_service.cc
)

target_compile_definitions(service PRIVATE SERVICE_EXPORT_SYMBOLS)

target_link_libraries(service PRIVATE Qt6::Core Qt6::Gui Qt6::Concurrent network engine)
