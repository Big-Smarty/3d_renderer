add_library(context context.cpp)
target_link_libraries(context Vulkan::Vulkan SDL2::SDL2 spdlog::spdlog vk-bootstrap::vk-bootstrap VulkanMemoryAllocator)
