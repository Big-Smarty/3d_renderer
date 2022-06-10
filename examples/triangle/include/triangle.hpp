#pragma once
#include "engine/engine.hpp"

namespace bs::engine::wrappers::shader_module {
  struct ShaderModule;
}

namespace bs::examples::triangle {
class Triangle {
public:
  Triangle();
  ~Triangle();

private:
  std::vector<bs::engine::wrappers::shader_module::ShaderModule> m_shader_modules;
};
} // namespace bs::examples::triangle
