cmake_minimum_required(VERSION 3.0)

project(dll_test)

#https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
macro(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    get_filename_component(CHILD_EXT ${child} EXT)
    if(IS_DIRECTORY ${curdir}/${child} AND NOT CHILD_EXT STREQUAL ".ignore")
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

set(OUTPUT_LOCATION ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_LOCATION})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LOCATION}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LOCATION}/lib)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

set(NAME dll_test)

set(CMAKE_CXX_STANDARD 17)

set(INSTALL_FOLDER ${CMAKE_SOURCE_DIR}/install/${CMAKE_SYSTEM_NAME})
set(LIBRARY_INSTALL_DIR ${INSTALL_FOLDER}/lib)
set(INCLUDE_INSTALL_DIR ${INSTALL_FOLDER}/include)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "-g3 -DDEBUG -fsanitize=address,undefined")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wl,--no-undefined")
endif(UNIX)

add_subdirectory(./lel_library)

include(GenerateExportHeader)
add_subdirectory(./Utility)
add_subdirectory(./Entity)
add_subdirectory(./C)
add_subdirectory(./E)
add_subdirectory(./S)

set(SRCS
  main.cpp
  Core.cpp
  FileSearcher.cpp
  StartupLoader.cpp
  )

set(HDRS
  Core.hh
  FileSearcher.hh
  StartupLoader.hh
  CoreSystemData.hh
  )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeModules)
if (CMAKE_COMPILER_IS_GNUCXX)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  find_program(lcov_found NAMES lcov)
  if (lcov_found)
    setup_target_for_coverage(NAME ${NAME}_coverage
      EXECUTABLE ${NAME} coverage)
  else()
    message(STATUS "lcov not found")
  endif()
endif()

add_executable(${NAME} ${SRCS} ${HDRS})
target_link_libraries(${NAME} PUBLIC
  lel_lib
  EntityLogic
  EManager
  CManager
  CoreEvent
  CManagerEvent)
target_include_directories(${NAME} PUBLIC
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR})

if(UNIX)
  if (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${NAME} PUBLIC gcov)
  endif()
  target_link_libraries(${NAME} PUBLIC dl stdc++fs)
endif(UNIX)


#install(TARGETS ${NAME}
#  RUNTIME DESTINATION ${INSTALL_FOLDER}
#  ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
#  LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
#  PRIVATE_HEADER DESTINATION ${INCLUDE_INSTALL_DIR}
#  PUBLIC_HEADER DESTINATION ${INSTALL_FOLDER})
#install(FILES ${HDRS} DESTINATION ${INCLUDE_INSTALL_DIR})
