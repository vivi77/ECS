set(NAME EntityManagerEvent)

file(GLOB SRCS *.cpp *.hh *.hpp)
set(DIRS
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR})
# IDLIB_NAME and MANAGER_NAME variables available from ECS/E/CMakeLists.txt
set(LIBS
  ${IDLIB_NAME}
  ${MANAGER_NAME}
  )

add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC ${DIRS})
target_link_libraries(${NAME} PUBLIC ${LIBS})

set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${EVENT_OUTPUT_LOCATION})
generate_export_header(${NAME})
string(TOLOWER ${NAME} NAME_LOW)
install(TARGETS ${NAME} DESTINATION ${LIBRARY_INSTALL_DIR}/E)
install(FILES
  ${CMAKE_BINARY_DIR}/E/${NAME_LOW}_export.h
  DESTINATION ${INCLUDE_INSTALL_DIR})
