cmake_minimum_required(VERSION 3.10)
project(PowerGL C)

set(CMAKE_C_STANDARD 99)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(EXPAT REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(EGL REQUIRED egl)

include_directories(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS} ${EGL_INCLUDE_DIRS})

add_library(powergl
    src/powergl.c
    src/window/window.c
    src/window/headless.c
    src/window/window_sdl.c
    src/window/window_glfw.c
    src/rendering/object.c
    src/rendering/pipeline.c
    src/rendering/visualscene.c
    src/rendering/dae2object.c
    src/rendering/objectlibrary.c
    src/rendering/3dtext.c
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
    ${EGL_LIBRARIES}
    ${PNG_LIBRARIES}
    ${EXPAT_LIBRARIES}
)

target_include_directories(powergl PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

