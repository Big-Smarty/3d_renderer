add_executable(triangle src/triangle.cpp)
target_link_libraries(triangle engine)
target_include_directories(triangle PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
add_dependencies(triangle triangle_shaders)
target_compile_definitions(triangle PRIVATE SHADERS_PATH="${SHADERS_PATH}")
