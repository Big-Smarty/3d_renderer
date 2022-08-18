#pragma once

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

namespace bs::wrappers::allocated_image {
struct AllocatedImage {
public:
  AllocatedImage(VmaAllocator _allocator,
                 const VkImageCreateInfo &_image_create_info,
                 const VkImageViewCreateInfo &_image_view_create_info,
                 const VmaAllocationCreateInfo &_allocation_create_info,
                 VkDevice &_device);
  ~AllocatedImage();

  VkImage image() { return m_image; }
  VkImageView image_view() { return m_image_view; }
  VkImage *image_ptr() { return &m_image; }
  VkImageView *image_view_ptr() { return &m_image_view; }
  VmaAllocation allocation() { return m_allocation; }

private:
  VkImage m_image = nullptr;
  VkImageView m_image_view = nullptr;

  VmaAllocation m_allocation = nullptr;
  VmaAllocator m_allocator = nullptr;

  VkDevice &m_device;
};
} // namespace bs::wrappers::allocated_image
