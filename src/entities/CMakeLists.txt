qt_add_library(entities SHARED
   media_item.h
   album_item.h
   arist_item.h
   media_item.cc
   local_media_item.h
   playlist_item.h
   user_item.h
   comment_item.h
)

target_compile_definitions(entities PRIVATE CONTROLLER_EXPORT_SYMBOLS)

target_include_directories(entities INTERFACE ".")

target_link_libraries(entities PUBLIC Qt6::Core)
