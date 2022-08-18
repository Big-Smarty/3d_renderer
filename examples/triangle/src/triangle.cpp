#include "engine/utils/init_structs/init_structs.hpp"
#include "engine/wrappers/pipeline/pipeline.hpp"
#include "engine/wrappers/pipeline_layout/pipeline_layout.hpp"
#include "engine/wrappers/shader_module/shader_module.hpp"
#include <cstdint>
#include <spdlog/spdlog.h>
#include <vulkan/vulkan_core.h>

#ifndef SHADERS_PATH
#define SHADERS_PATH                                                           \
  spdlog::error("No path given!");                                             \
  exit(-1);
#endif

#include "triangle.hpp"

namespace bs::examples::triangle {
Triangle::Triangle() {
  auto pipeline_layout_CI =
      bs::engine::utils::init_structs::make_info<VkPipelineLayoutCreateInfo>();
  std::vector<VkPipelineShaderStageCreateInfo> shader_stages;
  auto vertex_input_state = bs::engine::utils::init_structs::make_info<
      VkPipelineVertexInputStateCreateInfo>();
  auto input_assembly_state = bs::engine::utils::init_structs::make_info<
      VkPipelineInputAssemblyStateCreateInfo>();
  auto tesselation_state = bs::engine::utils::init_structs::make_info<
      VkPipelineTessellationStateCreateInfo>();
  auto viewport_state = bs::engine::utils::init_structs::make_info<
      VkPipelineViewportStateCreateInfo>();
  auto rasterization_state = bs::engine::utils::init_structs::make_info<
      VkPipelineRasterizationStateCreateInfo>();
  auto multisample_state = bs::engine::utils::init_structs::make_info<
      VkPipelineMultisampleStateCreateInfo>();
  auto depth_stencil_state = bs::engine::utils::init_structs::make_info<
      VkPipelineDepthStencilStateCreateInfo>();
  auto color_blend_state = bs::engine::utils::init_structs::make_info<
      VkPipelineColorBlendStateCreateInfo>();
  auto dynamic_state = bs::engine::utils::init_structs::make_info<
      VkPipelineDynamicStateCreateInfo>();
  bs::engine::wrappers::pipeline_layout::PipelineLayout pipeline_layout(
      m_engine.context()->device(), pipeline_layout_CI);

  bs::engine::wrappers::shader_module::ShaderModule vertex_shader(
      "build/shaders/triangle/triangle.vert.spv", m_engine.context()->device());
  bs::engine::wrappers::shader_module::ShaderModule fragment_shader(
      "build/shaders/triangle/triangle.frag.spv", m_engine.context()->device());
  shader_stages.push_back({
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_VERTEX_BIT,
      .module = vertex_shader.shader_module(),
      .pName = "main",
  });
  shader_stages.push_back({
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = fragment_shader.shader_module(),
      .pName = "main",
  });

  input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

  VkViewport viewport = {.x = 0,
                         .y = 0,
                         .width = 640,
                         .height = 480,
                         .minDepth = 0.0f,
                         .maxDepth = 1.0f};
  VkRect2D scissor = {
      .offset = {0, 0},
      .extent = {640, 480},
  };
  viewport_state.viewportCount = 1;
  viewport_state.pViewports = &viewport;
  viewport_state.scissorCount = 1;
  viewport_state.pScissors = &scissor;

  multisample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisample_state.sampleShadingEnable = VK_FALSE;
  multisample_state.alphaToCoverageEnable = VK_FALSE;
  multisample_state.alphaToOneEnable = VK_FALSE;

  rasterization_state.depthClampEnable = VK_FALSE;
  rasterization_state.polygonMode = VK_POLYGON_MODE_FILL;
  rasterization_state.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterization_state.depthBiasEnable = VK_FALSE;
  rasterization_state.depthBiasConstantFactor = 1.0f;
  rasterization_state.depthBiasSlopeFactor = 1.0f;
  rasterization_state.lineWidth = 1.0f;

  VkGraphicsPipelineCreateInfo triangle_pipeline_CI = {
      .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
      .stageCount = static_cast<uint32_t>(shader_stages.size()),
      .pStages = shader_stages.data(),
      .pVertexInputState = &vertex_input_state,
      .pInputAssemblyState = &input_assembly_state,
      .pTessellationState = &tesselation_state,
      .pViewportState = &viewport_state,
      .pRasterizationState = &rasterization_state,
      .pMultisampleState = &multisample_state,
      .pDepthStencilState = &depth_stencil_state,
      .pColorBlendState = &color_blend_state,
      .pDynamicState = &dynamic_state,
      .layout = pipeline_layout.pipeline_layout(),
      .renderPass = VK_NULL_HANDLE,
  };
  bs::engine::wrappers::pipeline::Pipeline example_pipeline(
      m_engine.context()->device(), triangle_pipeline_CI);

  m_engine.run(&example_pipeline);
}
Triangle::~Triangle() {}
} // namespace bs::examples::triangle

int main() {
  spdlog::set_level(spdlog::level::trace);
  spdlog::set_pattern("[%^%l%$] %v");
  bs::examples::triangle::Triangle triangle;
}
