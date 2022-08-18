#include "engine/engine.hpp"
#include "engine/utils/result/result.hpp"
#include <spdlog/spdlog.h>

#include <SDL2/SDL.h>
#include <vulkan/vulkan_core.h>

namespace bs::engine {
Engine::Engine() {}
Engine::~Engine() {}

bs::engine::utils::result::Result
bs::engine::Engine::run(wrappers::pipeline::Pipeline *_pipeline) {
  VkRenderingAttachmentInfo color_attachment = {
      .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
      .imageView = m_context.swapchain_image_views()[0],
      .imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .clearValue = {.color = {0, 0, 0, 0}}};
  VkRenderingAttachmentInfo depth_stencil_attachment = {
      .sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
      .imageView = m_context.depth_image()->image_view()};
  VkRenderingInfo rendering_info = {
      .sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
      .renderArea = {0, 0, 640, 480},
      .layerCount = 1,
      .colorAttachmentCount = 1,
      .pColorAttachments = &color_attachment,
  };

  VkCommandBufferBeginInfo cmdBufferBeginInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
  };

  VkFence fence;
  VkFenceCreateInfo fence_CI = {
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
  };
  VK_CHECK(vkCreateFence(m_context.device(), &fence_CI, nullptr, &fence));

  VkSemaphore semaphores[2];
  VkSemaphoreCreateInfo semaphore_CI = {
      .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
  VkPipelineStageFlags dstStageMask =
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  VkSubmitInfo submit_I = {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .pWaitSemaphores = &semaphores[0],
      .pWaitDstStageMask = &dstStageMask,
      .commandBufferCount = 1,
      .pCommandBuffers = m_context.command_buffer_ptr(),
      .signalSemaphoreCount = 1,
      .pSignalSemaphores = &semaphores[1],
  };

  uint32_t swapchain_image_index = 0;
  VkPresentInfoKHR present_I = {
      .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &semaphores[1],
      .swapchainCount = 1,
      .pSwapchains = m_context.swapchain_ptr(),
      .pImageIndices = &swapchain_image_index,
  };

  VK_CHECK(vkCreateSemaphore(m_context.device(), &semaphore_CI, nullptr,
                             &semaphores[0]));
  VK_CHECK(vkCreateSemaphore(m_context.device(), &semaphore_CI, nullptr,
                             &semaphores[1]));

  auto last_time = std::chrono::high_resolution_clock::now();
  VkClearColorValue clear_color = {1.0f, 1.0f, 1.0f, 1.0f};
  do {
    auto last_time = std::chrono::high_resolution_clock::now();
    handle_events();

    VK_CHECK(vkAcquireNextImageKHR(m_context.device(), m_context.swapchain(),
                                   1000000000, semaphores[0], fence,
                                   &swapchain_image_index));

    VK_CHECK(
        vkBeginCommandBuffer(m_context.command_buffer(), &cmdBufferBeginInfo));
    vkCmdBeginRendering(m_context.command_buffer(), &rendering_info);
    vkCmdBindPipeline(m_context.command_buffer(),
                      VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline->pipeline());

    vkCmdDraw(m_context.command_buffer(), 3, 1, 0, 0);
    vkCmdEndRendering(m_context.command_buffer());
    VK_CHECK(vkEndCommandBuffer(m_context.command_buffer()));

    VK_CHECK(vkQueueSubmit(m_context.queue(), 1, &submit_I, fence));

    VK_CHECK(vkQueueWaitIdle(m_context.queue()));
    VK_CHECK(vkQueuePresentKHR(m_context.queue(), &present_I));
    VK_CHECK(vkQueueWaitIdle(m_context.queue()));
    auto current_time = std::chrono::high_resolution_clock::now();

    auto delta_time =
        std::chrono::duration<float, std::chrono::seconds::period>(
            current_time - last_time)
            .count();
    auto fps = 1.0f / delta_time;
    spdlog::info("Frametime: {0}\nFPS: {1}", delta_time, fps);
  } while (m_running);
  return utils::result::BS_SUCCESS;
}
bs::engine::utils::result::Result bs::engine::Engine::handle_events() {
  SDL_Event *e = new SDL_Event;
  while (SDL_PollEvent(e)) {
    switch (e->type) {
    case SDL_QUIT:
      m_running = false;
    }
  }
  delete e;
  return utils::result::BS_SUCCESS;
}

} // namespace bs::engine
