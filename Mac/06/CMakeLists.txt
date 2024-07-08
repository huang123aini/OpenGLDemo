cmake_minimum_required(VERSION 3.5)
project(opengl_material)

# 包含头文件
set(GLFW_H /usr/local/Cellar/glfw/3.4/include)
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
set(GLM_H /Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/third_party/glm)

include_directories(${GLFW_H} ${GLEW_H} ${GLM_H})


#添加链接
set(GLFW_LINK /usr/local/Cellar/glfw/3.4/lib/libglfw.3.4.dylib)
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib)
link_libraries(${GLFW_LINK} ${GLEW_LINK})


# Add executables
ADD_EXECUTABLE(opengl_material main.cpp)
   
# 链接系统的 OpenGL 框架
if (APPLE)
    target_link_libraries(opengl_material "-framework OpenGL")
endif()
