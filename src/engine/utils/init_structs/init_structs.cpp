#include "engine/utils/init_structs/init_structs.hpp"
#include <vector>

#define VK_NO_PROTOTYPES
#include <vulkan/vulkan_core.h>

namespace bs::engine::utils::init_structs {
template <> VkApplicationInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
          .pApplicationName = "",
          .applicationVersion = 1,
          .pEngineName = "",
          .engineVersion = 1,
          .apiVersion = VK_API_VERSION_1_3};
}
template <> VkImageCreateInfo make_info() {
  return {
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .imageType = VK_IMAGE_TYPE_2D,
      .mipLevels = 1,
      .arrayLayers = 1,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .tiling = VK_IMAGE_TILING_OPTIMAL,
  };
}
template <> VkInstanceCreateInfo make_info() {
  return {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
  };
}
template <> VkPipelineShaderStageCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO};
}
template <> VkPipelineVertexInputStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
}
template <> VkPipelineInputAssemblyStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
}
template <> VkPipelineTessellationStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO};
}
template <> VkPipelineViewportStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
}
template <> VkPipelineRasterizationStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
}
template <> VkPipelineMultisampleStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
}
template <> VkPipelineDepthStencilStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
}
template <> VkPipelineColorBlendStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
}
template <> VkPipelineDynamicStateCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
}
template <> VkPipelineLayoutCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
}
template <> VkShaderModuleCreateInfo make_info() {
  return {.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};
}
} // namespace bs::engine::utils::init_structs
