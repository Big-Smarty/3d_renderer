add_library(context context.cpp)
target_link_libraries(context volk::volk SDL2::SDL2 spdlog::spdlog vk-bootstrap::vk-bootstrap VulkanMemoryAllocator utils)
