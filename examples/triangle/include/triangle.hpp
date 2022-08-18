#pragma once
#define VK_NO_PROTOTYPES
#include "engine/engine.hpp"
#include "engine/wrappers/pipeline/pipeline.hpp"

namespace bs::examples::triangle {
class Triangle {
public:
  Triangle();
  ~Triangle();

private:
  bs::engine::Engine m_engine;
};
} // namespace bs::examples::triangle
