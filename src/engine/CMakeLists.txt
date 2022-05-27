add_library(engine engine.cpp context/context.cpp)
target_link_libraries(engine volk::volk spdlog::spdlog SDL2::SDL2 glm utils)
