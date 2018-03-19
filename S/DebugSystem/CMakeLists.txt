set(NAME DebugSystem)

file(GLOB SRCS
  *.cpp)
file(GLOB HDRS
  *.hh
  *.hpp)
set(HDRS ${HDRS} ../S_lib.hh)
set(DIRS ${DIRS}
  ${CMAKE_BINARY_DIR}/S/${NAME}
  ${CMAKE_BINARY_DIR}/E/CoreEvent
  ${CMAKE_BINARY_DIR}/E/EManagerEvent
  ${CMAKE_BINARY_DIR}/E/CManagerEvent
  ${PROJECT_SOURCE_DIR}/E/CoreEvent
  ${PROJECT_SOURCE_DIR}/E/EManagerEvent
  ${PROJECT_SOURCE_DIR}/E/CManagerEvent
  ${PROJECT_SOURCE_DIR}/C
  ${PROJECT_SOURCE_DIR}/E
  ${PROJECT_SOURCE_DIR}/S)

add_library(${NAME} SHARED ${SRCS} ${HDRS})
target_include_directories(${NAME} PUBLIC ${DIRS})
# IDLIB_NAME variable available from ECS/S/CMakeLists.txt
target_link_libraries(${NAME} ${IDLIB_NAME} EManager ${LIBS})
set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${SYS_OUTPUT_LOCATION})
generate_export_header(${NAME})

string(TOLOWER ${NAME} NAME_LOW)
install(TARGETS ${NAME} DESTINATION ${LIBRARY_INSTALL_DIR}/S)
install(FILES
  ${HDRS}
  ${CMAKE_BINARY_DIR}/S/${NAME_LOW}_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
