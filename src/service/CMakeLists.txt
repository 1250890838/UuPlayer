add_library(service SHARED 
    login_service.h
    playlist_service.h
    model/media_item_model.h
    model/playlist_item_model.h

    login_service.cc
    playlist_service.cc
    model/media_item_model.cc
    model/playlist_item_model.cc
)

target_compile_definitions(service PRIVATE SERVICE_EXPORT_SYMBOLS)

target_link_libraries(service PRIVATE Qt6::Core Qt6::Gui Qt6::Concurrent network)
