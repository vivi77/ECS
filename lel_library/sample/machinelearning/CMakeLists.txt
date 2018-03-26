set(EXEC_NAME machinelearning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address,undefined")

set(ML_SRCS
  ML_Data.cpp
  ML_ANode.cpp
  ML_Input.cpp
  ML_Output.cpp
  ML_Circuit.cpp
  )

set(ML_HDRS
  ML_Data.hh
  ML_ANode.hh
  ML_Input.hh
  ML_Output.hh
  ML_Circuit.hh
  ../../ANode.hpp
  )

set(ML_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}
  ../../)

add_executable(${EXEC_NAME} main.cpp ${ML_SRCS} ${ML_HDRS})
target_include_directories(${EXEC_NAME} PUBLIC ${ML_DIR})
target_link_libraries(${EXEC_NAME} PUBLIC lel_utils)

if (ML_TEST)
  add_subdirectory(unit_tests)
endif()
