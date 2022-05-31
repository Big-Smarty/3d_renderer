#pragma once

#define VK_NO_PROTOTYPES
#include "engine/context/context.hpp"

namespace bs::engine {
class Engine {
public:
  Engine();
  Engine(const Engine &) = delete;
  Engine(Engine &&) noexcept;
  Engine &operator=(const Engine &) = delete;
  Engine &operator=(Engine &&) = delete;

  ~Engine();

private:
  context::Context m_context;
};
} // namespace bs::engine
