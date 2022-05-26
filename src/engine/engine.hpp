#pragma once

#include "engine/context/context.hpp"
#include "wrapper/pipeline/pipeline.hpp"

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
  bs::wrapper::pipeline::Pipeline
  example_pipeline(bs::engine::context::Context m_context);
};
} // namespace bs::engine
