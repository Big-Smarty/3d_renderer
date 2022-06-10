#pragma once

struct VkDevice_T;
typedef struct VkDevice_T *VkDevice;
struct VkShaderModule_T;
typedef struct VkShaderModule_T *VkShaderModule;
struct VkShaderModuleCreateInfo;

namespace bs::engine::wrappers::shader_module {
class ShaderModule {
public:
  ShaderModule(const char *path, VkDevice &device);
  ShaderModule(const ShaderModule &) = delete;
  ShaderModule(ShaderModule &&) noexcept;
  ShaderModule &operator=(const ShaderModule &) = delete;
  ShaderModule &operator=(ShaderModule &&) = delete;
  ~ShaderModule();

private:
  const char *m_path;
  VkDevice &m_device;
  VkShaderModule m_shader_module;
};
} // namespace bs::engine::wrappers::shader_module
