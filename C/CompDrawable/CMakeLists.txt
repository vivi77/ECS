set(NAME CompDrawable)

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.hh *.hpp)
add_library(${NAME} SHARED ${SRCS} ${HDRS})
target_include_directories(${NAME} PUBLIC
  ${CMAKE_BINARY_DIR}/C/${NAME}
  )
target_link_libraries(${NAME}
  )

set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${OUTPUT_LOCATION})
generate_export_header(${NAME})
string(TOLOWER ${NAME} NAME_LOW)
install(TARGETS ${NAME} DESTINATION ${LIBRARY_INSTALL_DIR}/C)
install(FILES
  ${HDRS}
  ${CMAKE_BINARY_DIR}/C/${NAME_LOW}_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
