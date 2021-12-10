cmake_minimum_required(VERSION 3.5)

add_subdirectory(KnapsackProblem)

file(
  GLOB APP_SOURCES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  *.cpp)
foreach(testsourcefile ${APP_SOURCES})
  string(REPLACE ".cpp" "" testname ${testsourcefile})
  add_executable(${testname} ${testsourcefile})
  target_link_libraries(${testname} PUBLIC c_cpp_lib)
endforeach(testsourcefile ${APP_SOURCES})
