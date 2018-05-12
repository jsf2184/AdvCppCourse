cmake_minimum_required(VERSION 3.10)
project(AdvCppCourse)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
add_executable(AdvCppCourse main.cpp TestedClass.cpp TestedClass.h Tests/tests.cpp Tests/exceptions/StandardExceptions.cpp Tests/exceptions/CustomExceptions.cpp Tests/exceptions/BasicExceptions.cpp Tests/exceptions/CatchingSubclassExceptions.cpp)
target_link_libraries(AdvCppCourse gtest gtest_main)
