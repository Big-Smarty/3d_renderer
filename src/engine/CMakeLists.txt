add_subdirectory("context")
add_subdirectory("camera")

add_library(engine engine.cpp)
target_link_libraries(engine Vulkan::Vulkan spdlog::spdlog glm context)
