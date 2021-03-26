cmake_minimum_required(VERSION 3.10)

# set the project name
project(LearnOpenGL VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include sub-projects.
add_subdirectory ("Src")

install(TARGETS LearnOpenGL 
        PUBLIC_HEADER DESTINATION include
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

include(CTest)
# enable_testing()
# add_test(Usage Debug/bin/LearnOpenGL)


