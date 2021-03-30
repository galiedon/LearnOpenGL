# OpenGL学习记录

**工具**：
- [cmake](https://cmake.org/download/)
- [vs code](https://code.visualstudio.com/download)
- [visual studio2019](https://visualstudio.microsoft.com/zh-hans/)

**Library**：
- [GLFW3](https://github.com/glfw/glfw)
- [GLAD](https://github.com/Dav1dde/glad)
- [stb](https://github.com/nothings/stb)

**下载**：`git clone --recursive https://github.com/galiedon/LearnOpenGL.git`

**编译**：`build.bat`

**运行**：`run.bat`

**问题**：
- 如果`SOIL`库无法正常链接，请修改以下内容：
  1. 在生成的`Src/ThirdParty/glad/include/glad.h`文件中添加`#define GLAD`
        ```cpp
        #ifndef __glad_h_
        #define __glad_h_
        #define GLAD
        ```
  2. 修改`SOIL.c`:

        从**23行**左右的
        ```cpp
        #include <GL/gl.h>
        ```
        修改为
        ```cpp
        #include <GLAD/glad.h>
        #include <GLFW/glfw3.h>
        #ifndef GLAD
            #include <GL/gl.h>
        #endif
        ```
        从**1974行**左右的
        ```cpp
        ext_addr = (P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC)
                wglGetProcAddress
                (
                    "glCompressedTexImage2DARB"
                );
        ```
        修改为
        ```cpp
        #ifndef GLAD
            ext_addr = (P_SOIL_GLCOMPRESSEDTEXIMAGE2DPROC)
                    wglGetProcAddress
                    (
                        "glCompressedTexImage2DARB"
                    );
        #endif
        ```
  3. 