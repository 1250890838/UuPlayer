add_library(network SHARED
    api_network.h
    basic_network.h login_network.h playlist_network.h
    basic_network.cc login_network.cc playlist_network.cc
    song_network.h song_network.cc)


target_compile_definitions(network PRIVATE NETWORK_EXPORT_SYMBOLS)

target_include_directories(network INTERFACE ".")

target_link_libraries(network PUBLIC Qt6::Core Qt6::Network Qt6::Qml)
