#pragma once

#include <vulkan/vulkan_core.h>

namespace bs::engine::wrappers::pipeline {
class Pipeline {
public:
  Pipeline(const VkDevice &device,
           const VkGraphicsPipelineCreateInfo &graphics_pipeline_CI);
  Pipeline(const Pipeline &) = delete;
  Pipeline(Pipeline &&) noexcept;
  Pipeline &operator=(const Pipeline &) = delete;
  Pipeline &operator=(Pipeline &&) = delete;
  ~Pipeline();

  VkPipeline pipeline() { return m_pipeline; }

private:
  const VkDevice &m_device;
  VkPipeline m_pipeline;
};
} // namespace bs::wrappers::pipeline
