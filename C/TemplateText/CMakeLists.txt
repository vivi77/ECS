set(NAME TemplateText)

file(GLOB SRCS TemplateText.hpp)
add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE)
target_link_libraries(${NAME} INTERFACE
  CIDGen
  CManager
  )
target_sources(${NAME} INTERFACE ${SRCS})
