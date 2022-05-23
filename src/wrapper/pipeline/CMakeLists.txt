add_library(pipeline pipeline.cpp)
target_link_libraries(pipeline utils spdlog::spdlog volk::volk)
