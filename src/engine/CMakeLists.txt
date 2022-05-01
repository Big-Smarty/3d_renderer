add_subdirectory("context")
add_subdirectory("camera")

add_library(engine engine.cpp)
target_link_libraries(engine volk::volk spdlog::spdlog glm context)
