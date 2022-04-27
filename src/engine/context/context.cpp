#include "context.hpp"

#include <utils/utils.hpp>

#include <SDL.h>
#include <SDL_video.h>
#include <VkBootstrap.h>

#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan_core.h>

namespace bs::engine::context {
Context::Context() {
  SDL_Init(SDL_INIT_EVERYTHING);
  m_window = SDL_CreateWindow("BS Engine (improved)", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 640, 480,
                              SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);

  vkb::InstanceBuilder vkb_instance_builder;
  vkb::Instance vkb_instance =
      vkb_instance_builder.set_app_name("BS Engine (improved)")
          .request_validation_layers(1)
          .require_api_version(1, 3)
          .build()
          .value();
  m_instance = vkb_instance.instance;

  SDL_Vulkan_CreateSurface(m_window, m_instance, &m_surface);

  vkb::PhysicalDeviceSelector vkb_selector{vkb_instance};
  vkb::PhysicalDevice vkb_physical_device =
      vkb_selector.set_minimum_version(1, 3)
          .set_surface(m_surface)
          .select_first_device_unconditionally()
          .add_required_extension("VK_KHR_swapchain")
          .add_required_extension("VK_KHR_dynamic_rendering")
          .select()
          .value();
  m_physical_device = vkb_physical_device.physical_device;

  VkPhysicalDeviceDynamicRenderingFeaturesKHR
      dynamic_rendering_feature{
          .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES,
          .dynamicRendering = VK_TRUE,
      };

  vkb::DeviceBuilder vkb_device_builder(vkb_physical_device);
  vkb::Device vkb_device =
      vkb_device_builder.add_pNext(&dynamic_rendering_feature).build().value();

  m_device = vkb_device.device;

  VkPhysicalDeviceProperties physical_device_properties{};
  vkGetPhysicalDeviceProperties(m_physical_device, &physical_device_properties);
  spdlog::info("\nSelected physical device: {0}",
               physical_device_properties.deviceName);

  m_queue = vkb_device.get_queue(vkb::QueueType::graphics).value();
  m_queue_family = vkb_device.get_queue_index(vkb::QueueType::graphics).value();

  vkb::SwapchainBuilder vkb_swapchain_builder(m_physical_device, m_device,
                                              m_surface);
  vkb::Swapchain vkb_swapchain =
      vkb_swapchain_builder.use_default_format_selection()
          .set_desired_present_mode(VK_PRESENT_MODE_IMMEDIATE_KHR)
          .set_desired_extent(640, 480)
          .build()
          .value();

  VkSurfaceCapabilitiesKHR surface_capabilities{};
  VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
      m_physical_device, m_surface, &surface_capabilities));
  vkb_swapchain.image_count = surface_capabilities.maxImageCount;
  m_swapchain = vkb_swapchain.swapchain;
  m_swapchain_images = vkb_swapchain.get_images().value();
  m_swapchain_image_views = vkb_swapchain.get_image_views().value();

  VmaAllocatorCreateInfo allocator_CI = {.physicalDevice = m_physical_device,
                                         .device = m_device,
                                         .instance = m_instance};
  VK_CHECK(vmaCreateAllocator(&allocator_CI, &m_allocator));

  VkImageCreateInfo depth_image_CI = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .imageType = VK_IMAGE_TYPE_2D,
      .format = VK_FORMAT_D32_SFLOAT,
      .extent =
          {
              .width = 640,
              .height = 480,
              .depth = 1,
          },
      .mipLevels = 1,
      .arrayLayers = 1,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .tiling = VK_IMAGE_TILING_OPTIMAL,
      .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT};
  VmaAllocationCreateInfo depth_image_allocation_CI = {
      .usage = VMA_MEMORY_USAGE_GPU_ONLY,
      .requiredFlags =
          VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
  };
  *m_depth_image = utils::AllocatedImage(&m_allocator, &depth_image_CI,
                                         &depth_image_allocation_CI,
                                         m_depth_image->image(), nullptr);

  VkCommandPoolCreateInfo command_pool_CI = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .queueFamilyIndex = m_queue_family};
}
Context::~Context() {
  for (auto iv : m_swapchain_image_views) {
    vkDestroyImageView(m_device, iv, nullptr);
  }

  vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
  vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
  vkDestroyDevice(m_device, nullptr);
  vkDestroyInstance(m_instance, nullptr);

  SDL_DestroyWindow(m_window);
  SDL_Quit();
}
} // namespace bs::engine::context
