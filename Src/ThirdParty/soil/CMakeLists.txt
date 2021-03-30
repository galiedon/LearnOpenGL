cmake_minimum_required(VERSION 3.10)

include_directories(inc)

ADD_LIBRARY(soil STATIC
  src/image_helper.c
  src/stb_image_aug.c
  src/image_DXT.c
  src/SOIL.c
  )

target_link_libraries(soil PUBLIC 
glfw
glad)
target_include_directories(soil PUBLIC 
                          "${GLAD_SOURCE_DIR}/include"
                          "${GLFW_SOURCE_DIR}/include"
                          "${SOIL_SOURCE_DIR}/inc")

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()