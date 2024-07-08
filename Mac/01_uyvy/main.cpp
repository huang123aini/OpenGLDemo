//
//  main.m
//  OpenGL_01
//
//  Created by hsp on 2024/6/20.
//

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include "../common/Shader.h"
#include "stb_image_wrapper.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

const int PIXEL_WIDTH = 1280;
const int PIXEL_HEIGHT = 720;

FILE* infile = NULL;
unsigned char buffer[PIXEL_WIDTH * PIXEL_HEIGHT * 2];

void readUyvyFile() {
  std::string uyvyFile =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/01_uyvy/"
      "_view_0086_1.uyvy";
  if ((infile = fopen(uyvyFile.c_str(), "rb")) == NULL) {
    printf("cannot open this file\n");
    return;
  }

  if (fread(buffer, 1, PIXEL_WIDTH * PIXEL_HEIGHT * 2, infile) !=
      PIXEL_WIDTH * PIXEL_HEIGHT * 2) {
    // Loop
    fseek(infile, 0, SEEK_SET);
    fread(buffer, 1, PIXEL_WIDTH * PIXEL_HEIGHT * 2, infile);
  }
}

int main() {
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "Texture", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  int window_width, window_height;
  glfwGetFramebufferSize(window, &window_width, &window_height);
  glViewport(0, 0, window_width, window_height);

  /**
   * 数据准备阶段
   */

  std::string textureVsPath =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/shaders/"
      "01_uyvy.vs";
  std::string textureFsPath =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/shaders/"
      "01_uyvy.fs";

  // 生成Shader
  Shader ourShader(textureVsPath.c_str(), textureFsPath.c_str());

  // 读取文件内容
  readUyvyFile();

  // 顶点数据
  //   float vertices[] = {
  //       // positions         // texture coords
  //       0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
  //       0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
  //       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
  //       -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
  //   };

  float vertices[] = {
      // positions         // texture coords
      1.f,  1.f,  0.0f, 1.0f, 0.0f,  // top right
      1.f,  -1.f, 0.0f, 1.0f, 1.0f,  // bottom right
      -1.f, -1.f, 0.0f, 0.0f, 1.0f,  // bottom left
      -1.f, 1.f,  0.0f, 0.0f, 0.0f   // top left
  };

  // 索引数据
  unsigned int indices[] = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // 绑定VAO
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // 加载并创建纹理
  unsigned int uyvyId;
  glGenTextures(1, &uyvyId);
  glBindTexture(GL_TEXTURE_2D, uyvyId);
  // 设置纹理环绕模式
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // 设置纹理过滤
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // 将数据加载到GPU
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, PIXEL_WIDTH / 2, PIXEL_HEIGHT, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, buffer);

  glGenerateMipmap(GL_TEXTURE_2D);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    /**
     * 绘制操作
     */

    // 清理屏幕颜色缓冲
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 激活并绑定纹理
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, uyvyId);

    // 使用shader
    ourShader.use();
    // 绑定VAO
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Swap the screen buffers
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
