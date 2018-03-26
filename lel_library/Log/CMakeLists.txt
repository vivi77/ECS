set(NAME Log)

file(GLOB SRCS *.cpp *.hh)

add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
