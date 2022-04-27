#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <utils/utils.hpp>
#include <vector>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

namespace bs::engine::context {
class Context {
public:
  Context();
  ~Context();

private:
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

  utils::AllocatedImage *m_depth_image;

  VmaAllocator m_allocator;

  SDL_Window *m_window;
};
} // namespace bs::engine::context
