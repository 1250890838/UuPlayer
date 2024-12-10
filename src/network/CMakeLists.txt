add_library(network SHARED basic_network.cc)


target_compile_definitions(network PRIVATE NETWORK_EXPORT_SYMBOLS)

target_link_libraries(network PRRIVATE Qt6::Core Qt6::Network)