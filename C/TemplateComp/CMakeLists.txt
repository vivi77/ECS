set(NAME TemplateComp)

file(GLOB SRCS *.hpp)
add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}
  )
target_link_libraries(${NAME} INTERFACE
  ${IDLIB_NAME}
  ecs_utils
  BaseComp
  )
target_sources(${NAME} INTERFACE ${SRCS})
