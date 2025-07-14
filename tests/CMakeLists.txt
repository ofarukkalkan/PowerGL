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

add_test(NAME vertexcoloredcube_headless
          COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run_vertexcoloredcube_headless.sh
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

