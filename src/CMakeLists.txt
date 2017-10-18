
cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME "visitor")
project(${PROJECT_NAME})


include_directories(
)

set(PRIV
	main.cpp)

# create executable
add_executable(${PROJECT_NAME}
	    ${PRIV}
      ${INCLUDE_DIRECTORIES})

# common compilation options
target_compile_options(${PROJECT_NAME} PUBLIC -O3)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14)
target_compile_options(${PROJECT_NAME} PUBLIC -pedantic)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall)
target_compile_options(${PROJECT_NAME} PUBLIC -Wextra)
target_compile_options(${PROJECT_NAME} PUBLIC -Wconversion)
target_compile_options(${PROJECT_NAME} PUBLIC -fmessage-length=0)

# changed library output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${CMAKE_BUILD_TYPE})
