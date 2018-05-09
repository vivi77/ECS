set(NAME Commands)

file(GLOB SRCS *.cpp *.hpp *.hh)
add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC
  ${CMAKE_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}
  )
target_link_libraries(${NAME} PUBLIC
  ${IDLIB_NAME}
  BaseComp
  )
#target_sources(${NAME} INTERFACE ${SRCS})
