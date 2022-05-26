#pragma once

namespace bs::engine::camera {
  class Camera {
    public:
      Camera();
      Camera(const Camera &) = delete;
      Camera(Camera &&) noexcept;
      Camera &operator=(const Camera &) = delete;
      Camera &operator=(Camera &&) = delete;

      ~Camera();
  };
}
