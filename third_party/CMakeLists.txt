find_package(Vulkan REQUIRED)

add_library(glm INTERFACE)

add_library(stb_image INTERFACE)

add_library(tinyobjloader STATIC)

#both vma and glm and header only libs so we only need the include path
target_include_directories(glm INTERFACE glm)

target_sources(
  tinyobjloader PRIVATE
  tinyobjloader/tiny_obj_loader.h
  tinyobjloader/tiny_obj_loader.cc
)

target_include_directories(tinyobjloader PUBLIC tinyobjloader)

add_subdirectory(vk-bootstrap)
add_subdirectory(vma)
add_subdirectory(spdlog)
add_subdirectory(volk)


include_directories("vkbootstrap/src/")
include_directories("vma/include/")
include_directories("spdlog/include/")

add_library(sdl2 INTERFACE)
set(sdl2_DIR "SDL_PATH" CACHE PATH "Path to SDL2")

target_link_libraries(sdl2 INTERFACE SDL2 SDL2main)

target_include_directories(stb_image INTERFACE stb_image)
