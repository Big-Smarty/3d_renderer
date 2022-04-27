#pragma once

#include "engine/context/context.hpp"

namespace bs::engine {
  class Engine {
    public:
      Engine();
      ~Engine();

    private:
      context::Context m_context;
  };
}
