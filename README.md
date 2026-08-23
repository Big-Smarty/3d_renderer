# BS Engine

A small C++ 3D renderer built on SDL2 and Vulkan.

This is early work. It opens a window, runs a render loop, and prints a frame
time. Whether it will eventually render something more interesting than a
clear color is still an open question. Use at your own risk, and don't run it
on anything you care about.

## Status

- Window and Vulkan instance/device/swapchain setup
- Pipeline, pipeline layout, shader module, and allocated image wrappers
- Dynamic rendering, no render passes yet
- A triangle example (which, at the time of writing, does not show a triangle)

Known limitations: nothing is cached, resources are created and torn down on
every frame, and error handling is a check that exits the process. All of that
is expected to change as the engine grows.

## Building

Dependencies are pulled in as git submodules, so clone with `--recursive`:

```
git clone --recursive git@github.com:Big-Smarty/3d_renderer.git
```

Then build with CMake:

```
cmake -B build
cmake --build build
```

Requirements: a Vulkan SDK with `glslangValidator`, SDL2, and a compiler that
supports C++20. The examples are built by default.

## Layout

- `src/engine/` - the engine: context, renderer, and Vulkan object wrappers
- `include/engine/` - public headers
- `shaders/` - GLSL shaders, compiled to SPIR-V at build time
- `examples/triangle/` - the triangle example

## Dependencies

- [glm](https://github.com/g-truc/glm)
- [spdlog](https://github.com/gabime/spdlog)
- [volk](https://github.com/zeux/volk)
- [VMA](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
- [stb](https://github.com/nothings/stb)
- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
