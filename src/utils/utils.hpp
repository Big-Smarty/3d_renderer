#pragma once

#include <spdlog/spdlog.h>
#define VK_NO_PROTOTYPES
#include <vk_mem_alloc.h>
#include <volk.h>

#define VK_CHECK(x)                                                            \
  {                                                                            \
    auto res = x;                                                              \
    if (res == 0) {                                                            \
      spdlog::debug("{0}: {1}", #x, res);                                      \
    } else {                                                                   \
      spdlog::error("{0}: {1} Exiting...", #x, res);                           \
      exit(res);                                                               \
    }                                                                          \
  }

namespace bs::utils {
struct AllocatedImage {
public:
  AllocatedImage(VmaAllocator _allocator,
                 const VkImageCreateInfo &_image_create_info,
                 const VmaAllocationCreateInfo &_allocation_create_info);
  ~AllocatedImage();

  VkImage *image() { return &m_image; };
  VmaAllocation allocation() { return m_allocation; };

private:
  VkImage m_image;
  VmaAllocation m_allocation;

  VmaAllocator m_allocator;
};
} // namespace bs::utils
