#include "init.hpp"
#include <vulkan/vulkan_core.h>

namespace bs::utils::init_structs {
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
} // namespace bs::utils::init_structs
