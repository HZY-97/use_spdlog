include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/thirdparty
    ${PROJECT_SOURCE_DIR}/thirdparty/glfw/include
    ${PROJECT_SOURCE_DIR}/thirdparty/spdlog/include
)

set(NODE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(use_spdlog ${NODE_SRC})
target_link_libraries(use_spdlog Threads::Threads Ws2_32)

install(
    TARGETS use_spdlog
    DESTINATION .
)

set_target_properties(
    use_spdlog
    PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/lib"
)