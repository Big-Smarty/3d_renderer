#include "engine/wrappers/allocated_image/allocated_image.hpp"
#include "engine/utils/utils.hpp"
#include <vulkan/vulkan_core.h>

namespace bs::wrappers::allocated_image {
AllocatedImage::AllocatedImage(
    VmaAllocator _allocator, const VkImageCreateInfo &_image_create_info,
    const VkImageViewCreateInfo &_image_view_create_info,
    const VmaAllocationCreateInfo &_allocation_create_info, VkDevice &_device)
    : m_device(_device) {
  m_allocator = _allocator;
  VK_CHECK(vmaCreateImage(m_allocator, &_image_create_info,
                          &_allocation_create_info, &m_image, &m_allocation,
                          nullptr));
  if (m_device == nullptr) {
    spdlog::error("Device is nullptr, therefor no image view can be created!");
    exit(-1);
  } else {
    VkImageViewCreateInfo image_view_CI = _image_view_create_info;
    image_view_CI.image = m_image;
    VK_CHECK(
        vkCreateImageView(m_device, &image_view_CI, nullptr, &m_image_view));
  }
}
AllocatedImage::~AllocatedImage() {
  vkDestroyImageView(m_device, m_image_view, nullptr);
  vmaDestroyImage(m_allocator, m_image, m_allocation);
}
} // namespace bs::wrappers::allocated_image
