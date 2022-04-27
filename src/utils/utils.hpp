#pragma once

#include <spdlog/spdlog.h>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

#define VK_CHECK(x)                                                            \
  {                                                                            \
    auto res = x;                                                              \
    if (res == 0) {                                                            \
      spdlog::debug("{0}: {1}", #x, res);                                      \
    } else {                                                                   \
      spdlog::error("{0}: {1}! Exiting...", #x, res);                          \
      exit(res);                                                               \
    }                                                                          \
  }

namespace bs::utils {
struct AllocatedImage {
public:
  AllocatedImage(VmaAllocator *_allocator,
                 VkImageCreateInfo *_image_create_info,
                 VmaAllocationCreateInfo *_allocation_create_info,
                 VkImage *_image, VmaAllocationInfo *_allocation_info);
  ~AllocatedImage();

  VkImage *image() { return &m_image; };
  VmaAllocation allocation() { return m_allocation; };

private:
  VkImage m_image;
  VmaAllocation m_allocation;

  VmaAllocator m_allocator;
};
} // namespace bs::utils
