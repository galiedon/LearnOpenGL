# OpenGL学习记录

**工具**：
- [cmake](https://cmake.org/download/)
- [vs code](https://code.visualstudio.com/download)
- [visual studio2019](https://visualstudio.microsoft.com/zh-hans/)

**Library**：
- [GLFW3](https://github.com/glfw/glfw)
- [GLAD](https://github.com/Dav1dde/glad)
- [SOIL](https://github.com/paralin/soil)
- [glm](https://github.com/g-truc/glm)
- [assimp](https://github.com/assimp/assimp)

**下载**：`git clone https://github.com/galiedon/LearnOpenGL.git`

**编译**：`build.bat`

**运行**：`run.bat`

**目录介绍**：
TODO

**Demo介绍**：
1. `Demo1`：使用了VBO、IBO、VAO绘制出了矩形。
2. `Demo2`：使用uniform使图形动起来，并传入了color字段使图形具有颜色
3. `Demo3`：引入`soil库`读取图片，使用两张图片生成贴图并显示，添加键盘响应事件，上、下键可以调整两张图片的alpha值
4. `Demo4`：引入`glm库`完成数学运算，顶点属性中传入`TexCoords`，并通过`uniform mat4 trans`传入变换矩阵，完成坐标转换。 
5. `Demo5`：引入`Z-Buffer`设置，引入五大坐标系统来实现坐标的变换。
6. `Demo6`：添加摄像机类，完成自由移动功能
7. `Demo7`：添加光照属性，搭建光照环境
8. `Demo8`：引入冯氏光照模型
9. `Demo9`：引入材质概念，调整光照计算公式
10. `Demo10`：引入光照贴图（漫反射贴图、镜面光照贴图）
11. `Demo11`：引入不同类型的光源（平行光、点光、聚光）, 并搭建多光源场景。
11. `Demo12`：引入顶点、网格、模型。


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
   