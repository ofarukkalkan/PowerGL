# CMake configuration for unit tests

find_package(GTest REQUIRED)

# Build GoogleTest executables
add_executable(gtest_math gtest_math.cpp)
target_compile_definitions(gtest_math PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(gtest_math PRIVATE powergl GTest::gtest_main)

gtest_discover_tests(gtest_math)

add_executable(gtest_collada gtest_collada.cpp)
target_compile_definitions(gtest_collada PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(gtest_collada PRIVATE powergl GTest::gtest_main)

gtest_discover_tests(gtest_collada)

add_executable(gtest_intersect gtest_intersect.cpp)
target_compile_definitions(gtest_intersect PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(gtest_intersect PRIVATE powergl GTest::gtest_main)

gtest_discover_tests(gtest_intersect)

add_executable(vertexcoloredcube_demo vertexcoloredcube_demo.c)
target_compile_definitions(vertexcoloredcube_demo PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(vertexcoloredcube_demo PRIVATE powergl)

add_executable(flat_demo flat_demo.c)
target_compile_definitions(flat_demo PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(flat_demo PRIVATE powergl)

add_executable(gouraud_demo gouraud_demo.c)
target_compile_definitions(gouraud_demo PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(gouraud_demo PRIVATE powergl)

add_executable(lambert_demo lambert_demo.c)
target_compile_definitions(lambert_demo PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(lambert_demo PRIVATE powergl)

add_executable(blinnphong_demo blinnphong_demo.c)
target_compile_definitions(blinnphong_demo PRIVATE TEST_SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(blinnphong_demo PRIVATE powergl)

add_test(NAME vertexcoloredcube_headless
          COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run_vertexcoloredcube_headless.sh
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

