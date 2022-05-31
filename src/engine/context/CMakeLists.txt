add_library(context context.cpp)
target_link_libraries(context volk::volk spdlog::spdlog utils allocated_image)
