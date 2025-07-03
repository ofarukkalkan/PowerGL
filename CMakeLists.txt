cmake_minimum_required(VERSION 3.10)
project(PowerGL C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(EXPAT REQUIRED)
set(POWERGL_WINDOW_BACKEND "SDL" CACHE STRING "Window backend implementation (SDL or GLFW)")
set_property(CACHE POWERGL_WINDOW_BACKEND PROPERTY STRINGS SDL GLFW)

if(POWERGL_WINDOW_BACKEND STREQUAL "GLFW")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    set(BACKEND_SOURCES src/window/window_glfw.c)
    add_definitions(-DPOWERGL_BACKEND_GLFW)
    list(APPEND BACKEND_LIBS ${GLFW_LIBRARIES})
    include_directories(${GLFW_INCLUDE_DIRS})
else()
    set(BACKEND_SOURCES src/window/window_sdl.c)
    add_definitions(-DPOWERGL_BACKEND_SDL)
endif()

# EGL support is provided by FindOpenGL in modern CMake versions.  Using
# a separate find_package(EGL) call fails on systems without a dedicated
# FindEGL.cmake module, so rely on the variables exported by FindOpenGL
# instead.

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
    ${OPENGL_EGL_INCLUDE_DIR}
    
)

set(POWERGL_WINDOW_SOURCES
    src/window/window.c
    src/window/headless.c
    ${BACKEND_SOURCES}
)

add_library(powergl
    src/powergl.c
    ${POWERGL_WINDOW_SOURCES}
    src/rendering/object.c
    src/rendering/pipeline.c
    src/rendering/visualscene.c
    src/rendering/dae2object.c
    src/rendering/objectlibrary.c
    src/rendering/3dtext.c
    src/ui/scene_hierarchy.c
    src/ui/nuklear_impl.c
    src/math/mat4x4.c
    src/math/vec3.c
    src/math/intersect.c
    src/collada/importer.c
    src/collada/exporter.c
    src/collada/dom_connector.c
    src/collada/parse_utils.c
    src/collada/core/core.c
    src/png/png_loader.c
)

target_link_libraries(powergl PUBLIC
    ${SDL2_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARIES}
    ${OPENGL_egl_LIBRARY}
    ${PNG_LIBRARIES}
    ${EXPAT_LIBRARIES}
    m
    ${BACKEND_LIBS}
    
)

target_include_directories(powergl PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

enable_testing()
add_subdirectory(tests)

