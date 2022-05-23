#include "context.hpp"

#include <algorithm>
#include <cstdint>
#include <exception>
#include <utils/utils.hpp>

#include <SDL.h>
#include <SDL_video.h>

#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan_core.h>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

namespace bs::engine::context {
Context::Context() {
  SDL_Init(SDL_INIT_EVERYTHING);
  m_window = SDL_CreateWindow("BS Engine (improved)", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 640, 480,
                              SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);

  VK_CHECK(volkInitialize());

  uint32_t instance_extension_count{0};
  SDL_Vulkan_GetInstanceExtensions(m_window, &instance_extension_count,
                                   nullptr);
  m_instance_extensions.resize(instance_extension_count);
  SDL_Vulkan_GetInstanceExtensions(m_window, &instance_extension_count,
                                   m_instance_extensions.data());
  m_instance_layers.push_back("VK_LAYER_KHRONOS_validation");

  VkApplicationInfo app_I = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName = "BS Engine",
      .applicationVersion = 1,
      .pEngineName = "BS Engine",
      .engineVersion = 1,
      .apiVersion = VK_API_VERSION_1_3,
  };
  VkInstanceCreateInfo instance_CI = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &app_I,
      .enabledLayerCount = static_cast<uint32_t>(m_instance_layers.size()),
      .ppEnabledLayerNames = m_instance_layers.data(),
      .enabledExtensionCount =
          static_cast<uint32_t>(m_instance_extensions.size()),
      .ppEnabledExtensionNames = m_instance_extensions.data(),
  };
  VK_CHECK(vkCreateInstance(&instance_CI, nullptr, &m_instance));

  volkLoadInstance(m_instance);

  SDL_Vulkan_CreateSurface(m_window, m_instance, &m_surface);

  std::vector<VkPhysicalDevice> physical_devices;
  uint32_t physical_devices_count{0};
  VK_CHECK(
      vkEnumeratePhysicalDevices(m_instance, &physical_devices_count, nullptr));
  physical_devices.resize(physical_devices_count);
  VK_CHECK(vkEnumeratePhysicalDevices(m_instance, &physical_devices_count,
                                      physical_devices.data()));

  {
    int i{0};
    for (auto vpd : physical_devices) {
      VkPhysicalDeviceProperties physical_device_properties;
      vkGetPhysicalDeviceProperties(vpd, &physical_device_properties);
      spdlog::trace("Physical device nr. {0}: {1}", i,
                    physical_device_properties.deviceName);
      i++;
    }
  }
  m_physical_device = physical_devices[0];
  VkPhysicalDeviceProperties physical_device_properties;
  vkGetPhysicalDeviceProperties(m_physical_device, &physical_device_properties);
  spdlog::info("Selected physical device: {0}",
               physical_device_properties.deviceName);

  m_device_extensions.push_back("VK_KHR_swapchain");
  m_device_extensions.push_back("VK_KHR_dynamic_rendering");
  VkPhysicalDeviceDynamicRenderingFeaturesKHR dynamic_rendering_feature{
      .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES,
      .dynamicRendering = VK_TRUE,
  };
  VkPhysicalDeviceFeatures2 device_features2 = {
    .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
    .pNext = &dynamic_rendering_feature,
  };
  const float &queue_priorities = {0.0f};
  VkDeviceQueueCreateInfo device_queue_CI = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .queueCount = 1,
      .pQueuePriorities = &queue_priorities,
  };
  VkDeviceCreateInfo device_CI = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .pNext = &device_features2,
      .queueCreateInfoCount = 1,
      .pQueueCreateInfos = &device_queue_CI,
      .enabledExtensionCount =
          static_cast<uint32_t>(m_device_extensions.size()),
      .ppEnabledExtensionNames = m_device_extensions.data(),
  };
  VK_CHECK(vkCreateDevice(m_physical_device, &device_CI, nullptr, &m_device));

  volkLoadDevice(m_device);

  const uint32_t &queue_family_indices = {1};
  VkSwapchainCreateInfoKHR swapchain_CI = {
      .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .surface = m_surface,
      .minImageCount = 3,
      .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,
      .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
      .imageExtent = {640, 480},
      .imageArrayLayers = 1,
      .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
      .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount = 1,
      .pQueueFamilyIndices = &queue_family_indices,
      .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode = VK_PRESENT_MODE_FIFO_KHR,
      .clipped = VK_TRUE,
  };

  VK_CHECK(
      vkCreateSwapchainKHR(m_device, &swapchain_CI, nullptr, &m_swapchain));

  VmaAllocatorCreateInfo allocator_CI = {
      .physicalDevice = m_physical_device,
      .device = m_device,
      .instance = m_instance,
  };
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
      .usage = VMA_MEMORY_USAGE_AUTO,
  };
  m_depth_image = std::make_unique<utils::AllocatedImage>(
      m_allocator, depth_image_CI, depth_image_allocation_CI);

  VkCommandPoolCreateInfo command_pool_CI = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .queueFamilyIndex = m_queue_family};
  VK_CHECK(vkCreateCommandPool(m_device, &command_pool_CI, nullptr,
                               &m_command_pool));
  VkCommandBufferAllocateInfo command_buffer_AI = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .commandPool = m_command_pool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = 1,
  };
  VK_CHECK(vkAllocateCommandBuffers(m_device, &command_buffer_AI,
                                    &m_command_buffer));
}
Context::~Context() {
  m_depth_image.reset();
  vkFreeCommandBuffers(m_device, m_command_pool, 1, &m_command_buffer);
  vkDestroyCommandPool(m_device, m_command_pool, nullptr);
  vmaDestroyAllocator(m_allocator);
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
