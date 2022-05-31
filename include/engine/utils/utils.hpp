#pragma once

#include <spdlog/spdlog.h>
#define VK_NO_PROTOTYPES

#define VK_CHECK(x)                                                            \
  {                                                                            \
    auto res = x;                                                              \
    if (res == 0) {                                                            \
      spdlog::debug("{0}: {1}", #x, res);                                      \
    } else {                                                                   \
      spdlog::error("{0}: {1} Exiting...", #x, res);                           \
      exit(res);                                                               \
    }                                                                          \
  }
