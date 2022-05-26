#pragma once
#include <engine/context/context.hpp>
#include <utils/utils.hpp>

namespace bs::wrapper::pipeline {
class Pipeline {
public:
  Pipeline(Pipeline &pipeline);
  Pipeline(const Pipeline &) = delete;
  Pipeline(Pipeline &&) noexcept;
  Pipeline &operator=(const Pipeline &) = delete;
  Pipeline &operator=(Pipeline &&) = delete;

  ~Pipeline();

  VkPipeline *pipeline_ptr() { return &m_pipeline; }

private:
  VkPipeline m_pipeline;
};
} // namespace bs::wrapper::pipeline
