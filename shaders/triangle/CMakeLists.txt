find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin)

file(
  GLOB_RECURSE GLSL_SOURCE_FILES
  "${PROJECT_SOURCE_DIR}/shaders/triangle/*.frag"
  "${PROJECT_SOURCE_DIR}/shaders/triangle/*.vert"
  "${PROJECT_SOURCE_DIR}/shaders/triangle/*.comp"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "BUILDING SHADER")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${CMAKE_BINARY_DIR}/shaders/triangle/${FILE_NAME}.spv")
  message(STATUS ${GLSL})
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL}
  )
list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
  triangle_shaders
  DEPENDS ${SPIRV_BINARY_FILES}
)

set(SHADER_DIR=${CMAKE_CURRENT_BINARY_DIR})
