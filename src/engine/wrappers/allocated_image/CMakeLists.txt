add_library(allocated_image allocated_image.cpp)
target_link_libraries(allocated_image VulkanMemoryAllocator volk::volk spdlog::spdlog context)
