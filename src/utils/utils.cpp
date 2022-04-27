#include "utils.hpp"

namespace bs::utils {
AllocatedImage::AllocatedImage(VmaAllocator *_allocator,
                               VkImageCreateInfo *_image_create_info,
                               VmaAllocationCreateInfo *_allocation_create_info,
                               VkImage *_image,
                               VmaAllocationInfo *_allocation_info) {
  m_allocator = *_allocator;
  vmaCreateImage(m_allocator, _image_create_info, _allocation_create_info,
                 _image, &m_allocation, _allocation_info);
}
AllocatedImage::~AllocatedImage() {
  vmaDestroyImage(m_allocator, m_image, m_allocation);
}
} // namespace bs::utils
