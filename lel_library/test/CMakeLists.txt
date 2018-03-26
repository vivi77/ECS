set(TEST_NAME test_suite)

file(GLOB TEST_SRCS *.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeModules)
if (CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  find_program(lcov_found NAMES lcov)
  if (lcov_found)
    setup_target_for_coverage(NAME ${TEST_NAME}_coverage
      EXECUTABLE ${TEST_NAME} coverage)
  else()
    message(STATUS "lcov not found")
  endif()
endif()

add_executable(${TEST_NAME} ${TEST_SRCS})
target_include_directories(${TEST_NAME} PUBLIC ../googletest/googletest/include)
target_link_libraries(${TEST_NAME} gtest_main gmock_main dl gcov lel_lib)
