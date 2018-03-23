set(NAME Vector3)

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.hh *.hpp)
set(DIRS
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}
  )

add_library(${NAME} SHARED ${SRCS} ${HDRS})
target_include_directories(${NAME} PUBLIC ${DIRS})
target_link_libraries(${NAME} PUBLIC)

set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${UTIL_OUTPUT_LOCATION})
generate_export_header(${NAME})
string(TOLOWER ${NAME} NAME_LOW)
install(TARGETS ${NAME} DESTINATION ${LIBRARY_INSTALL_DIR}/Utility)
install(FILES
  ${HDRS}
  ${CMAKE_BINARY_DIR}/Utility/${NAME_LOW}_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
