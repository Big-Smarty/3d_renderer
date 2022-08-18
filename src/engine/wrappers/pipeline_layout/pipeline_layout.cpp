#include "engine/wrappers/pipeline_layout/pipeline_layout.hpp"
#include "engine/utils/utils.hpp"

namespace bs::engine::wrappers::pipeline_layout {
PipelineLayout::PipelineLayout(
    const VkDevice &_device,
    const VkPipelineLayoutCreateInfo &_pipeline_layout_create_info)
    : m_device(_device) {
  VK_CHECK(vkCreatePipelineLayout(m_device, &_pipeline_layout_create_info,
                                  nullptr, &m_pipeline_layout));
}
PipelineLayout::~PipelineLayout() {
  vkDestroyPipelineLayout(m_device, m_pipeline_layout, nullptr);
}
} // namespace bs::engine::wrappers::pipeline_layout
