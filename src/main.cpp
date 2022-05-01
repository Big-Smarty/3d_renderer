#include "engine/engine.hpp"

int main() {
  spdlog::set_pattern("[%^%l%$] %v");
  spdlog::set_level(spdlog::level::trace);
  bs::engine::Engine engine;
}
