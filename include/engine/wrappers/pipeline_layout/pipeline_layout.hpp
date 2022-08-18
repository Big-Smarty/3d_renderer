#pragma once

#include <vulkan/vulkan_core.h>

namespace bs::engine::wrappers::pipeline_layout {
class PipelineLayout {
public:
  PipelineLayout(
      const VkDevice &_device,
      const VkPipelineLayoutCreateInfo &_pipeline_layout_create_info);
  ~PipelineLayout();

  VkPipelineLayout pipeline_layout() { return m_pipeline_layout; }

private:
  VkPipelineLayout m_pipeline_layout;
  const VkDevice &m_device;
};
} // namespace bs::engine::wrappers::pipeline_layout
