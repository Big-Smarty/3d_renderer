set(SOURCE_FILES 
  engine/utils/utils.cpp
  engine/utils/init_structs/init_structs.cpp
  engine/wrappers/allocated_image/allocated_image.cpp
  engine/wrappers/pipeline/pipeline.cpp
  engine/wrappers/pipeline_layout/pipeline_layout.cpp
  engine/wrappers/shader_module/shader_module.cpp
  engine/context/context.cpp
  engine/renderer/renderer.cpp
  engine/engine.cpp)
add_library(engine ${SOURCE_FILES})
add_library(vk_mem_alloc vk_mem_alloc.cpp)
target_link_libraries(vk_mem_alloc VulkanMemoryAllocator)
target_link_libraries(engine Vulkan::Vulkan spdlog::spdlog SDL2::SDL2 glm vk_mem_alloc)
