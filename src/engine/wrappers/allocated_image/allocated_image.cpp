#include "engine/wrappers/allocated_image/allocated_image.hpp"
#include "engine/utils/utils.hpp"

#include <vk_mem_alloc.h>

namespace bs::wrappers::allocated_image {
AllocatedImage::AllocatedImage(
    VmaAllocator _allocator, const VkImageCreateInfo &_image_create_info,
    const VmaAllocationCreateInfo &_allocation_create_info) {
  m_allocator = _allocator;
  VK_CHECK(vmaCreateImage(m_allocator, &_image_create_info,
                          &_allocation_create_info, &m_image, &m_allocation,
                          nullptr));
}
AllocatedImage::~AllocatedImage() {
  vmaDestroyImage(m_allocator, m_image, m_allocation);
}
} // namespace bs::wrappers::allocated_image
