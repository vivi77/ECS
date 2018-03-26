cmake_minimum_required(VERSION 3.0)

set(EXEC_NAME unit_tests)

set(SRCS
  main.cpp
  ./UT.cpp
  ${ML_SRCS}
  )

set(HDRS
  ${ML_HDRS}
  )

set(HDRS_DIR
  ${ML_DIR}
  )

add_executable(${EXEC_NAME} ${SRCS} ${HDRS})
target_include_directories(${EXEC_NAME} PUBLIC ${HDRS_DIR})
target_link_libraries(${EXEC_NAME} gtest_main gmock_main)
