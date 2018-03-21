set(NAME CoreSystemProxy)

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.hh *.hpp)
set(DIRS
  ${PROJECT_SOURCE_DIR}
  )

add_library(${NAME} SHARED ${SRCS} ${DIRS})
target_include_directories(${NAME} PUBLIC ${DIRS})
target_link_libraries(${NAME} PUBLIC)
