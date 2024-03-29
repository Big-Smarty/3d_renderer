cmake_minimum_required(VERSION 3.20)
project(bs_engine_improved)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_BUILD_TYPE Release)

add_compile_options(-g)

include_directories("${PROJECT_SOURCE_DIR}/third_party/spdlog/include/")
include_directories("${PROJECT_SOURCE_DIR}/third_party/volk/")
include_directories("${PROJECT_SOURCE_DIR}/third_party/vma/include/")
include_directories("${PROJECT_SOURCE_DIR}/include/")

find_package(SDL2 REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory("third_party")
add_subdirectory("src")
add_subdirectory("shaders")
add_subdirectory("examples")

set(CMAKE_C_COMPILER /bin/clang)
set(CMAKE_CXX_COMPILER /bin/clang++)
