set(NAME TextInputUpdaterEvents)

file(GLOB SRCS *.hh *.hpp *.cpp)
add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}
  )
target_link_libraries(${NAME} INTERFACE
  ${IDLIB_NAME}
  ${MANAGER_NAME}
  )
target_sources(${NAME} INTERFACE ${SRCS})
