set(NAME Threadpool)

file(GLOB SRCS *.cpp *.hh)

add_library(${NAME} SHARED ${SRCS})
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${NAME} lel_utils pthread)
