cmake_minimum_required(VERSION 3.04)
set(CMAKE_CXX_STANDARD 17)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g3 -fsanitize=address,undefined -Wl,--no-undefined")
endif(UNIX)

set(LIBLIST meta Log CLIParser OSDLLoader Threadpool)
foreach(LIBDIR ${LIBLIST})
  add_subdirectory(${LIBDIR})
endforeach()

file(GLOB HDRS *.hpp)

set(UTILS_NAME lel_utils)
add_library(${UTILS_NAME} INTERFACE)
target_include_directories(${UTILS_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${UTILS_NAME} INTERFACE ${HDRS})

set(LIB_NAME lel_lib)
add_library(${LIB_NAME} INTERFACE)
target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIB_NAME} INTERFACE ${LIBLIST})
target_sources(${LIB_NAME} INTERFACE ${HDRS})

if(LEL_TEST)
  add_subdirectory(./googletest)
  add_subdirectory(./test)
endif(LEL_TEST)
if(LEL_SAMPLE)
  add_subdirectory(./sample)
endif(LEL_SAMPLE)
