struct VkImageCreateInfo;
struct VmaAllocationCreateInfo;
struct VkImage_T;
typedef struct VkImage_T *VkImage;
struct VmaAllocator_T;
typedef struct VmaAllocator_T *VmaAllocator;
struct VmaAllocation_T;
typedef struct VmaAllocation_T *VmaAllocation;

namespace bs::wrappers::allocated_image {
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
} // namespace bs::wrappers::allocated_image
