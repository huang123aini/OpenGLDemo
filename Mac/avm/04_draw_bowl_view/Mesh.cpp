/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-05 10:53:47
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-05 12:08:23
 * @FilePath: /OpenGL_Demo/Mac/avm/02_uyvy_to_fbo_4_fisheye/Mesh.cpp
 */
#include "Mesh.h"

Mesh::Mesh() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Mesh::createQuadMesh(float x, float y, float w, float h) {
  // 顶点数据

  V2_T0 VerData[4];

  // 索引数据
  unsigned int indices[] = {
      0, 1, 2,  // first triangle
      2, 1, 3   // second triangle
  };

  // 纹理坐标
  VerData[0].t0x = 0.0f;
  VerData[0].t0y = 0.0f;
  VerData[1].t0x = 1.0f;
  VerData[1].t0y = 0.0f;
  VerData[2].t0x = 0.0f;
  VerData[2].t0y = 1.0f;
  VerData[3].t0x = 1.0f;
  VerData[3].t0y = 1.0f;

  float l = x * 2.0f - 1.0f;
  float t = y * 2.0f - 1.0f;
  float r = (x + w) * 2.0f - 1.0f;
  float b = (y + h) * 2.0f - 1.0f;
  VerData[0].x = l;
  VerData[0].y = t;
  VerData[1].x = r;
  VerData[1].y = t;
  VerData[2].x = l;
  VerData[2].y = b;
  VerData[3].x = r;
  VerData[3].y = b;

  // 顶点数据
  float vertices[] = {
      // positions         // texture coords
      VerData[0].x, VerData[0].y, VerData[0].t0x, VerData[0].t0y,
      VerData[1].x, VerData[1].y, VerData[1].t0x, VerData[1].t0y,
      VerData[2].x, VerData[2].y, VerData[2].t0x, VerData[2].t0y,
      VerData[3].x, VerData[3].y, VerData[3].t0x, VerData[3].t0y};

  // 绑定VAO
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                        (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
}