set(MANAGER_NAME CManager)

file(GLOB SRCS *.cpp *.hh *.hpp)
add_library(${MANAGER_NAME} SHARED ${SRCS})
target_include_directories(${MANAGER_NAME} PUBLIC
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}
  )
target_link_libraries(${MANAGER_NAME} PUBLIC
  EManager
  CManagerEvent
  )

set_target_properties(${MANAGER_NAME} PROPERTIES IMPORTED_LOCATION ${OUTPUT_LOCATION})
generate_export_header(${MANAGER_NAME})
string(TOLOWER ${MANAGER_NAME} MANAGER_NAME_LOW)
install(TARGETS ${MANAGER_NAME} DESTINATION ${LIBRARY_INSTALL_DIR}/C)
install(FILES
  ${HDRS}
  ${CMAKE_BINARY_DIR}/C/${MANAGER_NAME_LOW}_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
