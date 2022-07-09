#pragma once

#include <engine/context/context.hpp>

struct VkGraphicsPipelineCreateInfo;
struct VkPipeline_T;
typedef struct VkPipeline_T *VkPipeline;

namespace bs::wrappers::pipeline {
class Pipeline {
public:
  Pipeline(const VkDevice &device,
           const VkGraphicsPipelineCreateInfo &graphics_pipeline_CI);
  Pipeline(const Pipeline &) = delete;
  Pipeline(Pipeline &&) noexcept;
  Pipeline &operator=(const Pipeline &) = delete;
  Pipeline &operator=(Pipeline &&) = delete;
  ~Pipeline();

private:
  const VkDevice &m_device;
  VkPipeline m_pipeline;
};
} // namespace bs::wrapper::pipeline
