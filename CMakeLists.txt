cmake_minimum_required(VERSION 3.6.0)

project(voxigen VERSION 0.1.0)


file(GLOB_RECURSE voxigen_src CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${voxigen_src})

add_subdirectory(dep/glfw)

add_subdirectory(dep/glad)


#include directories

include_directories(src dep/glfw/include)

target_link_libraries(${PROJECT_NAME} glfw glad)