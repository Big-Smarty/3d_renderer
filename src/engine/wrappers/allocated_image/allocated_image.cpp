#include "engine/wrappers/allocated_image/allocated_image.hpp"
#include "engine/utils/utils.hpp"

#include <vk_mem_alloc.h>

namespace bs::wrappers::allocated_image {
AllocatedImage::AllocatedImage(
    VmaAllocator _allocator, const VkImageCreateInfo &_image_create_info,
    const VmaAllocationCreateInfo &_allocation_create_info, VkDevice &_device) {
  m_allocator = _allocator;
  VK_CHECK(vmaCreateImage(m_allocator, &_image_create_info,
                          &_allocation_create_info, &m_image, &m_allocation,
                          nullptr));
  VkImageViewCreateInfo image_view_CI = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .image = m_image,
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = VK_FORMAT_B8G8R8A8_SRGB,
      .components = {VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
                     VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A},
      .subresourceRange =
          {
              .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
              .baseMipLevel = 0,
              .levelCount = 1,
              .baseArrayLayer = 0,
              .layerCount = 1,
          },
  };
  if (_device == nullptr) {
    spdlog::error("Device is nullptr, therefor no image view can be created!");
    exit(-1);
  } else {
    VK_CHECK(
        vkCreateImageView(_device, &image_view_CI, nullptr, &m_image_view));
  }
}
AllocatedImage::~AllocatedImage() {
  vmaDestroyImage(m_allocator, m_image, m_allocation);
}
} // namespace bs::wrappers::allocated_image
