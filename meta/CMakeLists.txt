set(NAME meta)

file(GLOB HDRS *.hpp)

add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${NAME} INTERFACE ${HDRS})
