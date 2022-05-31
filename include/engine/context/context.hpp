#pragma once

#include "engine/utils/utils.hpp"

#include <memory>

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>

namespace bs::wrappers::allocated_image {
class AllocatedImage;
} // namespace bs::wrappers::allocated_image
struct VkInstance_T;
typedef struct VkInstance_T *VkInstance;
struct VkPhysicalDevice_T;
typedef struct VkPhysicalDevice_T *VkPhysicalDevice;
struct VkDevice_T;
typedef struct VkDevice_T *VkDevice;
struct VkQueue_T;
typedef struct VkQueue_T *VkQueue;
struct VkSurfaceKHR_T;
typedef struct VkSurfaceKHR_T *VkSurfaceKHR;
struct VkSwapchainKHR_T;
typedef struct VkSwapchainKHR_T *VkSwapchainKHR;
struct VkImage_T;
typedef struct VkImage_T *VkImage;
struct VkImageView_T;
typedef struct VkImageView_T *VkImageView;
struct VkCommandPool_T;
typedef struct VkCommandPool_T *VkCommandPool;
struct VkCommandBuffer_T;
typedef struct VkCommandBuffer_T *VkCommandBuffer;
struct VmaAllocator_T;
typedef struct VmaAllocator_T *VmaAllocator;

namespace bs::engine::context {
class Context {
public:
  Context();
  Context(const Context &) = delete;
  Context(Context &&) noexcept;
  Context &operator=(const Context &) = delete;
  Context &operator=(Context &&) = delete;

  ~Context();

  VkInstance instance() { return m_instance; };
  VkPhysicalDevice physical_Device() { return m_physical_device; };
  VkDevice device() { return m_device; };
  VkQueue queue() { return m_queue; };

private:
  std::vector<const char *> m_instance_extensions;
  std::vector<const char *> m_instance_layers;

  std::vector<const char *> m_device_extensions;

  VkInstance m_instance;
  VkPhysicalDevice m_physical_device;
  VkDevice m_device;
  VkQueue m_queue;
  uint32_t m_queue_family{0};
  VkSurfaceKHR m_surface;
  VkSwapchainKHR m_swapchain;
  std::vector<VkImage> m_swapchain_images;
  std::vector<VkImageView> m_swapchain_image_views;

  VkCommandPool m_command_pool;
  VkCommandBuffer m_command_buffer;

  std::unique_ptr<bs::wrappers::allocated_image::AllocatedImage *>
      m_depth_image;

  VmaAllocator m_allocator{};

  SDL_Window *m_window;
};
} // namespace bs::engine::context
