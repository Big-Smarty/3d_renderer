set(SOURCE_FILES 
  engine/utils/utils.cpp
  engine/utils/init_structs/init_structs.cpp
  engine/wrappers/allocated_image/allocated_image.cpp
  engine/wrappers/pipeline/pipeline.cpp
  engine/wrappers/shader_module/shader_module.cpp
  engine/context/context.cpp
  engine/renderer/renderer.cpp
  engine/engine.cpp
  vk_mem_alloc.cpp)
add_library(engine ${SOURCE_FILES})
target_link_libraries(engine volk::volk spdlog::spdlog SDL2::SDL2 glm VulkanMemoryAllocator)
