#pragma once

#define VK_NO_PROTOTYPES
#include "engine/context/context.hpp"
#include "engine/utils/result/result.hpp"

namespace bs::engine {
class Engine {
public:
  Engine();
  Engine(const Engine &) = delete;
  Engine(Engine &&) noexcept;
  Engine &operator=(const Engine &) = delete;
  Engine &operator=(Engine &&) = delete;
  ~Engine();

  bs::engine::utils::result::Result run();
private:
  bool m_running{1};
  context::Context m_context;
};
} // namespace bs::engine
