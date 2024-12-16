add_library(service SHARED login_service.cc)

target_compile_definitions(service PRIVATE SERVICE_EXPORT_SYMBOLS)

target_link_libraries(service PRIVATE Qt6::Core network)