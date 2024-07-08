//
//  main.m
//  OpenGL_01
//
//  Created by hsp on 2024/6/25.
//

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

// Shaders
const GLchar* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource =
    "#version 330 core\n"
    "precision mediump float;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

// 将球横纵划分成50X50的网格
const int Y_SEGMENTS = 100;
const int X_SEGMENTS = 100;

unsigned int VBO, VAO, EBO;
GLint shaderProgram;

void generateSphereDataToOpenGL() {
  // TODO:
  // create 2D objects and 3D objects and/or lines (points) here and bind to
  // VAOs & VBOs

  std::vector<float> sphere_vertices_;
  std::vector<int> sphere_indices_;

  float radius = 0.5;

  // 生成球的顶点
  for (int y = 0; y <= Y_SEGMENTS; y++) {
    for (int x = 0; x <= X_SEGMENTS; x++) {
      float xSegment = (float)x / (float)X_SEGMENTS;
      float ySegment = (float)y / (float)Y_SEGMENTS;
      float xPos =
          std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI) * radius;
      float yPos = std::cos(ySegment * M_PI) * radius;
      float zPos =
          std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI) * radius;

      sphere_vertices_.push_back(xPos);
      sphere_vertices_.push_back(yPos);
      sphere_vertices_.push_back(zPos);
    }
  }

  // 生成球的Indices
  for (int i = 0; i < Y_SEGMENTS; i++) {
    for (int j = 0; j < X_SEGMENTS; j++) {
      sphere_indices_.push_back(i * (X_SEGMENTS + 1) + j);
      sphere_indices_.push_back((i + 1) * (X_SEGMENTS + 1) + j);
      sphere_indices_.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);

      sphere_indices_.push_back(i * (X_SEGMENTS + 1) + j);
      sphere_indices_.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
      sphere_indices_.push_back(i * (X_SEGMENTS + 1) + j + 1);
    }
  }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sphere_vertices_.size() * sizeof(float),
               &sphere_vertices_[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere_indices_.size() * sizeof(int),
               &sphere_indices_[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void paintSphere() {
  glBindVertexArray(VAO);

  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);

  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1,
                     GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE,
                     &view[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE,
                     &model[0][0]);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glBindVertexArray(VAO);
  // 使用线框模式绘制
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements(GL_TRIANGLES, X_SEGMENTS * Y_SEGMENTS * 6, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

int main() {
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  // Init GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "OpenGL_Sphere", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // Check for compile time errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  generateSphereDataToOpenGL();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

    paintSphere();

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
