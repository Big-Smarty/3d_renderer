#include "pipeline.hpp"
#include <vulkan/vulkan_core.h>

namespace bs::wrapper::pipeline {
Pipeline::Pipeline(bs::engine::context::Context &_context) {
  m_context = _context;
  VkPipelineLayoutCreateInfo pipeline_layout_CI = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
  };
  VK_CHECK(vkCreatePipelineLayout(m_context.device(), nullptr, nullptr,
                                  &m_pipeline_layout));
}
Pipeline::~Pipeline() {}
} // namespace bs::wrapper::pipeline
