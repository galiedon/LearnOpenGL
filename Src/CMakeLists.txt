cmake_minimum_required(VERSION 3.10)

add_subdirectory(ThirdParty)

configure_file(CMake.h.in CMake.h)

add_executable(LearnOpenGL main.cpp)

target_include_directories(LearnOpenGL PUBLIC 
                            "${GLFW_SOURCE_DIR}/include"
                            "${GLAD_SOURCE_DIR}/include")
