#pragma once

#include "engine/context/context.hpp"
#include "engine/utils/result/result.hpp"
#include "engine/wrappers/pipeline/pipeline.hpp"

namespace bs::engine {
class Engine {
public:
  Engine();
  Engine(const Engine &) = delete;
  Engine(Engine &&) noexcept;
  Engine &operator=(const Engine &) = delete;
  Engine &operator=(Engine &&) = delete;
  ~Engine();

  bs::engine::context::Context *context() { return &m_context; }

  bs::engine::utils::result::Result run(bs::engine::wrappers::pipeline::Pipeline *_pipeline);
  bs::engine::utils::result::Result handle_events();

private:
  bool m_running{1};
  context::Context m_context;
};
} // namespace bs::engine
