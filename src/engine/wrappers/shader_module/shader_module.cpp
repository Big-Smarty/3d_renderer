#include "engine/wrappers/shader_module/shader_module.hpp"
#include "engine/utils/init_structs/init_structs.hpp"
#include "engine/utils/utils.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

namespace bs::engine::wrappers::shader_module {
ShaderModule::ShaderModule(const char *path, const VkDevice &device)
    : m_device(device) {
  std::vector<char> shader_content;
  if (std::filesystem::exists(path)) {
    spdlog::trace("{0} found", path);
  } else {
    spdlog::error("{0} not found!", path);
    exit(-1);
  }
  std::ifstream shader_file(path, std::ios::binary | std::ios::ate);
  if (!shader_file.is_open()) {
    spdlog::error("Failed to open shader file: {0}", path);
    exit(-1);
  }
  shader_content.resize(shader_file.tellg());
  shader_file.seekg(0);
  shader_file.read(shader_content.data(), shader_content.size());
  shader_file.close();

  auto shader_module_CI =
      bs::engine::utils::init_structs::make_info<VkShaderModuleCreateInfo>();
  shader_module_CI.codeSize = shader_content.size();
  shader_module_CI.pCode = reinterpret_cast<uint32_t *>(shader_content.data());
  VK_CHECK(vkCreateShaderModule(m_device, &shader_module_CI, nullptr,
                                &m_shader_module));
}
ShaderModule::~ShaderModule() {
  vkDestroyShaderModule(m_device, m_shader_module, nullptr);
}
} // namespace bs::engine::wrappers::shader_module
