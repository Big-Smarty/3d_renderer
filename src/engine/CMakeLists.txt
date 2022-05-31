add_subdirectory("utils")
add_subdirectory("wrappers")
add_subdirectory("context")
add_subdirectory("renderer")

add_library(engine engine.cpp)
target_link_libraries(engine volk::volk spdlog::spdlog SDL2::SDL2 glm context)
