#include "utils.hpp"

namespace bs::utils {
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
} // namespace bs::utils
