#pragma once

#define VK_NO_PROTOTYPES
#include "engine/wrappers/allocated_image/allocated_image.hpp"
#include "engine/utils/utils.hpp"

#include <memory>

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>

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

  std::unique_ptr<bs::wrappers::allocated_image::AllocatedImage> m_depth_image;

  VmaAllocator m_allocator{};

  SDL_Window *m_window;
};
} // namespace bs::engine::context