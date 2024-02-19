cmake_minimum_required(VERSION 3.18)
project(Binary-Reader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to Release.")
	message(STATUS "To Debug, run `cmake -DCMAKE_BUILD_TYPE=Debug`")
	set(CMAKE_BUILD_TYPE "Release")
endif()

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /W4")
elseif(UNIX)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -ggdb")
endif()

set(BINARY_READER_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/BinaryReader.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/BinaryReaderFile.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/BinaryReaderBuffered.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/BinaryReaderExceptions.cpp"
)

add_library(Binary-Reader STATIC ${BINARY_READER_SOURCES})
target_include_directories(Binary-Reader PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
