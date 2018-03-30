set(NAME Vector)

file(GLOB HDRS *.hh)
set(DIRS
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}
  )

add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE ${DIRS})
target_link_libraries(${NAME} INTERFACE)
target_sources(${NAME} INTERFACE ${HDRS})
