#pragma once

#include "engine/context/context.hpp"
#include "wrapper/pipeline/pipeline.hpp"

namespace bs::engine {
class Engine {
public:
  Engine();
  ~Engine();

private:
  context::Context m_context;
  bs::wrapper::pipeline::Pipeline
  example_pipeline(bs::engine::context::Context m_context);
};
} // namespace bs::engine
