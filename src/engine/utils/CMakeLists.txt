add_library(utils utils.cpp init_structs/init_structs.cpp)
target_link_libraries(utils spdlog::spdlog volk::volk)
