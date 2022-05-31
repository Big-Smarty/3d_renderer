add_library(vk_mem_alloc vk_mem_alloc.cpp)
target_link_libraries(vk_mem_alloc VulkanMemoryAllocator)
add_subdirectory("engine")
