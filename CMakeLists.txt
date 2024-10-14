cmake_minimum_required(VERSION 3.6.0)

project(voxigen VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)


file(GLOB_RECURSE voxigen_src CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(${PROJECT_NAME} ${voxigen_src})

add_subdirectory(dep/glfw)
add_subdirectory(dep/glad)
add_subdirectory(dep/spdlog)

#include directories

include_directories(src dep/glfw/include dep/spdlog/include)


target_link_libraries(${PROJECT_NAME} glfw glad spdlog)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake)
add_dependencies(${PROJECT_NAME} copy_assets)