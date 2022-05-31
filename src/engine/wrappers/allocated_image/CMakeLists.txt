add_library(allocated_image allocated_image.cpp)
target_link_libraries(allocated_image vk_mem_alloc volk::volk spdlog::spdlog context)
