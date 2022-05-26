#include "pipeline_builder.hpp"

namespace bs::wrapper::pipeline_builder {
pipeline::Pipeline
PipelineBuilder::create_graphics_pipeline(VkDevice device,
                                          VkPipelineCache pipeline_cache) {
  m_graphics_CI.stageCount = m_stage_count;
  m_graphics_CI.pStages = m_shader_stages_CI;
  m_graphics_CI.pVertexInputState = m_vertex_input_state_CI;
  m_graphics_CI.pInputAssemblyState = m_input_assembly_state_CI;
  m_graphics_CI.pTessellationState = m_tesselation_state_CI;
  m_graphics_CI.pViewportState = m_viewport_state_CI;
  m_graphics_CI.pRasterizationState = m_rasterization_state_CI;
  m_graphics_CI.pMultisampleState = m_multisample_state_CI;
  m_graphics_CI.pDepthStencilState = m_depth_stencil_state_CI;
  m_graphics_CI.pColorBlendState = m_color_blend_state_CI;
  m_graphics_CI.pDynamicState = m_dynamic_state_CI;
  m_graphics_CI.layout = *m_pipeline_layout;
  m_graphics_CI.renderPass = *m_renderpass;
  m_graphics_CI.basePipelineHandle = *m_base_pipeline_handle;
  m_graphics_CI.basePipelineIndex = m_base_pipeline_index;

  VK_CHECK(vkCreateGraphicsPipelines(device, pipeline_cache, 1, &m_graphics_CI,
                                     nullptr, m_pipeline->pipeline_ptr()))
  return *m_pipeline;
}
pipeline::Pipeline
PipelineBuilder::create_compute_pipeline(VkDevice device,
                                         VkPipelineCache pipeline_cache) {
  m_compute_CI.stage = *m_shader_stages_CI;
  m_compute_CI.layout = *m_pipeline_layout;
  m_compute_CI.basePipelineHandle = *m_base_pipeline_handle;
  m_compute_CI.basePipelineIndex = m_base_pipeline_index;
  return *m_pipeline;
}

PipelineBuilder &PipelineBuilder::set_stage_count(uint32_t stage_count) {
  m_stage_count = stage_count;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_pstages(
    VkPipelineShaderStageCreateInfo *shader_stages_CI) {
  m_shader_stages_CI = shader_stages_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_vertex_input_state(
    VkPipelineVertexInputStateCreateInfo *vertex_input_state_CI) {
  m_vertex_input_state_CI = vertex_input_state_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_input_assembly_state(
    VkPipelineInputAssemblyStateCreateInfo *input_assembly_state_CI) {
  m_input_assembly_state_CI = input_assembly_state_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_tesselation_state(
    VkPipelineTessellationStateCreateInfo *tesselation_state_CI) {
  m_tesselation_state_CI = tesselation_state_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_viewport_state(
    VkPipelineViewportStateCreateInfo *viewport_state_CI) {
  m_viewport_state_CI = viewport_state_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_rasterization_state(
    VkPipelineRasterizationStateCreateInfo *rasterization_CI) {
  m_rasterization_state_CI = rasterization_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_multisampling_state(
    VkPipelineMultisampleStateCreateInfo *multisampling_state_CI) {
  m_multisample_state_CI = multisampling_state_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_depth_stencil_state(
    VkPipelineDepthStencilStateCreateInfo *depth_stencil_state_CI) {
  m_depth_stencil_state_CI = depth_stencil_state_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_color_blend_state(
    VkPipelineColorBlendStateCreateInfo *color_blend_state_CI) {
  m_color_blend_state_CI = color_blend_state_CI;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_dynamic_state(
    VkPipelineDynamicStateCreateInfo *dynamic_state_CI) {
  m_dynamic_state_CI = dynamic_state_CI;
  return *this;
}
PipelineBuilder &
PipelineBuilder::set_layout(VkPipelineLayout *pipeline_layout) {
  m_pipeline_layout = pipeline_layout;
  return *this;
}
PipelineBuilder &PipelineBuilder::set_renderpass(VkRenderPass *renderpass) {
  m_renderpass = renderpass;
  return *this;
}
PipelineBuilder &
PipelineBuilder::set_base_pipeline_handle(VkPipeline *base_pipeline_handle) {
  m_base_pipeline_handle = base_pipeline_handle;
  return *this;
}
PipelineBuilder &
PipelineBuilder::set_base_pipeline_index(int32_t base_pipeline_index) {
  m_base_pipeline_index = base_pipeline_index;
  return *this;
}
} // namespace bs::wrapper::pipeline_builder
