cmake_minimum_required(VERSION 3.10)

add_subdirectory(ThirdParty)

configure_file(CMake.h.in CMake.h)


set(sources 
    main.cpp
    DemoBase.cpp
    Demo1/Demo1.cpp
    Object/Object.cpp
    )


add_executable(LearnOpenGL ${sources})


target_link_libraries(LearnOpenGL PUBLIC 
                        glfw
                        glad)

target_include_directories(LearnOpenGL PUBLIC 
                            "${GLFW_SOURCE_DIR}/include"
                            "${GLAD_SOURCE_DIR}/include")
