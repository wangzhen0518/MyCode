cmake_minimum_required(VERSION 3.5)

project(c_cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_executable(random_data lib/random_data.cpp)

add_library(c_cpp_lib SHARED lib/data_structure.cpp lib/sort.cpp)

target_include_directories(c_cpp_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)