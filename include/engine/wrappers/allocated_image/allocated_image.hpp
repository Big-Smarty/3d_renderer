#pragma once

#include <vulkan/vulkan_core.h>
#include <vk_mem_alloc.h>

namespace bs::wrappers::allocated_image {
struct AllocatedImage {
public:
  AllocatedImage(VmaAllocator _allocator,
                 const VkImageCreateInfo &_image_create_info,
                 const VmaAllocationCreateInfo &_allocation_create_info,
                 VkDevice &_device);
  ~AllocatedImage();

  VkImage *image() { return &m_image; };
  VmaAllocation allocation() { return m_allocation; };

private:
  VkImage m_image;
  VkImageView m_image_view;
  VmaAllocation m_allocation;

  VmaAllocator m_allocator;
};
} // namespace bs::wrappers::allocated_image
