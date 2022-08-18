#include "engine/wrappers/pipeline/pipeline.hpp"

#include "engine/utils/utils.hpp"

namespace bs::engine::wrappers::pipeline {
Pipeline::Pipeline(const VkDevice &device,
                   const VkGraphicsPipelineCreateInfo &graphics_pipeline_CI)
    : m_device(device) {
  VK_CHECK(vkCreateGraphicsPipelines(
      m_device, nullptr, 1, &graphics_pipeline_CI, nullptr, &m_pipeline));
}
Pipeline::~Pipeline() { vkDestroyPipeline(m_device, m_pipeline, nullptr); }
} // namespace bs::wrappers::pipeline
