include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/thirdparty
    ${PROJECT_SOURCE_DIR}/thirdparty/glfw/include
    ${PROJECT_SOURCE_DIR}/thirdparty/spdlog/include
)

set(NODE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/udp_recv_log.cpp
)

add_executable(udp_recv_log ${NODE_SRC})
target_link_libraries(udp_recv_log Threads::Threads Ws2_32)

install(
    TARGETS udp_recv_log
    DESTINATION .
)

set_target_properties(
    udp_recv_log
    PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/lib"
)