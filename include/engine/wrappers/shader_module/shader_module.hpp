#pragma once

#include <vulkan/vulkan_core.h>

namespace bs::engine::wrappers::shader_module {
class ShaderModule {
public:
  ShaderModule(const char *path, const VkDevice &device);
  ShaderModule(const ShaderModule &) = delete;
  ShaderModule(ShaderModule &&) noexcept;
  ShaderModule &operator=(const ShaderModule &) = delete;
  ShaderModule &operator=(ShaderModule &&) = delete;
  ~ShaderModule();

  VkShaderModule shader_module() { return m_shader_module; }

private:
  const char *m_path;
  const VkDevice &m_device;
  VkShaderModule m_shader_module;
};
} // namespace bs::engine::wrappers::shader_module
