#include "pipeline.hpp"
#include <vulkan/vulkan_core.h>

namespace bs::wrapper::pipeline {
Pipeline::Pipeline(Pipeline &pipeline) {
  m_pipeline = *pipeline.pipeline_ptr();
}
Pipeline::~Pipeline() {}
} // namespace bs::wrapper::pipeline
