add_library(shader_module shader_module.cpp)
target_link_libraries(shader_module volk::volk spdlog::spdlog utils)
