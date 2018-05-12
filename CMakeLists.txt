cmake_minimum_required(VERSION 3.10)
project(CppTestSkeleton)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
add_executable(CppTestSkeleton main.cpp TestedClass.cpp TestedClass.h Tests/tests.cpp)
target_link_libraries(CppTestSkeleton gtest gtest_main)
