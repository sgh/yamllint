cmake_minimum_required(VERSION 2.8)
project(yamllint)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

set(SRC src/main.cpp)

link_libraries(yaml-cpp)
add_executable(yamllint ${SRC})
