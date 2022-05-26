#pragma once

#include <wrapper/pipeline/pipeline.hpp>

namespace bs::wrapper::pipeline_builder {
class PipelineBuilder {
public:
  PipelineBuilder(const PipelineBuilder &) = delete;
  PipelineBuilder(PipelineBuilder &&) noexcept;
  PipelineBuilder &operator=(const PipelineBuilder &) = delete;
  PipelineBuilder &operator=(PipelineBuilder &&) = delete;

  pipeline::Pipeline
  create_graphics_pipeline(VkDevice device,
                           VkPipelineCache pipeline_cache = nullptr);
  pipeline::Pipeline
  create_compute_pipeline(VkDevice device,
                          VkPipelineCache pipeline_cache = nullptr);

  PipelineBuilder &set_stage_count(uint32_t stage_count);
  PipelineBuilder &
  set_pstages(VkPipelineShaderStageCreateInfo *shader_stages_CI);
  PipelineBuilder &set_vertex_input_state(
      VkPipelineVertexInputStateCreateInfo *vertex_input_state_CI);
  PipelineBuilder &set_input_assembly_state(
      VkPipelineInputAssemblyStateCreateInfo *input_assembly_state_C);
  PipelineBuilder &set_tesselation_state(
      VkPipelineTessellationStateCreateInfo *tesselation_state_CI);
  PipelineBuilder &
  set_viewport_state(VkPipelineViewportStateCreateInfo *viewport_state_CI);
  PipelineBuilder &set_rasterization_state(
      VkPipelineRasterizationStateCreateInfo *rasterization_CI);
  PipelineBuilder &set_multisampling_state(
      VkPipelineMultisampleStateCreateInfo *multisampling_state_CI);
  PipelineBuilder &set_depth_stencil_state(
      VkPipelineDepthStencilStateCreateInfo *depth_stencil_state_CI);
  PipelineBuilder &set_color_blend_state(
      VkPipelineColorBlendStateCreateInfo *color_blend_state_CI);
  PipelineBuilder &
  set_dynamic_state(VkPipelineDynamicStateCreateInfo *dynamic_state_CI);
  PipelineBuilder &set_layout(VkPipelineLayout *pipeline_layout);
  PipelineBuilder &set_renderpass(VkRenderPass *renderpass);
  PipelineBuilder &set_base_pipeline_handle(VkPipeline *base_pipeline_handle);
  PipelineBuilder &set_base_pipeline_index(int32_t base_pipeline_index);

  pipeline::Pipeline pipeline() { return *m_pipeline; }

private:
  uint32_t m_stage_count{0};
  VkPipelineShaderStageCreateInfo *m_shader_stages_CI{nullptr};
  VkPipelineVertexInputStateCreateInfo *m_vertex_input_state_CI{nullptr};
  VkPipelineInputAssemblyStateCreateInfo *m_input_assembly_state_CI{nullptr};
  VkPipelineTessellationStateCreateInfo *m_tesselation_state_CI{nullptr};
  VkPipelineViewportStateCreateInfo *m_viewport_state_CI{nullptr};
  VkPipelineRasterizationStateCreateInfo *m_rasterization_state_CI{nullptr};
  VkPipelineMultisampleStateCreateInfo *m_multisample_state_CI{nullptr};
  VkPipelineDepthStencilStateCreateInfo *m_depth_stencil_state_CI{nullptr};
  VkPipelineColorBlendStateCreateInfo *m_color_blend_state_CI{nullptr};
  VkPipelineDynamicStateCreateInfo *m_dynamic_state_CI{nullptr};
  VkPipelineLayout *m_pipeline_layout{nullptr};
  VkRenderPass *m_renderpass{nullptr};
  VkPipeline *m_base_pipeline_handle{nullptr};
  int32_t m_base_pipeline_index{0};

  VkComputePipelineCreateInfo m_compute_CI{
      .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO};
  VkGraphicsPipelineCreateInfo m_graphics_CI{
      .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
  pipeline::Pipeline *m_pipeline{nullptr};
};
} // namespace bs::wrapper::pipeline_builder
