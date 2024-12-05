add_library(engine SHARED audio_player.cc media_item_model.cc)


target_compile_definitions(engine PRIVATE ENGINE_EXPORT_SYMBOLS)

target_link_libraries(engine PUBLIC Qt6::Core Qt6::Quick Qt6::Multimedia)