add_library(pipeline pipeline.cpp)
target_link_libraries(pipeline volk::volk spdlog::spdlog context)
