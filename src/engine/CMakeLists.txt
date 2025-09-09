add_library(engine SHARED
    audio_player.h
    audio_player.cc
    metadata_extractor.h metadata_extractor.cpp)


target_compile_definitions(engine PRIVATE ENGINE_EXPORT_SYMBOLS)

target_include_directories(engine PUBLIC .)

target_link_libraries(engine PUBLIC Qt6::Core Qt6::Quick Qt6::Multimedia)
