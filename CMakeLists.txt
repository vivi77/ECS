cmake_minimum_required(VERSION 3.0)

set(LIB_NAME ecs_core)
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address,undefined")
endif(UNIX)

add_subdirectory(./lel_library)

add_subdirectory(./Utility)
add_subdirectory(./C)
add_subdirectory(./E)
add_subdirectory(./S)

file(GLOB SRCS *.cpp *.hh)

add_library(${LIB_NAME} SHARED ${C_SRCS} ${E_SRCS} ${S_SRCS} ${SRCS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIB_NAME} PUBLIC lel_lib)
if(UNIX)
  target_link_libraries(${LIB_NAME} PUBLIC dl stdc++fs)
endif(UNIX)
