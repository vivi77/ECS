set(NAME DebugSystem)

file(GLOB SRCS
  *.cpp
  *.hh
  *.hpp
  ../S_lib.hh)
set(DIRS
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR})

add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC ${DIRS})
# IDLIB_NAME variable available from ECS/S/CMakeLists.txt
target_link_libraries(${NAME} PUBLIC
  Log
  EManagerEvent
  CManagerEvent
  CoreEvent
  CLISystemEvent
  EntityManagerEvent
  ${IDLIB_NAME}
  OSDLLoader
  EIDGen
  )
set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${SYS_OUTPUT_LOCATION})
generate_export_header(${NAME})

string(TOLOWER ${NAME} NAME_LOW)
install(TARGETS ${NAME} DESTINATION ${LIBRARY_INSTALL_DIR}/S)
install(FILES
  ${HDRS}
  ${CMAKE_BINARY_DIR}/S/${NAME_LOW}_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
