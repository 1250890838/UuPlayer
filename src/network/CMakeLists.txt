add_library(network SHARED basic_network.cc login_network.cc playlist_network.cc)


target_compile_definitions(network PRIVATE NETWORK_EXPORT_SYMBOLS)

target_include_directories(network INTERFACE ".")

target_link_libraries(network PUBLIC Qt6::Core Qt6::Network Qt6::Qml)
