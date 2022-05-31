#include <spdlog/spdlog.h>

#ifndef SHADERS_PATH
#define SHADERS_PATH                                                           \
  spdlog::error("No path given!");                                             \
  exit(-1);
#endif

#include "engine/engine.hpp"
#include "triangle.hpp"

int main() {
  spdlog::set_level(spdlog::level::trace);
  spdlog::set_pattern("[%^%l%$] %v");
  bs::engine::Engine();
}
