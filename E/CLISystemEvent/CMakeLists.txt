set(NAME CLISystemEvent)

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.hh *.hpp)
set(HDRS ${HDRS} ../E_lib.hh)
set(DIRS
  ${CMAKE_BINARY_DIR}/E/${NAME}
  ${PROJECT_SOURCE_DIR}/E
  ${PROJECT_SOURCE_DIR})

add_library(${NAME} SHARED ${SRCS} ${HDRS})
target_include_directories(${NAME} PUBLIC ${DIRS})
# IDLIB_NAME and MANAGER_NAME variables available from ECS/E/CMakeLists.txt
target_link_libraries(${NAME} ${IDLIB_NAME} ${MANAGER_NAME} ${LIBS})
set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${EVENT_OUTPUT_LOCATION})
generate_export_header(${NAME})

string(TOLOWER ${NAME} NAME_LOW)
install(TARGETS ${NAME} DESTINATION ${LIBRARY_INSTALL_DIR}/E)
install(FILES
  ${HDRS}
  ${CMAKE_BINARY_DIR}/E/${NAME_LOW}_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
