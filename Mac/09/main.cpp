//
//  main.m
//
//  Created by hsp on 2024/6/26.
//

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "../common/OBJ_Loader.h"
#include "../common/Shader.h"
#include "../common/camera.h"
#include "../common/stb_image_wrapper.h"

/**
 * OBJ File 加载
 */

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void loadObj() {
  // Initialize Loader
  objl::Loader Loader;

  std::string objFile =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/resources/"
      "spongebob_bind.obj";
  bool loadout = Loader.LoadFile(objFile.c_str());

  std::string outLog =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/09/out.txt";
  if (loadout) {
    std::ofstream file(outLog.c_str());

    for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {
      objl::Mesh curMesh = Loader.LoadedMeshes[i];

      file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

      // Print Vertices
      file << "Vertices:\n";

      // Go through each vertex and print its number,
      //  position, normal, and texture coordinate
      for (int j = 0; j < curMesh.Vertices.size(); j++) {
        file << "V" << j << ": " << "P(" << curMesh.Vertices[j].Position.X
             << ", " << curMesh.Vertices[j].Position.Y << ", "
             << curMesh.Vertices[j].Position.Z << ") " << "N("
             << curMesh.Vertices[j].Normal.X << ", "
             << curMesh.Vertices[j].Normal.Y << ", "
             << curMesh.Vertices[j].Normal.Z << ") " << "TC("
             << curMesh.Vertices[j].TextureCoordinate.X << ", "
             << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
      }

      // Print Indices
      file << "Indices:\n";

      // Go through every 3rd index and print the
      //	triangle that these indices represent
      for (int j = 0; j < curMesh.Indices.size(); j += 3) {
        file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", "
             << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2]
             << "\n";
      }

      // Print Material
      file << "Material: " << curMesh.MeshMaterial.name << "\n";
      file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", "
           << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z
           << "\n";
      file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", "
           << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z
           << "\n";
      file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", "
           << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z
           << "\n";
      file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
      file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
      file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
      file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
      file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
      file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
      file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
      file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
      file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

      // Leave a space to separate from the next mesh
      file << "\n";
    }

    // Close File
    file.close();
  }
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window =
      glfwCreateWindow(WIDTH, HEIGHT, "OpenGLCamera", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // tell GLFW to capture our mouse
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glewExperimental = GL_TRUE;
  glewInit();

  // 加载Obj数据
  loadObj();

  glEnable(GL_DEPTH_TEST);

  /**
   *数据准备阶段
   */

  glEnable(GL_DEPTH_TEST);

  // unsigned int VBO, cubeVAO;
  // glGenVertexArrays(1, &cubeVAO);
  // glGenBuffers(1, &VBO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindVertexArray(cubeVAO);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  // (void*)0); glEnableVertexAttribArray(0);
  // // normal attribute
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  //                       (void*)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);

  // unsigned int lightCubeVAO;
  // glGenVertexArrays(1, &lightCubeVAO);
  // glBindVertexArray(lightCubeVAO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  // (void*)0); glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());

    processInput(window);
    /**
     * 绘制操作
     */
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {}
