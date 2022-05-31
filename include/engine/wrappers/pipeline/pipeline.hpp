#pragma once

#define VK_NO_PROTOTYPES
#include <engine/context/context.hpp>

namespace bs::wrapper::pipeline {
class Pipeline {
public:
  Pipeline(const VkDevice &device,
           const VkGraphicsPipelineCreateInfo &graphics_pipeline_CI = {
               .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO});
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
