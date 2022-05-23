#pragma once
#include <engine/context/context.hpp>
#include <utils/utils.hpp>

namespace bs::wrapper::pipeline {
class Pipeline {
public:
  Pipeline(bs::engine::context::Context &_context);
  ~Pipeline();

  Pipeline compute_pipeline();
  Pipeline graphics_pipeline();

private:
  bs::engine::context::Context &m_context;

  VkPipeline m_pipeline;
};
} // namespace bs::wrapper::pipeline
