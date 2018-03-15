cmake_minimum_required(VERSION 3.0)
project(dll_test)

#https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
macro(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
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
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
  if (DEBUG)
    message(STATUS "DEBUG ACTIVATED")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
  else(DEBUG)
    message(STATUS "DEBUG DEACTIVATED")
  endif(DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
endif(UNIX)

add_subdirectory(./C)
add_subdirectory(./E)
add_subdirectory(./S)

set(SRCS
  main.cpp
  Core.cpp
  FileSearcher.cpp
  ../dlloader/LinuxDLLoader.cpp
  ../dlloader/WindowsDLLoader.cpp
  ../log/Log.cpp
  )

set(HDRS
  Core.hh
  FileSearcher.hh
  ../dlloader/DLLoader.hpp
  ../dlloader/LinuxDLLoader.hh
  ../dlloader/OSLoader.hpp
  ../dlloader/WindowsDLLoader.hh
  ../log/Log.hh
  ../meta/conditional_os.hpp
  )

add_executable(${NAME} ${SRCS} ${HDRS})
target_link_libraries(${NAME} PUBLIC EManager CoreEvent)
target_include_directories(${NAME} PUBLIC C S E E/CoreEvent ${CMAKE_BINARY_DIR}/E/CoreEvent ..)

if(UNIX)
  target_link_libraries(${NAME} PUBLIC dl stdc++fs)
endif(UNIX)

#install(TARGETS ${NAME}
#  RUNTIME DESTINATION ${INSTALL_FOLDER}
#  ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
#  LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
#  PRIVATE_HEADER DESTINATION ${INCLUDE_INSTALL_DIR}
#  PUBLIC_HEADER DESTINATION ${INSTALL_FOLDER})
#install(FILES ${HDRS} DESTINATION ${INCLUDE_INSTALL_DIR})
