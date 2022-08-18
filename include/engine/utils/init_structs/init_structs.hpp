#pragma once

struct VkShaderModule_T;
typedef struct VkShaderModule_T *VkShaderModule;

namespace bs::engine::utils::init_structs {
template <typename T> T make_info();
}
