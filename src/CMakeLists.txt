add_subdirectory("engine")
add_subdirectory("utils")

add_executable(example main.cpp)
target_link_libraries(example engine)
