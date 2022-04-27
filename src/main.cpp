#include "engine/engine.hpp"
#include <spdlog/spdlog.h>

int main() {
  spdlog::set_pattern("[%^%l%$] %v");
  spdlog::set_level(spdlog::level::trace);
  bs::engine::Engine engine;
}
