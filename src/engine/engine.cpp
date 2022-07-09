#include "engine/engine.hpp"
#include "engine/utils/result/result.hpp"
#include <spdlog/spdlog.h>

#include "volk.h"
#include <SDL2/SDL.h>

namespace bs::engine {
Engine::Engine() { run(); }
Engine::~Engine() {}

bs::engine::utils::result::Result bs::engine::Engine::run() {
  VkRenderingAttachmentInfo color_attachment = {
      .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
      .imageView = m_context.swapchain_image_views()[0],
      .imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .clearValue = {.color = {0, 0, 0, 0}}};
  VkRenderingAttachmentInfo depth_stencil_attachment = {
      .sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
      //.imageView =
  };
  VkRenderingInfo rendering_info = {
      .sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
      .renderArea = {0, 0, 640, 480},
      .layerCount = 1,
      .colorAttachmentCount = 1,
      .pColorAttachments = &color_attachment,
  };
  do {
    handle_events();

    vkCmdBeginRendering(m_context.command_buffer(), &rendering_info);

    vkCmdEndRendering(m_context.command_buffer());
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
  return utils::result::BS_SUCCESS;
}

} // namespace bs::engine
