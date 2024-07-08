/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-06-28 10:32:21
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-05 14:49:15
 * @FilePath: /OpenGL_Demo/Mac/01_bowl/BowlModel.cpp
 */
#include "BowlModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float k_rotation = 0.8f;

BowlModel::BowlModel() { bowl_mapping_ = std::make_unique<BowlMapping>(); }

BowlModel::~BowlModel() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void BowlModel::update() {
  std::vector<float> bowlVertices;
  std::vector<unsigned short> bowlIndices;

  // 生成碗模型的点
  bowl_mapping_->buildBowlPoint(k_rotation);
  // 更新顶点数据
  bowl_mapping_->getPointBuffer(bowlVertices);

  // 更新索引数据
  bowl_mapping_->getIndexBuffer(bowlIndices);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // 绑定VAO
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, bowlVertices.size() * sizeof(float),
               &bowlVertices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               bowlIndices.size() * sizeof(unsigned short), &bowlIndices[0],
               GL_STATIC_DRAW);

  // 解绑VAO
  glBindVertexArray(0);

  // 准备shader 只绘制Mesh
  std::string bowl_vs_mesh_only =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/shaders/"
      "01_bowl.vs";
  std::string bowl_fs_mesh_only =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/shaders/"
      "01_bowl.fs";
  shader_mesh_only_ = std::make_unique<Shader>(bowl_vs_mesh_only.c_str(),
                                               bowl_fs_mesh_only.c_str());

  // 准备shader 绘制Mesh贴图
  std::string bowl_vs_mesh_texture =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/shaders/"
      "01_bowl_texture.vs";
  std::string bowl_fs_mesh_texture =
      "/Users/huangshiping/Documents/GitHub/OpenGL_Demo/Mac/shaders/"
      "01_bowl_texture.fs";
  shader_mesh_texture_ = std::make_unique<Shader>(bowl_vs_mesh_texture.c_str(),
                                                  bowl_fs_mesh_texture.c_str());
}

void BowlModel::setTextureId(unsigned int textureId) {
  texture_id_ = textureId;
}

void BowlModel::renderMeshOnly() {
  glBindVertexArray(VAO);

  // camera/view transformation
  glm::mat4 view = glm::mat4(
      1.0f);  // make sure to initialize matrix to identity matrix first
  float radius = 1.0f;
  float camX = static_cast<float>(sin(0) * radius);
  float camZ = static_cast<float>(cos(0) * radius);

  /**
   * LookAt: 1、相机位置向量
   * 2、相机指向Target位置向量
   * 3、世界空间朝上向量
   */
  view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

  shader_mesh_only_->use();
  shader_mesh_only_->setMat4("projection", projection);
  shader_mesh_only_->setMat4("view", view);
  shader_mesh_only_->setMat4("model", model);

  if (texture_id_ != -1) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
  }

  glBindVertexArray(VAO);
  // 使用线框模式绘制
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements(GL_TRIANGLES, bowl_mapping_->getIndexCount(),
                 GL_UNSIGNED_SHORT, 0);

  glBindVertexArray(0);
}

void BowlModel::renderMeshTexture() {
  glBindVertexArray(VAO);

  // camera/view transformation
  glm::mat4 view = glm::mat4(
      1.0f);  // make sure to initialize matrix to identity matrix first
  float radius = 1.0f;
  float camX = static_cast<float>(sin(0) * radius);
  float camZ = static_cast<float>(cos(0) * radius);

  /**
   * LookAt: 1、相机位置向量
   * 2、相机指向Target位置向量
   * 3、世界空间朝上向量
   */
  view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(0.0f, 1.0f, 0.0f));

  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

  shader_mesh_texture_->use();
  shader_mesh_texture_->setMat4("projection", projection);
  shader_mesh_texture_->setMat4("view", view);
  shader_mesh_texture_->setMat4("model", model);
  shader_mesh_texture_->setInt("uTexture", 0);

  if (texture_id_ != -1) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
  }

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, bowl_mapping_->getIndexCount(),
                 GL_UNSIGNED_SHORT, 0);

  glBindVertexArray(0);
}