cmake_minimum_required(VERSION 3.10)
# BUILD_STATIC_LIBS
set(STB_SOURCE_DIR ${GLFW_SOURCE_DIR}/../stb/)
add_subdirectory(ThirdParty)

configure_file(CMake.h.in CMake.h)

set(sources 
    main.cpp
    DemoBase.cpp
    Demo1/Demo1.cpp
    Demo2/Demo2.cpp
    Demo3/Demo3.cpp
    Demo4/Demo4.cpp
    Demo5/Demo5.cpp
    Demo6/Demo6.cpp
    Demo7/Demo7.cpp
    Demo8/Demo8.cpp
    
    Object/Object.cpp
    Camera/Camera.cpp
    Shader/Shader.cpp
    )


add_executable(LearnOpenGL ${sources})

target_link_libraries(LearnOpenGL PUBLIC 
                        glfw
                        glad
                        soil
                        glm)

target_include_directories(LearnOpenGL PUBLIC 
                            "${GLFW_SOURCE_DIR}/include"
                            "${GLAD_SOURCE_DIR}/include"
                            "${GLFW_SOURCE_DIR}/../soil/inc"
                            "${GLFW_SOURCE_DIR}/../glm/glm")
